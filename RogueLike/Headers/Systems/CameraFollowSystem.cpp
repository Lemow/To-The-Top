#include "CameraFollowSystem.h"
#include "Headers/Components/Velocity.h"
#include "Headers/Transform.h"
#include "Headers/Time.h"
#include "Headers/Math.h"
#include "Headers/Input.h"

void CameraFollowSystem(EntityManager& em, glm::vec3& camera, Entity& toFollow)
{
	constexpr float smoothSpeed = 10.0f;
	//glm::vec3& cameraTrans = em.GetComponent<glm::vec3>(camera);
	Transform& toFollowTrans = toFollow.GetComponent<Transform>();
	Velocity& toFollowVel = toFollow.GetComponent<Velocity>();

	camera.x = lerp(camera.x, toFollowTrans.pos.x, Time::DeltaTime() * smoothSpeed);
	camera.y = lerp(camera.y, toFollowTrans.pos.y, Time::DeltaTime() * smoothSpeed);

}
