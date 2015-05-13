#ifndef __TYPES_H
#define __TYPES_H

namespace Cheesy
{

struct Point2D
{
	float						x, y;

	Point2D()
	{}

	Point2D( float i_x, float i_y ) :
		x( i_x ),
		y( i_y )
	{}
} ;
typedef Point2D Point2D;

struct ColorRGB
{
	unsigned char				r, g, b;
	
	ColorRGB()
	{}

	ColorRGB( unsigned char i_r, unsigned char i_g, unsigned char i_b ) :
		r( i_r ),
		g( i_g ),
		b( i_b )
	{}
} ;
typedef ColorRGB ColorRGB;

struct ColorRGBA
{
	unsigned char				r, g, b, a;

	ColorRGBA()
	{}

	ColorRGBA( unsigned char i_r, unsigned char i_g, unsigned char i_b, unsigned char i_a ) :
		r( i_r ),
		g( i_g ),
		b( i_b ),
		a( i_a )
	{}
} ;
typedef ColorRGBA ColorRGBA;

struct UV
{
	float						u, v;

	UV()
	{}

	UV( float i_u, float i_v ) :
		u( i_u ),
		v( i_v )
	{}
};
typedef UV UV;

typedef struct UV UVSet[4];

} // namespace Cheesy

#endif // __TYPES_H
