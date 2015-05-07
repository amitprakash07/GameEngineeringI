Player = 
{
	name = "Joe",
	class = "Player",
	controller = "walk",
	initial_position = { 0.0, 0.0, 0.0 },
	initial_velocity = { 0.0, 0.0, 0.0 },
	collision_settings = 
	{
		collision_handler = "PlayerCollision",
		bounding_box = { 
			offset = { 0.0, 0.0, 0.0 },
			size = { 5.0, 5.0, 5.0 }
		} ,
		collides_with = { "Monsters", "Aliens" },
		mass = 2.0
	},
	render_settings = 
	{
		spriteSize = { 50.0, 50.0 },
		spriteColor = { 255, 255, 255, 255 }
	}
}
	
Monsters =
{
	{
		name = "Inky",
		class = "Monster",
		controller = "static",
		initial_position = { -250.0, -250.0, 0.0 },
		collision_settings = 
		{
			bounding_box = { 
				offset = { 0.0, 0.0, 0.0 },
				size = { 5.0, 5.0, 5.0 }	
			} ,
		collides_with = { "Monsters", "Aliens" },
		mass = 2.0
		},
		render_settings = 
		{
			spriteSize = { 50.0, 50.0 },
			spriteColor = { 255, 255, 255, 255 }
		}

	}
--	,
--
--	{
--		name = "Binky",
--		class = "Monster",
--		controller = "StaticController",
--		initial_position = {  250.0, 250.0, 0.0 },
--		collision_settings = 
--		{
--			bounding_box = { 
--				offset = { 0.0, 0.0, 0.0 },
--				size = { 5.0, 5.0, 5.0 }
--			} ,
--		collides_with = { "Monsters", "Aliens" },
--		mass = 2.0
--		},
--		render_settings = 
--		{
--			spriteSize = { 50.0, 50.0 },
--			spriteColor = { 255, 255, 255, 255 }
--		}
--	},
--	
--	{
--		name = "Pinky",
--		class = "Monster",
--		controller = "staticcontroller",
--		initial_position = {  250.0, -250.0, 0.0 },
--		collision_settings = 
--		{
--			bounding_box = { 
--				offset = { 0.0, 0.0, 0.0 },
--				size = { 5.0, 5.0, 5.0 }
--			} ,
--		collides_with = { "Monsters", "Aliens" },
--		mass = 2.0
--		},
--		render_settings = 
--		{
--			spriteSize = { 50.0, 50.0 },
--			spriteColor = { 255, 255, 255, 255 }
--		}
--	},
--
--	{
--		name = "Clyde",
--		class = "Monster",
--		controller = "static",
--		initial_position = {  -250.0, 250.0, 0.0 },
--		collision_settings = 
--		{
--			bounding_box = { 
--				offset = { 0.0, 0.0, 0.0 },
--				size = { 5.0, 5.0, 5.0 }
--			} ,
--		collides_with = { "Monsters", "Aliens" },
--		mass = 2.0
--		},
--		render_settings = 
--		{
--			spriteSize = { 50.0, 50.0 },
--			spriteColor = { 255, 255, 255, 255 }
--		}
--	}
}
	