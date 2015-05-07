#ifndef __WORLD_SCENE_H
#define __WORLD_SCENE_H

#include "SharedPointer.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Cheesy.h"
#include "CheesyHelper.h"


//Singleton
namespace myEngine
{
	class World
	{
	public:

		static World*													getWorld();
		void															deleteWorld();
		void															createGameObjects(char *);
		void															addToWorld(SharedPointer<GameObject> &);
		void															updateWorld();
		LuaUtilityHelper::Settings										getGameConfiguration();
		SharedPointer<GameObject>										getNearestGameObject(Vector3D);
		SharedPointer<GameObject>										getNearestGameObjectWithPointer(Vector3D);
		bool															isInitialized();
		std::vector<SharedPointer<GameObject>>							getGameObjectList();
		
		//T0-Dos
		bool															removeFromWorld(SharedPointer<GameObject>&); //To Do
		char*															getGameName() const;
		void															setGameName(char*);
		myEngine::typedefs::RGBA										getWindowColor() const;
		void															setWindowColor(myEngine::typedefs::RGBA);
		Vector2D														getWindowSize() ;
		void															setWindowSize(Vector2D);

		
	private:

		World();		
		static World*													mWorld;
		std::vector<SharedPointer<GameObject>>							mGameObjectList;
		LuaUtilityHelper::Settings										gameConfiguration;
		char *															mGameName;
		Vector2D														mGameWindow;
		myEngine::typedefs::RGBA										mGameWindowColor;
		World(World&);
		World(World*);
		World operator = (World);
		//static bool														initialized;
		

	}; //world
}//namespace myEngine

#endif //__WORLD_SCENE_H