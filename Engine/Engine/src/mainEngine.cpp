#include <iostream>

#include "core/include/scene.h"
#include "core/include/sceneView.h"

/*----------------------------------- Simple overview/to do list ---------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
//	ECS:																																																//
//		- !!!DONE!!! it has entities, which are unique identifires																				//
//		- !!!IN PROGRESS!!! it has components, which are plain datatypes whithout behavior 								//
//		- !!!TODO!!! entities can contain zero or more components - they can, but found a few problems 		//
//		- !!!TODO!!! entities can change components dynamically  																					//
//		- !!!TODO!!! it has systems, which are functions matched with entities that have certain 					//
//			           set of components - only system atm is the scene, but that's not the plan  					//
//																																																			//
//																																																			//
//																																																			//
// 																																																			//
//																																																			//
//																																																			//
//																																																			//
//																																																			//
//																																																			//
//																																																			//
//																																																			//
//																																																			//
//																																																			//
//																																																			//
/*------------------------------------------------------------------------------------------------------*/

/*---------------------------- Just for debugging ----------------------------------*/
int main(int argc, char* argv[])
{
	/* End goal is to have smth like this */
	/*
	for (EntityID ent : SceneView<Transform, Shape>(scene))
	{
		doSomeWork();
	}
	*/

	using namespace ECS;
	using namespace MemoryPool::ComponentPool;

	ComponentPool Transform(1);
	ComponentPool Shape(1);
	
	Scene scene;

	for (int i = 0; i < 1; ++i)
	{
		scene.NewEntity();
	}
	auto entityIndex = scene.GetEntityIndex(scene.entities[0].id);

	printf("EntityID: %i\n", static_cast<int>(scene.entities[0].id));
	printf("Entity index: %i\n", static_cast<int>(entityIndex));


}