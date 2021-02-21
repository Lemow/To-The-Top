#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <glm/glm.hpp>
#include "Transform.h"
#include "Sprite.h"
#include "SpriteSheetManager.h"
#include "Headers/EntityManager.h"
#include "Headers/Entity.h"
#include "UI.h"

struct Vertex
{
	glm::vec2 pos;
	glm::vec2 uv;
	float textureID;

	Vertex() = default;
	Vertex(const glm::vec2& pos, const glm::vec2& uv, float textureID)
		:pos(pos),
		uv(uv),
		textureID(textureID)
	{}
	Vertex(float posX, float posY, float u, float v, float textureID)
		:pos(posX, posY),
		uv(u, v),
		textureID(textureID)
	{}
};

class Shader;

class Renderer
{
private:
	Renderer(); 

public:
	~Renderer();

public:

	////////////////////
	////Game Section////
	////////////////////

	static void Init();
	static void Shutdown();
	static void Clear();
	static void BeginScene(const glm::vec3& camera, const Shader& shader);
	static void EndScene();
	static void DrawSprite(const Transform& transform, uint32_t spriteIndex);
	static void DrawSprite(EntityManager& em,const Transform& transform, uint32_t spriteIndex);
	static void DrawParticles(); // WIP
	static void Flush();

	/////////////////////
	/////UI Section//////
	/////////////////////

	static void DrawUI(UI* ui);

	/////////////////////
	////////Misc.////////
	/////////////////////

	
	static void SetClearColor(const glm::vec4& color);
	static uint32_t GetNextTextureUnit();
	static bool isTextureBound(uint32_t TextureID);
	static void BindTexture(uint32_t TextureID);
	static Renderer* Get();

private:
	static Renderer* instance;

public:
	std::vector<Vertex> m_vertices;
	std::array<uint32_t,32> m_boundTextures;
	SpriteSheetManager m_ssManager;
	glm::vec3 m_camera;
	uint32_t m_lastTextureSlot;
	uint32_t m_vao, m_vbo,m_ibo;
	uint32_t m_maxBatchSize;

};