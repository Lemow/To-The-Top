#include <iostream>
#include <GL/glew.h>
#include <chrono>
#include "Headers/Window.h"
#include "Headers/Renderer.h"
#include "Headers/Shader.h"
#include "Headers/Sprite.h"
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include "Headers/Input.h"
#include "Headers/Map.h"
#include "Headers/Random.h"
#include "Headers/Time.h"
#include <unordered_set>
#include "Headers/GameLoop.h"
#include "Headers/Scenes/GameScene.h"

int main()
{
	GameScene testScene;
	GameLoop::Init(&testScene);
	GameLoop::Loop();

	glfwTerminate();
	return 0;
}


	/*
	Time::Init();
	Random::Init();
	Window::Init("Wondow", {1920,1080});
	Renderer::Init();
	Transform tile;

	glm::vec3 camera(0, 0, 1);
	Shader shader("Shaders/vertex.shader", "Shaders/fragment.shader");
	shader.Bind();

	Map map = GenMap(333, 333);
	glm::uvec2 player(0, 0);

	for (int i = 0; i < map.sizeY; i++)
	{
		for (int j = 0; j < map.sizeX; j++)
			if (map[i][j] == Tile::Player)
			{
				map[i][j] = Tile::Grass;
				player.x = j;
				player.y = i;
				i = map.sizeY;
				break;
			}
	}


	tile.size = { 800.0f, 600.0f };
	tile.pos = { 0.0f,0.0f };
	tile.rotation = 0.0f;

	camera.x = (player.x - 1) * tile.size.x;
	camera.y = (player.y + 1) * tile.size.y;

	shader.SetCameraUniform(camera.x, camera.y, camera.z);


	while (Window::IsRunning())
	{
		constexpr float speed = 2000.0f;
		Time::Step();
		float dt = Time::DeltaTime();

		if (Input::GetKey(Key::RightMB) == KeyState::KeyHold)
			camera.z = std::clamp(camera.z + camera.z * speed / 500.0f * dt, 0.01f, 10000.0f);
		if (Input::GetKey(Key::LeftMB) == KeyState::KeyHold)
			camera.z = std::clamp(camera.z - camera.z * speed / 500.0f * dt, 0.01f, 10000.0f);

		bool mid = Input::GetKey(Key::MiddleMB) == KeyState::KeyHold;
		if (mid)
		{
			if (Input::GetKey(Key::W) == KeyState::KeyHold)
			{
				camera.y += speed * Time::DeltaTime() * camera.z;
			}
			if (Input::GetKey(Key::S) == KeyState::KeyHold)
			{
				camera.y -= speed * Time::DeltaTime() * camera.z;
			}
			if (Input::GetKey(Key::A) == KeyState::KeyHold)
			{
				camera.x -= speed * Time::DeltaTime() * camera.z;
			}
			if (Input::GetKey(Key::D) == KeyState::KeyHold)
			{
				camera.x += speed * Time::DeltaTime() * camera.z;
			}
		}
		else
		{
			if (Input::GetKey(Key::W) == KeyState::KeyHold)
			{
				if (player.y < map.sizeY - 1)
					if (map[player.y + 1][player.x] == Tile::Grass)
						player.y++;
			}
			if (Input::GetKey(Key::S) == KeyState::KeyHold)
			{
				if (player.y > 0)
					if (map[player.y - 1][player.x] == Tile::Grass)
						player.y--;
			}
			if (Input::GetKey(Key::A) == KeyState::KeyHold)
			{
				if (player.x > 0)
					if (map[player.y][player.x - 1] == Tile::Grass)
						player.x--;
			}
			if (Input::GetKey(Key::D) == KeyState::KeyHold)
			{
				if (player.x < map.sizeX - 1)
					if (map[player.y][player.x + 1] == Tile::Grass)
						player.x++;
			}
		}





		if (Input::GetKey(Key::SPACE) == KeyState::KeyPress)
		{
			map = GenMap(map.sizeX, map.sizeY);
			for (int i = 0; i < map.sizeY; i++)
			{
				for (int j = 0; j < map.sizeX; j++)
					if (map[i][j] == Tile::Player)
					{
						map[i][j] = Tile::Grass;
						player.x = j;
						player.y = i;
						i = map.sizeY;
						break;
					}
			}
			camera.x = (player.x - 1) * tile.size.x;
			camera.y = (player.y + 1) * tile.size.y;
		}

		const glm::vec2& res = Window::GetResolution();
		Renderer::Clear();
		Renderer::BeginScene(camera, shader);

		for (int i = 0; i < map.sizeY; i++)
		{
			for (int j = 0; j < map.sizeX; j++)
			{
				if (map[i][j] == Tile::None)// || abs((int)player.x - (int)j) > 5 || abs((int)player.y - (int)i) > 5)
					continue;
				tile.pos = glm::vec2(j * tile.size.x, i * tile.size.y) - glm::vec2(res.x, -res.y) / 2.0f;
				Renderer::DrawSprite(tile, (uint32_t)map[i][j]);
			}
		}

		tile.pos = glm::vec2(player.x * tile.size.x, player.y * tile.size.y) - glm::vec2(Window::GetResolution().x, -Window::GetResolution().y) / 2.0f;
		Renderer::DrawSprite(tile, (uint32_t)Tile::Player);

		Renderer::EndScene();
		Window::SwapBuffers();
		Input::ScanKeys();

	}
	*/ // unrolled Game Loop

