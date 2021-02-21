#pragma once
#include "Headers/Scene.h"
#include "Headers/UI.h"


class MainMenuScene : public Scene
{

	MainMenuScene();
	void Update(float dt) override;
	void Render(float dt) override;

private:
	Button startButton;
	Button exitButton;
};

