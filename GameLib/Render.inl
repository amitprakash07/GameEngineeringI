namespace myEngine
{
	namespace Rendering
	{
		myEngine::Vector2D Sprite::getDimension()
		{
			myEngine::Vector2D temp(dimension.x, dimension.y);
			return temp;
		}//getdimension

		void Sprite::setDimension(myEngine::Vector2D i_dimension)
		{
			dimension.x = i_dimension.getX();
			dimension.y = i_dimension.getY();
		}// setdimension

		Cheesy::ColorRGBA Sprite::getColor()
		{
			return color;
		}//getColor

		void Sprite::setColor(Cheesy::ColorRGBA i_color)
		{
			color.a = i_color.a;
			color.b = i_color.b;
			color.g = i_color.g;
			color.r = i_color.r;
		}//setColor

		char * Sprite::getFileName()
		{
			return filename;
		}//getFilename

		Cheesy::Point2D Sprite::getOffset()
		{
			return offset;
		}//getOffset

		void Sprite::setOffset(Vector2D i_offset)
		{
			offset.x = i_offset.getX();
			offset.y = i_offset.getY();
		}//setOffset

		float Sprite::getRotation()
		{
			return rotation;
		}//getRotation

		void Sprite::setRotation(float i_rotation)
		{
			rotation = i_rotation;
		}//setRotation
	}//namespace Rendering
}//namespace myEngine