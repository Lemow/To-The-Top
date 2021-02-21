#include "GameScene.h"
#include "Headers/Renderer.h"
#include "Headers/Window.h"
#include "Headers/Shader.h"
#include "Headers/Input.h"
#include "Headers/Time.h"
#include "Headers/Components/Rigidbody.h"
#include "Headers/GameLoop.h"
#include "Headers/Components/Texture.h"
#include "Headers/Components/Tag.h"
#include "Headers/Systems/CameraFollowSystem.h"
#include "Headers/Components/Interactable.h"
#include "Headers/Components/Peon.h"
#include "Headers/Systems/InteractSystem.h"
#include "Headers/Systems/ItemPickupSystem.h"
#include "Headers/Components/Item.h"
#include "Headers/Animation.h"
#include "Headers/Systems/PeonOrientationSystem.h"

void GameScene::Start()
{
	player.playerStats = Stats(100,500.0f, 2.0f, 100.0f);
	tile.size = { 100,100 };
	camera = glm::vec3(0, 0, 1);
	shader = Shader("Shaders/vertex.shader", "Shaders/fragment.shader");
	shader.Bind();
	playerEntity = em.Create({0,0}, Tag::Player, { 9 * 5.0f,19 * 5.0f });
	playerEntity.AddComponent<Rigidbody>(Rigidbody::Dynamic);
	playerEntity.AddComponent<Velocity>();
	playerEntity.AddComponent<Texture>(257);
	playerEntity.AddComponent<Peon>();
	map = GenTestMap();
	mapID = em.RegistryCreate();

	glm::vec2 interPos = playerEntity.transform().pos;
	interPos.x += tile.size.x;

	for (int i = 0; i < map.sizeY; i++)
	{
		for (int j = 0; j < map.sizeX; j++)
		{
			if (map[i][j] == Tile::Player)
			{
				Transform& tr = playerEntity.transform();
				tr.pos.x = j * tile.size.x;
				tr.pos.y = i * tile.size.y;
				tr.pos -= Window::GetResolution();

				map[i][j] = Tile::Grass;
			}
			if (map[i][j] == Tile::None )
				continue;
			entity_t Tile = em.RegistryCreate(glm::vec2{ j * tile.size.x, i * tile.size.y } - Window::GetResolution(), Tag::Wall,tile.size);
			em.AddComponent<Texture>(Tile,(int)map[i][j]);
			em.GetComponent<Transform>(Tile).parentID = mapID;
			if (map[i][j] == Tile::Tree)
				em.AddComponent<Rigidbody>(Tile,Rigidbody::Static);
		}
	}

	entity_t inter = em.RegistryCreate(interPos);
	em.AddComponent<Interactable>(inter, [](EntityManager& em, entity_t thisID) 
		{
			entity_t playerID = 0;

			auto iter = em.Iterate<Peon>();

			for (auto it : iter)
			{
				if (em.GetComponent<Tag>(it) == Tag::Player)
				{
					playerID = it;
					break;
				}
			}
			Peon& pe = em.GetComponent<Peon>(playerID);
			Transform& tr = em.GetComponent<Transform>(thisID);
			entity_t item = em.RegistryCreate(tr.pos);
			em.AddComponent<Item>(item, [](EntityManager& em, entity_t playerID)
				{
					std::cout << "Item Equiped by " << playerID << " entity\n";
				});
			em.AddComponent<Texture>(item, (int)Tile::Tree);
			em.AddComponent<Velocity>(item, Velocity(glm::vec2(0,0), -500.0f * CardinalToVec2(pe.orientation)));
			std::cout << "Sayonara... Tomos-san...\n";
			em.Destroy(thisID);
		});
	em.AddComponent<Texture>(inter, (int)Tile::Player);

	Transform& playerTrans = playerEntity.GetComponent<Transform>();
	/*
	
	map = GenMap(80, 80);
	playerTrans.pos.x = playerTrans.pos.y = 0;

	for (int i = 0; i < map.sizeY; i++)
	{
		for (int j = 0; j < map.sizeX; j++)
			if (map[i][j] == Tile::PlayerEntity)
			{
				map[i][j] = Tile::Grass;
				playerTrans.pos.x = j * tile.size.x;
				playerTrans.pos.y = i * tile.size.y;
				i = map.sizeY;
				break;
			}
	}


	tile.size = { 800.0f, 600.0f };
	tile.pos = { 0.0f,0.0f };
	tile.rotation = 0.0f;
	*/
	camera.x = playerTrans.pos.x;
	camera.y = playerTrans.pos.y;

	shader.SetCameraUniform(camera.x, camera.y, camera.z);

}

void GameScene::Update(float dt)
{
	constexpr float speed = 500.0f;
	constexpr int dirX[4] = {0,-1,0,1};
	constexpr int dirY[4] = {1,0,-1,0};
	constexpr float maxZoom = 5.0f;
	constexpr float minZoom = 1.0f;
	Velocity& playerVel = playerEntity.GetComponent<Velocity>();
	Transform& playerTrans = playerEntity.GetComponent<Transform>();
	Peon& playerPeon = playerEntity.GetComponent<Peon>();
//	if (Input::GetGamepadButton(GamepadButton::X) == KeyState::KeyRelease)
//	{
//		std::cout << "bonk";
//	}
//	camera.x += Input::GetGamepadAxis(GamepadAxis::LeftX) * speed * dt * camera.z;
//	camera.y -= Input::GetGamepadAxis(GamepadAxis::LeftY) * speed * dt * camera.z;
//	camera.z += Input::GetGamepadAxis(GamepadAxis::LT) * speed/1000.0f * dt * camera.z;
//	camera.z -= Input::GetGamepadAxis(GamepadAxis::RT) * speed/1000.0f * dt * camera.z;
	//camera.z = std::clamp(camera.z,0.1f, 100000.0f);

	if (Input::GetKey(Key::RightMB) == KeyState::KeyHold)
		camera.z = std::clamp(camera.z + camera.z * speed / 500.0f * dt, minZoom, maxZoom);
	else camera.z = std::clamp(camera.z + camera.z * speed / 500.0f * dt * Input::GetGamepadAxis(GamepadAxis::RT), minZoom, maxZoom);

	if (Input::GetKey(Key::LeftMB) == KeyState::KeyHold)
		camera.z = std::clamp(camera.z - camera.z * speed / 500.0f * dt, minZoom, maxZoom);
	else camera.z = std::clamp(camera.z - camera.z * speed / 500.0f * dt * Input::GetGamepadAxis(GamepadAxis::LT), minZoom, maxZoom);


	playerVel.tv.x = speed * Input::GetGamepadAxis(GamepadAxis::LeftX);
	playerVel.tv.y = -speed * Input::GetGamepadAxis(GamepadAxis::LeftY); 

	bool VertPress = false;

	if (Input::GetKey(Key::W) == KeyState::KeyHold)
	{
		playerVel.tv.y = speed;
		playerPeon.orientation = CardinalDir::N;
		VertPress = true;
	}
	else if (Input::GetKey(Key::S) == KeyState::KeyHold)
	{
		playerVel.tv.y = -speed;
		playerPeon.orientation = CardinalDir::S;
		VertPress = true;
	}

	if (Input::GetKey(Key::D) == KeyState::KeyHold)
	{
		playerVel.tv.x = speed;
		if(VertPress)
			if (playerPeon.orientation == CardinalDir::N)
				playerPeon.orientation = CardinalDir::NE;
			else 
				playerPeon.orientation = CardinalDir::SE;
		else
			playerPeon.orientation = CardinalDir::E;

	}
	else if (Input::GetKey(Key::A) == KeyState::KeyHold)
	{
		playerVel.tv.x = -speed;
		if(VertPress)
			if (playerPeon.orientation == CardinalDir::N)
				playerPeon.orientation = CardinalDir::NW;
			else 
				playerPeon.orientation = CardinalDir::SW;
		else
			playerPeon.orientation = CardinalDir::W;
	}

	if (playerVel.tv.x != 0 && playerVel.tv.y != 0)
	{
		playerVel.tv *= sqrt_2 / 2.0f;
	}


	if (Input::GetKey(Key::E) == KeyState::KeyPress)
	{
		ItemPickupSystem(playerEntity, em, player);
		InteractSystem(playerEntity, em);
	}

	if (Input::GetKey(Key::SPACE) == KeyState::KeyPress || Input::GetGamepadButton(GamepadButton::A) == KeyState::KeyPress)
	{
		map = GenMap(map.sizeX, map.sizeY);
		for (entity_t ent : em.Iterate<Tag>())
		{
			if (em.GetComponent<Tag>(ent) == Tag::Wall)
				em.Destroy(ent);
		}
		for (int i = 0; i < map.sizeY; i++)
		{
			for (int j = 0; j < map.sizeX; j++)
			{
				if (map[i][j] == Tile::Player)
				{
					Transform& tr = playerEntity.transform();
					tr.pos.x = j * tile.size.x;
					tr.pos.y = i * tile.size.y;
					tr.pos -= Window::GetResolution();

					map[i][j] = Tile::Grass;
				}
				if (map[i][j] == Tile::None)
					continue;
				entity_t Tile = em.RegistryCreate(glm::vec2{ j * tile.size.x, i * tile.size.y } - Window::GetResolution(), Tag::Wall, tile.size);
				em.AddComponent<Texture>(Tile, (int)map[i][j]);
				em.GetComponent<Transform>(Tile).parentID = mapID;
				if (map[i][j] == Tile::Tree)
					em.AddComponent<Rigidbody>(Tile, Rigidbody::Static);
			}
		}
		camera.x = playerTrans.pos.x;
		camera.y = playerTrans.pos.y;
	}
	
	if (Input::GetGamepadButton(GamepadButton::Start) == KeyState::KeyPress || Input::GetKey(Key::MiddleMB) == KeyState::KeyPress)
	{
		Window::Close();
		return;
	}

	uint32_t& tex = playerEntity.GetComponent<Texture>().textureID;
	static bool started = false;
	static TimePoint Start;
	if (Input::GetGamepadButton(GamepadButton::Select) == KeyState::KeyPress || Input::GetKey(Key::E) == KeyState::KeyPress)
	{
		std::tie(tex, Start) = AnimationManager::StartAnimation(AnimationType::PlayerIdle);
		started = true;
	}
	else if (started)
	{
		tex = AnimationManager::ContinueAnimation(AnimationType::PlayerIdle, Start);
	}

	CollisionSystem(em);
	VelocitySystem(em);
	CameraFollowSystem(em, camera, playerEntity);
	OrientationSystem(em);
}

void GameScene::Render(float dt)
{
	const glm::vec2& res = Window::GetResolution();
	Renderer::BeginScene(camera, shader);

	auto iter = em.Iterate<Texture>();

	for (auto sprite : iter)
	{
		if (playerEntity == sprite)
			continue;
		Renderer::DrawSprite(em.GetComponent<Transform>(sprite), em.GetComponent<Texture>(sprite).textureID);
	}
		Renderer::DrawSprite(playerEntity.transform(), playerEntity.GetComponent<Texture>().textureID);

	Renderer::EndScene();

}
