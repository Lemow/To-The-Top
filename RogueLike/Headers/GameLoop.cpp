#include "GameLoop.h"
#include "Window.h"
#include "Renderer.h"
#include "Scene.h"
#include <chrono>
#include "Time.h"
#include "Random.h"
#include "Input.h"
#include "Animation.h"

Scene* GameLoop::m_activeScene = nullptr;

void GameLoop::Loop()
{
	while (Window::IsRunning())
	{
		Time::Step();

		m_activeScene->Update(Time::DeltaTime());
		Renderer::Clear();
		m_activeScene->Render(Time::DeltaTime());
		Window::SwapBuffers();
		Input::ScanKeys();
	}
	GameLoop::Shutdown();

}

void GameLoop::SwitchScene(Scene* scene)
{
	GameLoop::m_activeScene = scene;
	scene->Start();
}

void GameLoop::Init(Scene* scene)
{
	Time::Init();
	Random::Init();
	AnimationManager::Init();
	Window::Init("Test", { 1920,1080 });
	Renderer::Init();
	SwitchScene(scene);
}

void GameLoop::Shutdown()
{
	GameLoop::m_activeScene = nullptr;
	Renderer::Shutdown();
	Window::Shutdown();
}
