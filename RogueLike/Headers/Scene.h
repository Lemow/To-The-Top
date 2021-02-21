#pragma once
#include "Tabasco/EntityManager.h"

class Scene
{
	friend class GameLoop;

public:

	virtual void Start() {}
	virtual void Update(float dt) { }
	virtual void Render(float dt) {}

};