Defaults = 
{
	id = "Unknown",
	name = "Unknown", 
	class = "Unknown",
	-- controller defaults to NULL
	initial_position = { 0.0, 0.0, 0.0 },
	initial_velocity = { 0.0, 0.0, 0.0 },
	render_settings = 
	{
		sprite_size = { 10.0, 10.0, 1.0 },
		sprite_color = { 255, 0, 0, 255 } -- R, G, B, A
	},
	collision_settings = 
	{
		-- collision_handler defaults to NULL
		bounding_box = {
			offset = { 0.0, 0.0, 0.0 },
			size = { 10.0, 10.0, 10.0 }
		} ,
		-- collides_with defaults to empty set
		mass = 10.0
	}	
}