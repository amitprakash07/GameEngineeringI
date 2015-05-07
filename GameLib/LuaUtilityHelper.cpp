#include "LuaUtilityHelper.h"
#include "IGameObjectController.h"

namespace LuaUtilityHelper
{
	bool getAsVector3D(LuaPlus::LuaObject i_luaObject, myEngine::Vector3D &o_vector)
	{
		if (!i_luaObject.IsNil())
		{
			for (size_t i = 1; i <= i_luaObject.GetCount(); i++)
			{
				switch (i)
				{
				case 1:
					o_vector.setX(i_luaObject[1].GetFloat());
					break;
				case 2:
					o_vector.setY(i_luaObject[2].GetFloat());
					break;
				case 3:
					o_vector.setZ(i_luaObject[3].GetFloat());
					break;
				}
			}
			return true;
		}	

		return false;		
	}

	bool getAsVector3D(LuaPlus::LuaObject i_luaObject, unsigned __int16 &o_width, unsigned __int16 &o_height, unsigned __int16 &o_depth)
	{
		if (!i_luaObject.IsNil())
		{
			for (size_t i = 1; i <= i_luaObject.GetCount(); i++)
			{
				switch (i)
				{
				case 1:
					o_width = static_cast<unsigned __int16> (i_luaObject[1].GetFloat());
					break;
				case 2:
					o_height = static_cast<unsigned __int16> (i_luaObject[2].GetFloat());
					break;
				case 3:
					o_depth = static_cast<unsigned __int16> (i_luaObject[3].GetFloat());
					break;
				}
			}
			return true;
		}

		return false;
	}



	bool getAsRGBA(LuaPlus::LuaObject i_luaObject, myEngine::typedefs::RGBA &o_color)
	{
		if (!i_luaObject.IsNil())
		{
			for (size_t i = 1; i <= i_luaObject.GetCount(); i++)
			{
				switch (i)
				{
				case 1:
					o_color.R = static_cast<unsigned char>(i_luaObject[1].GetInteger());
					break;
				case 2:
					o_color.G = static_cast<unsigned char>(i_luaObject[2].GetInteger());
					break;
				case 3:
					o_color.B = static_cast<unsigned char>(i_luaObject[3].GetInteger());
					break;
				case 4:
					o_color.A = static_cast<unsigned char>(i_luaObject[4].GetInteger());
					break;
				}
			}
			return true;
		}
		return false;
	}

	
	bool getGlobalLuaObject(const char * i_filename, const char* i_global, LuaPlus::LuaObject &o_luaObject)
	{
		LuaPlus::LuaState *pState = LuaPlus::LuaState::Create();
		if (pState && (pState->DoFile(i_filename)==0))
		{
			o_luaObject = static_cast<LuaPlus::LuaObject>(pState->GetGlobal(i_global));
			return true;
		}

		return false;
	}//end function



	bool getGameSettings(LuaPlus::LuaObject luaSettings, LuaUtilityHelper::Settings &o_settings)
	{
			if (luaSettings.IsTable())
			{
				if (!luaSettings["Level"].IsNil() && luaSettings["Level"].IsNumber())
					o_settings.level = static_cast<int>(luaSettings["Level"].GetNumber());

				if (!luaSettings["MonsterCount"].IsNil() && luaSettings["MonsterCount"].IsNumber())
					o_settings.monsterCount = static_cast<int>(luaSettings["MonsterCount"].GetNumber());

				if (!luaSettings["ActorFile"].IsNil() && luaSettings["ActorFile"].IsString())
					o_settings.actorFile = const_cast<char*>(luaSettings["ActorFile"].GetString());

				if (!luaSettings["DefaultAIChar"].IsNil() && luaSettings["DefaultAIChar"].IsString())
					o_settings.defaultAIFile = const_cast<char*>(luaSettings["DefaultAIChar"].GetString());

				if (!luaSettings["PlayerTexture"].IsNil() && luaSettings["PlayerTexture"].IsString())
					o_settings.playerTexture = const_cast<char*>(luaSettings["PlayerTexture"].GetString());

				if (!luaSettings["MonsterTexture"].IsNil() && luaSettings["MonsterTexture"].IsString())
					o_settings.monsterTexture = const_cast<char*>(luaSettings["MonsterTexture"].GetString());

				return true;
			}//end if
		return false;
	}//end function



	//needs to be called with an iterator
	bool getLuaActor(LuaPlus::LuaObject i_luaGameObject,LuaUtilityHelper::LuaActor &o_lActor)
	{
				if (i_luaGameObject.IsTable()) //if-Table
				{
					if (!i_luaGameObject["id"].IsNil() && i_luaGameObject["id"].IsString())
						o_lActor.id = const_cast<char *> (i_luaGameObject["id"].GetString());

					if (!i_luaGameObject["name"].IsNil() && i_luaGameObject["name"].IsString())
						o_lActor.name = const_cast<char*>(i_luaGameObject["name"].GetString());

					if (!i_luaGameObject["class"].IsNil() && i_luaGameObject["class"].IsString())
						o_lActor.category = const_cast<char*>(i_luaGameObject["class"].GetString());
					
					if (!i_luaGameObject["controller"].IsNil() && i_luaGameObject["controller"].IsString())
						o_lActor.gameController = const_cast<char *>(i_luaGameObject["controller"].GetString());

					if (!i_luaGameObject["initial_position"].IsNil())
						LuaUtilityHelper::getAsVector3D(i_luaGameObject["initial_position"], o_lActor.position);

					if (!i_luaGameObject["initial_velocity"].IsNil())
						LuaUtilityHelper::getAsVector3D(i_luaGameObject["initial_velocity"], o_lActor.velocity);

					
					//Collision and Physics Data
					if (!i_luaGameObject["collision_settings"].IsNil())
					{
						LuaPlus::LuaObject collisionSettings = i_luaGameObject["collision_settings"];
						
						if (!collisionSettings["collision_handler"].IsNil() && collisionSettings["collision_handler"].IsString())
							o_lActor.collisionHandler = const_cast<char*>(collisionSettings["collision_handler"].GetString());

						LuaPlus::LuaObject bounding_box = collisionSettings["bounding_box"];
						if (!bounding_box.IsNil() && bounding_box.IsTable())
						{
							LuaUtilityHelper::getAsVector3D(bounding_box["offset"], o_lActor.collisionBox.position);
							LuaUtilityHelper::getAsVector3D(bounding_box["size"], o_lActor.collisionBox.width, o_lActor.collisionBox.height, o_lActor.collisionBox.depth);
						}

						LuaPlus::LuaObject colliders = collisionSettings["collides_with"];
						
						if (!colliders.IsNil() && colliders.IsTable())
						{
							for (size_t i = 1; i <= colliders.GetCount(); i++)
								o_lActor.collidingWith.push_back(const_cast<char*>(colliders[i].GetString()));
						}

						if (!collisionSettings["mass"].IsNil() && collisionSettings["mass"].IsNumber())
							o_lActor.mass = static_cast<float>(collisionSettings["mass"].GetNumber());
					}


					//Rendering Data
					if (!i_luaGameObject["render_settings"].IsNil())
					{
						LuaPlus::LuaObject renderSettings = i_luaGameObject["render_settings"];

						if (renderSettings.IsTable())
						{

							if (!renderSettings["spriteSize"].IsNil())
								LuaUtilityHelper::getAsVector3D(renderSettings["spriteSize"], o_lActor.spriteSize);

							if (!renderSettings["spriteColor"].IsNil())
								LuaUtilityHelper::getAsRGBA(renderSettings["spriteColor"], o_lActor.color);
						}
					}

						
					return true;
				}//end if - Table
		return false;

	} //end function
} //end namespace uaUtilityHelper