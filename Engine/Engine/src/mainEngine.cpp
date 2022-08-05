#include <iostream>

#include "core/include/scene.h"
#include "core/include/sceneView.h"

/*----------------------------------- Simple overview/to do list -----------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
//	ECS:																																																										//
//		- !!!DONE!!! it has entities, which are unique identifires																														//
//		- !!!IN PROGRESS!!! it has components, which are plain datatypes whithout behavior 																		//
//		- !!!TODO!!! entities can contain zero or more components - they can, but found a few problems 												//
//		- !!!TODO!!! entities can change components dynamically  																															//
//		- !!!TODO!!! it has systems, which are functions matched with entities that have certain 															//
//			           set of components - only system atm is the scene, but that's not the plan  															//
//		-	!!! TODO: FIX !!! When assigning the component, for example TransformComponent it 																	//															
// 			                  can't see it and I get unresolved external symbol																									//
//																																																													//
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

	for (int i = 0; i < 2; ++i)
	{
		scene.NewEntity();
		scene.AssignComponent<TransformComponent>(scene.entities[0].id);
		for (auto ent : SceneView<TransformComponent>(scene))
		{
			printf("TransformComponentID: %i\n", GetId<TransformComponent>());
			// world.place(ent);
		}
	}

	printf("EntityID: %i\n", static_cast<int>(scene.GetEntityIndex(scene.entities[0].id)));
	printf("EntityID: %i\n", static_cast<int>(scene.GetEntityIndex(scene.entities[1].id)));
}