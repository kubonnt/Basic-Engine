#include <random>
#include <chrono>

#include "core/include/physicsSystem.h"

using namespace ECS;
Coordinator coordinator;

int main()
{
	coordinator.Init();

	coordinator.RegisterComponent<Gravity>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RigidBody>();

	auto physicsSystem = coordinator.RegisterSystem<PhysicsSystem>();

	Signature signature;
	signature.set(coordinator.GetComponentType<Gravity>());
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<RigidBody>());
	coordinator.SetSystemSignature<PhysicsSystem>(signature);

	std::vector<Entity> entities(MAX_ENTITIES);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.f, 100.f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);

	for (auto& entity : entities)
	{
		entity = coordinator.CreateEntity();

		coordinator.AddComponent(entity, Gravity{ 2.0f });
		
		coordinator.AddComponent(entity, RigidBody{ 0.0f, 0.0f });

		coordinator.AddComponent(entity, Transform{randPosition(generator), randPosition(generator), scale});
	}

	float deltaT = 0.0f;

	while (true)
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		physicsSystem->Update(deltaT);
	
		auto stopTime = std::chrono::high_resolution_clock::now();

		deltaT = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
	}
	return 0; 
}