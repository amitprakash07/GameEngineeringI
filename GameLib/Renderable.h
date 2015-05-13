#ifndef __RENDERABLE_H
#define __RENDERABLE_H

#include "SharedPointer.h"
#include "GameObject.h"



namespace myEngine
{
	namespace Rendering
	{
		class Renderables
		{
		public:
			static Renderables*										getRenderingSystem();
			static	void											deleteRenderingSystem();
			void													addToRenderables(SharedPointer<GameObject>&);
			bool													removeFromRenderables(SharedPointer<GameObject>&);
			bool													isObjectRenderable(SharedPointer<GameObject>&, size_t &);
			void													drawRenderables();

		private:
			static Renderables *									mRenderingSystem;
			std::vector<SharedPointer<GameObject>>					mRenderables;
			bool													isInitialized;
			Renderables();
			Renderables(Renderables&);
			Renderables operator = (Renderables);
			~Renderables();
		};
	}
}

#endif //__RENDERABLE_H