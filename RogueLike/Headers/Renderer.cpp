#include "Renderer.h"
#include "Window.h"
#include "Shader.h"
#include <iostream>
#include <chrono>
#include "Headers/EntityManager.h"
#include "Headers/Entity.h"

Renderer* Renderer::instance = nullptr;

void Renderer::Init()
{
	if (instance)
		delete instance;
	instance = new Renderer();
}

void Renderer::Shutdown()
{
	if (instance)
		delete instance;
	instance = nullptr;
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::BeginScene(const glm::vec3& camera, const Shader& shader)
{
	shader.Bind();
	shader.SetCameraUniform(camera.x,camera.y,camera.z);
	Get()->m_camera = camera;
}

void Renderer::DrawSprite(const Transform& tr, uint32_t spi)
{
	if (tr.size.x == tr.size.y && tr.size.x == 0)
		return;
	Renderer* renderer = Get();
	const glm::vec2 res = Window::GetResolution();
	const glm::vec3& cam = renderer->m_camera;

	if (  (tr.pos.x + tr.size.x / 2.0f - cam.x) / cam.z < -res.x / 2.0f
		||(tr.pos.x - tr.size.x / 2.0f - cam.x) / cam.z >= res.x / 2.0f

		||(tr.pos.y + tr.size.y / 2.0f - cam.y) / cam.z < -res.y / 2.0f
		||(tr.pos.y - tr.size.y / 2.0f - cam.y) / cam.z >= res.y / 2.0f)
			return;
	uint32_t textureID;
	glm::vec4 si = renderer->m_ssManager.GetSprite(spi, &textureID);
	float tex = textureID;
	const glm::vec2 corner(si.x, si.y - si.w);
	const glm::vec2 size(si.z, si.w);



	renderer->m_vertices.emplace_back(tr.pos.x - tr.size.x / 2.0f, tr.pos.y - tr.size.y / 2.0f, corner.x,			corner.y		 , tex);
	renderer->m_vertices.emplace_back(tr.pos.x + tr.size.x / 2.0f, tr.pos.y - tr.size.y / 2.0f, corner.x + size.x, corner.y			 , tex);
	renderer->m_vertices.emplace_back(tr.pos.x + tr.size.x / 2.0f, tr.pos.y + tr.size.y / 2.0f, corner.x + size.x, corner.y + size.y , tex);
	renderer->m_vertices.emplace_back(tr.pos.x - tr.size.x / 2.0f, tr.pos.y + tr.size.y / 2.0f, corner.x,			corner.y + size.y, tex);

	if (renderer->m_vertices.size() >> 2 >= static_cast<uint64_t>(renderer->m_maxBatchSize))
	{
		Flush();
	}
}

void Renderer::DrawSprite(EntityManager& em, const Transform& transform, uint32_t spriteIndex)
{
	Transform tr = transform;
	entity_t parentID = tr.parentID;
	while (parentID & entity_traits::enabledMask)
	{
		Transform& parent = em.GetComponent<Transform>(parentID);
		tr.pos += parent.pos;
		parentID = parent.parentID;
	}
	DrawSprite(tr, spriteIndex);
}

void Renderer::Flush()
{
	Renderer* renderer = Get();
	for (int i = 0; i < renderer->m_lastTextureSlot; i++)
		glBindTextureUnit(i, renderer->m_boundTextures[i]);

	glBufferSubData(GL_ARRAY_BUFFER, 0, renderer->m_vertices.size() * sizeof(Vertex), renderer->m_vertices.data());
	glDrawElements(GL_TRIANGLES, (renderer->m_vertices.size() >> 1) * 3, GL_UNSIGNED_INT, nullptr);
	renderer->m_vertices.clear();
	renderer->m_lastTextureSlot = 0;
}

void Renderer::EndScene()
{
	if (Get()->m_vertices.size() > 0)
		Flush();
}

void Renderer::DrawUI(UI* ui)
{
	uint32_t spriteID = ui->GetSpriteID();
	uint32_t texID;
	glm::vec4 si = Get()->m_ssManager.GetSprite(spriteID, &texID);
	float tex = texID;
	const Transform& tr = ui->transform;
	const glm::vec2& res = Window::GetResolution();
	const glm::vec2 corner(si.x, si.y - si.w);
	const glm::vec2 size(si.z, si.w);
	glm::vec2 anchorPos;
	glm::vec2 parentPos(0, 0);
	AnchorPoint parentAnchor = AnchorPoint::CC;
	UI* ptr = ui->parent;
	if (ptr)
	{
		do
		{
			parentPos += ptr->transform.pos;
			parentAnchor = ptr->anchor;
			ptr = ptr->parent;
		} while (ptr);

		switch (parentAnchor)
		{
		case AnchorPoint::LU:
			anchorPos = { -res.x / 2.0f + ui->parent->transform.size.x / 2.0f, res.y / 2.0f - ui->parent->transform.size.y / 2.0f };
			break;
		case AnchorPoint::CU:
			anchorPos = { 0.0f, res.y / 2.0f - ui->parent->transform.size.y / 2.0f };
			break;
		case AnchorPoint::RU:
			anchorPos = { res.x / 2.0f - ui->parent->transform.size.x / 2.0f, res.y / 2.0f - ui->parent->transform.size.y / 2.0f };
			break;
		case AnchorPoint::LC:
			anchorPos = { -res.x / 2.0f + ui->parent->transform.size.x / 2.0f, 0.0f };
			break;
		case AnchorPoint::CC:
			anchorPos = { 0.0f, 0.0f };
			break;
		case AnchorPoint::RC:
			anchorPos = { res.x / 2.0f - ui->parent->transform.size.x / 2.0f, 0.0f };
			break;
		case AnchorPoint::LD:
			anchorPos = { -res.x / 2.0f + ui->parent->transform.size.x / 2.0f, -res.y / 2.0f + ui->parent->transform.size.y / 2.0f };
			break;
		case AnchorPoint::CD:
			anchorPos = { 0.0f, -res.y / 2.0f + ui->parent->transform.size.y / 2.0f };
			break;
		case AnchorPoint::RD:
			anchorPos = { res.x / 2.0f - ui->parent->transform.size.x / 2.0f, -res.y / 2.0f + ui->parent->transform.size.y / 2.0f };
			break;
		}


		switch (ui->anchor)
		{
		case AnchorPoint::LU:
			anchorPos += glm::vec2 ( -ui->parent->transform.size.x / 2.0f + tr.size.x / 2.0f, ui->parent->transform.size.y / 2.0f - tr.size.y / 2.0f );
			break;
		case AnchorPoint::CU:
			anchorPos += glm::vec2 ( 0.0f, ui->parent->transform.size.y / 2.0f - tr.size.y / 2.0f );
			break;
		case AnchorPoint::RU:
			anchorPos += glm::vec2 ( ui->parent->transform.size.x / 2.0f - tr.size.x / 2.0f, ui->parent->transform.size.y / 2.0f - tr.size.y / 2.0f );
			break;
		case AnchorPoint::LC:
			anchorPos += glm::vec2 ( -ui->parent->transform.size.x / 2.0f + tr.size.x / 2.0f, 0.0f );
			break;
		case AnchorPoint::CC:
			anchorPos += glm::vec2 ( 0.0f, 0.0f );
			break;
		case AnchorPoint::RC:
			anchorPos += glm::vec2 ( ui->parent->transform.size.x / 2.0f - tr.size.x / 2.0f, 0.0f );
			break;
		case AnchorPoint::LD:
			anchorPos += glm::vec2 ( -ui->parent->transform.size.x / 2.0f + tr.size.x / 2.0f, -ui->parent->transform.size.y / 2.0f + tr.size.y / 2.0f );
			break;
		case AnchorPoint::CD:
			anchorPos += glm::vec2 ( 0.0f, -ui->parent->transform.size.y / 2.0f + tr.size.y / 2.0f );
			break;
		case AnchorPoint::RD:
			anchorPos += glm::vec2 ( ui->parent->transform.size.x / 2.0f - tr.size.x / 2.0f, -ui->parent->transform.size.y / 2.0f + tr.size.y / 2.0f );
			break;
		}
	}
	else
	{
		switch (ui->anchor)
		{
		case AnchorPoint::LU:
			anchorPos = { -res.x / 2.0f + tr.size.x / 2.0f, res.y / 2.0f - tr.size.y / 2.0f };
			break;
		case AnchorPoint::CU:
			anchorPos = { 0.0f, res.y / 2.0f - tr.size.y / 2.0f };
			break;
		case AnchorPoint::RU:
			anchorPos = { res.x / 2.0f - tr.size.x / 2.0f, res.y / 2.0f - tr.size.y / 2.0f };
			break;
		case AnchorPoint::LC:
			anchorPos = { -res.x / 2.0f + tr.size.x / 2.0f, 0.0f };
			break;
		case AnchorPoint::CC:
			anchorPos = { 0.0f, 0.0f };
			break;
		case AnchorPoint::RC:
			anchorPos = { res.x / 2.0f - tr.size.x / 2.0f, 0.0f };
			break;
		case AnchorPoint::LD:
			anchorPos = { -res.x / 2.0f + tr.size.x / 2.0f, -res.y / 2.0f + tr.size.y / 2.0f };
			break;
		case AnchorPoint::CD:
			anchorPos = { 0.0f, -res.y / 2.0f + tr.size.y / 2.0f };
			break;
		case AnchorPoint::RD:
			anchorPos = { res.x / 2.0f - tr.size.x / 2.0f, -res.y / 2.0f + tr.size.y / 2.0f };
			break;
		}
	}
	

	Get()->m_vertices.emplace_back(parentPos.x + anchorPos.x + tr.pos.x - tr.size.x / 2.0f, parentPos.y + anchorPos.y + tr.pos.y - tr.size.y / 2.0f, corner.x		  , corner.y		 , tex);
	Get()->m_vertices.emplace_back(parentPos.x + anchorPos.x + tr.pos.x + tr.size.x / 2.0f, parentPos.y + anchorPos.y + tr.pos.y - tr.size.y / 2.0f, corner.x + size.x, corner.y		 , tex);
	Get()->m_vertices.emplace_back(parentPos.x + anchorPos.x + tr.pos.x + tr.size.x / 2.0f, parentPos.y + anchorPos.y + tr.pos.y + tr.size.y / 2.0f, corner.x + size.x, corner.y + size.y, tex);
	Get()->m_vertices.emplace_back(parentPos.x + anchorPos.x + tr.pos.x - tr.size.x / 2.0f, parentPos.y + anchorPos.y + tr.pos.y + tr.size.y / 2.0f, corner.x		  , corner.y + size.y, tex);

	if (Get()->m_vertices.size() >> 2 >= static_cast<uint64_t>(Get()->m_maxBatchSize))
	{
		Flush();
	}
}

void Renderer::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

uint32_t Renderer::GetNextTextureUnit()
{
	return Get()->m_lastTextureSlot++;
}

bool Renderer::isTextureBound(uint32_t TextureID)
{
	Renderer* renderer = Get();
	for (int i = 0; i < renderer->m_lastTextureSlot; i++)
	{
		if (renderer->m_boundTextures[i] == TextureID)
			return true;
	}
	return false;
}

void Renderer::BindTexture(uint32_t TextureID)
{
	Renderer* renderer = Get();
	if (!renderer->isTextureBound(TextureID))
	{
		renderer->m_boundTextures[renderer->GetNextTextureUnit()] = TextureID;
	}
}

Renderer* Renderer::Get()
{
	return Renderer::instance;
}

Renderer::Renderer()
	:m_vertices(),
	m_camera(0,0,1.0f),
	m_lastTextureSlot(0),
	m_maxBatchSize(10000)
{
	memset(m_boundTextures.data(), 0, 32 * sizeof(uint32_t));

	if (glewInit() != GLEW_OK)
	{
		throw - 1;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glCreateVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glCreateBuffers(1, &m_vbo);
	glCreateBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	
	std::vector<uint32_t> indices;
	indices.reserve(m_maxBatchSize * 6);

	for (int index = 0; index < m_maxBatchSize * 4; index += 4)
	{
		indices.push_back(index);
		indices.push_back(index + 1);
		indices.push_back(index + 2);
		indices.push_back(index + 2);
		indices.push_back(index + 3);
		indices.push_back(index + 0);
	}


	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, static_cast<uint64_t>(m_maxBatchSize) * 4Ui64 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2 , GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, textureID));

	m_ssManager.ReserveSheets(2);
	m_ssManager.AddSpriteSheet(SpriteSheet("Textures/SpriteSheet.png", 128,128));
	m_ssManager.AddSpriteSheet(SpriteSheet("Textures/Hero Walk.png", 9,19));
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1,&m_vao);
	glDeleteBuffers(1,&m_vbo);
	glDeleteBuffers(1,&m_ibo);
}
