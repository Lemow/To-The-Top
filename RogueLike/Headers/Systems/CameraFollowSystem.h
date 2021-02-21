#pragma once
#include <Tabasco/EntityManager.h>
#include "Headers/EntityManager.h"
#include "Headers/Entity.h"
#include <glm/glm.hpp>

void CameraFollowSystem(EntityManager& em, glm::vec3& camera, Entity& toFollow);
