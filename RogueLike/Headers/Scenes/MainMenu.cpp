#include "MainMenu.h"
#include "Headers/Input.h"
#include "Headers/Window.h"

void exitFunc(void* data)
{
	Window::Close();
}


MainMenuScene::MainMenuScene()
	:startButton(0, Transform{ glm::vec2(),glm::vec2()}, 1, 2,nullptr),
	exitButton(3, Transform{ glm::vec2(),glm::vec2()}, 4, 5, nullptr)
{
}

void MainMenuScene::Update(float dt)
{
	glm::vec2 mousePos = Input::GetMousePos();
	startButton.isHighlighted = startButton.isHovering(mousePos.x,mousePos.y);
	exitButton.isHighlighted = exitButton.isHovering(mousePos.x,mousePos.y);

	if (Input::GetKey(Key::LeftMB) == KeyState::KeyPress)
	{
		startButton.OnClick(nullptr);
		exitButton.OnClick(nullptr);
	}
}

void MainMenuScene::Render(float dt)
{
}
