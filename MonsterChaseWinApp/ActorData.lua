Player = 
{
	name = "Joe",
	class = "Player",
	controller = "walk",
	initial_position = { 0.0, 0.0, 0.0 },
	initial_velocity = { 0.0, 0.0, 0.0 },
	collision_settings = 
	{
		collision_handler = "Default",
		bounding_box = { 
			offset = { 0.0, 0.0, 0.0 },
			size = { 45.0, 45.0, 45.0 }	
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
		controller = "wander",
		initial_position = { -550.0, -350.0, 0.0 },
		collision_settings = 
		{
			collision_handler = "Default",
			bounding_box = { 
				offset = { 0.0, 0.0, 0.0 },
				size = { 45.0, 45.0, 45.0 }	
			} ,
		collides_with = { "Monsters", "Aliens" },
		mass = 2.0
		},
		render_settings = 
		{
			spriteSize = { 50.0, 50.0 },
			spriteColor = { 255, 255, 255, 255 }
		}

	},

	{
		name = "Binky",
		class = "Monster",
		controller = "wander",
		initial_position = {  700.0, 100.0, 0.0 },
		collision_settings = 
		{
			collision_handler = "Default",
			bounding_box = { 
				offset = { 0.0, 0.0, 0.0 },
				size = { 45.0, 45.0, 45.0 }	
			} ,
		collides_with = { "Monsters", "Aliens" },
		mass = 2.0
		},
		render_settings = 
		{
			spriteSize = { 50.0, 50.0 },
			spriteColor = { 255, 255, 255, 255 }
		}
	},
	
	{
		name = "Pinky",
		class = "Monster",
		controller = "wander",
		initial_position = {  100, -250.0, 0.0 },
		collision_settings = 
		{
			collision_handler = "Default",
			bounding_box = { 
				offset = { 0.0, 0.0, 0.0 },
				size = { 45.0, 45.0, 45.0 }	
			} ,
		collides_with = { "Monsters", "Aliens" },
		mass = 2.0
		},
		render_settings = 
		{
			spriteSize = { 50.0, 50.0 },
			spriteColor = { 255, 255, 255, 255 }
		}
	},

	{
		name = "Clyde",
		class = "Monster",
		controller = "wander",
		initial_position = {  -250.0, 20.0, 0.0 },
		collision_settings = 
		{
			collision_handler = "Default",
			bounding_box = { 
				offset = { 0.0, 0.0, 0.0 },
				size = { 45.0, 45.0, 45.0 }	
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
}
	