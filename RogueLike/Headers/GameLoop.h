#pragma once

class Scene;

class GameLoop
{
public:

	static void Init(Scene* scene);
	static void Shutdown();
	static void Loop();
	static void SwitchScene(Scene* scene);

private:

	static Scene* m_activeScene;
};