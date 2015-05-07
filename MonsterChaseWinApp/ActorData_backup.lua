Player = 
{
	name = "Joe",
	class = "Player",
	controller = "InputController",
	initial_position = { 0.0, 0.0, 0.0 },
	initial_velocity = { 0.0, 0.0, 0.0 },
	collision_settings = 
	{
		collision_handler = "PlayerCollision",
		bounding_box = { 
			offset = { 0.0, 0.0, 0.0 },
			size = { 10.0, 10.0, 10.0 }
		} ,
		collides_with = { "Monsters", "Aliens" },
		mass = 2.0
	},
	render_settings = 
	{
		spriteSize = { 20.0, 20.0 },
		spriteColor = { 255, 255, 255, 255 }
	}
}
	
Monsters =
{
	{
		name = "Inky",
		class = "Monster",
		controller = "Wander",
		initial_position = { -20.0, -20.0, 0.0 },

		render_settings = 
		{
			spriteSize = { 20.0, 20.0 },
			spriteColor = { 255, 255, 255, 255 }
		}

	}
}
	