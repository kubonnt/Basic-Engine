#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "../include/components.h"
#include "../include/entity.h"
#include "../include/system.h"

using namespace ECS;
Coordinator gCoordinator;

struct Gravity
{
	float force;
};

struct RigidBody
{
	float velocity;
	float acceleration;
};

struct Transform
{
	float position;
	float rotation;
	float scale;
};

class PhysicsSystem : public System
{
public:
	void Update(float deltaTime);
};

void PhysicsSystem::Update(float deltaTime)
{
	for (auto const& entity : m_entities)
	{
		auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);

		transform.position += rigidBody.velocity * deltaTime;

		rigidBody.velocity += gravity.force * deltaTime;
	}
};

#endif // !PHYSICS_SYSTEM_H

