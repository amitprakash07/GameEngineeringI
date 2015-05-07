
namespace myEngine
{
	namespace Maths
	{
		/** <summary>
		* Use as matrix looks like
		* a b
		* c d
		* </summary>
		*/
		inline float getDeterminant2x2(
			const float a, const float b, 
			const float c, const float d) 
		{
			return((a*d) - (b*c));
		}


		/** <summary>
		* Use as column major ie matrix looks like
		* a b c
		* d e f
		* g h i
		* </summary>
		*/
		inline float getDeterminant3x3(
			const float a, const float b, const float c,
			const float d, const float e, const float f,
			const float g, const float h, const float i)
		{
#ifdef _ENGINE_DEBUG
			std::cout << a << "\t" << b << "\t" << c << "\n";
			std::cout << d << "\t" << e << "\t" << f << "\n";
			std::cout << g << "\t" << h << "\t" << i << "\n";
			std::cout << "And determinant is " << (a* myEngine::Maths::getDeterminant2x2(e, f, h, i))
				- (b* myEngine::Maths::getDeterminant2x2(d, f, g, i))
				+ (c* myEngine::Maths::getDeterminant2x2(d, e, g, h)) << std::endl << std::endl;
			
#endif
			return(
				  (a* myEngine::Maths::getDeterminant2x2(e,f,h,i))
				- (b* myEngine::Maths::getDeterminant2x2(d,f,g,i))
				+ (c* myEngine::Maths::getDeterminant2x2(d,e,g,h))
				);
		}


		/** <summary>
		* Use as column major ie matrix looks like
		* a b c d
		* e f g h
		* i j k l
		* m n o p
		* </summary>
		*/

		inline float getDerteminant4x4(
			const float a, const float b, const float c, const float d,
			const float e, const float f, const float g, const float h,
			const float i, const float j, const float k, const float l,
			const float m, const float n, const float o, const float p)
		{
			return(
				  (a* getDeterminant3x3(f,g,h,		j,k,l,		n,o,p))
				- (e* getDeterminant3x3(b,c,d,		j,k,l,		n,o,p))
				+ (i* getDeterminant3x3(b,c,d,		f,g,h,		n,o,p))
				- (m* getDeterminant3x3(b,c,d,		f,g,h,		j,k,l))
				);
		}
	}//namespace Maths
}//namespace myEngine
