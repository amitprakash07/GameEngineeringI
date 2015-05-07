#ifndef __LUAHELPER_H
#define __LUAHELPER_H

#include "LuaPlus.h"
#include "Vector3D.h"
#include "additionaltypes.h"
#include "LuaStructure.h"
#include <assert.h>


namespace LuaUtilityHelper
{
	bool		getAsRGBA(LuaPlus::LuaObject, myEngine::typedefs::RGBA&);
	bool		getAsVector3D(LuaPlus::LuaObject, myEngine::Vector3D&);
	bool		getGlobalLuaObject(const char *, const char* , LuaPlus::LuaObject &);
	bool		getGameSettings(LuaPlus::LuaObject, LuaUtilityHelper::Settings &o_settings);
	bool		getLuaActor(LuaPlus::LuaObject i_luaGameObject, LuaUtilityHelper::LuaActor &o_lActor);
}

#endif //__LUAHELPER_H