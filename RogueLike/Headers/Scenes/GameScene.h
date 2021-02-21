#pragma once
#include "Headers/Scene.h"
#include "Headers/Map.h"
#include "Headers/Shader.h"
#include "Headers/Transform.h"
#include "Headers/Components/Velocity.h"
#include "Headers/Entity.h"
#include "Headers/EntityManager.h"
#include "Headers/Components/Player.h"

class GameScene : public Scene
{
public:
	void Start() override;
	void Update(float dt) override;
	void Render(float dt) override;


private:
	Map map;
	entity_t mapID;
	EntityManager em;
	Shader shader;
	Transform tile;
	glm::vec3 camera;
	Player player;
	Entity playerEntity;
	Entity col;
};