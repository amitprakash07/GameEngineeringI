#ifndef __WORLD_SCENE_H
#define __WORLD_SCENE_H

#include "SharedPointer.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Cheesy.h"
#include "CheesyHelper.h"
#include "IMessageHandler.h"


//Singleton
namespace myEngine
{
	class World:myEngine::IMessageHandler
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
		SharedPointer<GameObject>										getPlayer();
		bool															isInitialized();
		std::vector<SharedPointer<GameObject>>							getGameObjectList();
		bool															inWorld(SharedPointer<GameObject>&, unsigned __int16 &);
		
		//T0-Dos
		bool															removeFromWorld(SharedPointer<GameObject>&); //To Do
		char*															getGameName() const;
		void															setGameName(char*);
		myEngine::typedefs::RGBA										getWindowColor() const;
		void															setWindowColor(myEngine::typedefs::RGBA);
		Vector2D														getWindowSize() ;
		void															setWindowSize(Vector2D);

		void															HandleMessage(myEngine::utils::StringHash &, void *i_MessageSender, void* i_pMessageData) override;

		
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
		~World();
		//static bool														initialized;
		

	}; //world
}//namespace myEngine

#endif //__WORLD_SCENE_H