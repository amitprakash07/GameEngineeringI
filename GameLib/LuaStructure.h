#ifndef __LUA_STRUCTURE_H
#define __LUA_STRUCTURE_H

#include "Vector3D.h"
#include <vector>
#include "additionaltypes.h"

namespace LuaUtilityHelper
{
	struct _LuaActor
	{
		char *											id;
		char *											name;
		char *											category;
		char *											gameController;
		myEngine::Vector3D								position;
		myEngine::Vector3D								velocity;
		
		//rendering Settings
		myEngine::Vector3D								spriteSize;
		myEngine::typedefs::RGBA						color;
		
		//physics - collision data
		char *											collisionHandler;
		myEngine::typedefs::BoundingBox					collisionBox;
		std::vector<char*>								collidingWith;
		float											mass;

		
	};
	typedef _LuaActor LuaActor;

	struct _Settings
	{
		size_t level;
		size_t monsterCount;
		char * actorFile;
		char * defaultAIFile;
		char * monsterTexture;
		char * playerTexture;
	};

	typedef _Settings Settings;
}

#endif //__LUA_STRUCTURE_H