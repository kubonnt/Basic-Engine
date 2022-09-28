#include <iostream>
#include <thread>

#include "core/include/scene.h"
#include "core/include/sceneView.h"

/*----------------------------------- Simple overview/to do list -----------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
//	ECS:																																																										//
//		- !!!IN PROGRESS!!! it has components, which are plain datatypes whithout behavior                                    //
//																																																													//
//		- !!!TODO!!! entities can change components dynamically  																															//
//																																																													//
//		- !!!TODO!!! it has systems, which are functions matched with entities that have certain 															//
//			           set of components - only system atm is the scene 																                        //
//																																																													//
//		-	!!!TODO!!! more memory safe,	there probably is a memory leak - try to change raw ptrs into smart ones							//
//																																																													//
// 																																																													//
//																																																													//
//																																																													//
//																																																													//
//																																																													//
//																																																													//
//																																																													//
//																																																													//
//																																																													//
//																																																													//
//																																																													//
/*--------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------- Just for debugging ----------------------------------*/
int main(int argc, char* argv[])
{
	using namespace ECS;
	using namespace MemoryPool::ComponentPool;
	
	Scene scene;

	scene.NewEntity();
	scene.NewEntity();
	scene.AssignComponent<TransformComponent>(scene.GetEntityIndex(scene.entities[0].id));
	scene.AssignComponent<AnotherComponent>(scene.GetEntityIndex(scene.entities[1].id));

	printf("TransformComponentID: %i\n", GetId<TransformComponent>());
	printf("AnotherComponentID: %i\n", GetId<AnotherComponent>());

	printf("Entity %i\n", scene.GetEntityIndex(scene.entities[0].id));
	printf("Entity %i\n", scene.GetEntityIndex(scene.entities[1].id));

	scene.DestroyEntity(1); 
	scene.GetComponent<AnotherComponent>(1);
	printf("Entity %i\n", scene.GetEntityIndex(scene.entities[1].id)); 

	return 0;
}