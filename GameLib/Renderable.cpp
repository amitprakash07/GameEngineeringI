#include "Renderable.h"
#include "HeapManager.h"
#include "Engine.h"

namespace myEngine
{
	

	namespace Rendering
	{
		Renderables* Renderables::mRenderingSystem = nullptr;

		Renderables* Renderables::getRenderingSystem()
		{
			if (mRenderingSystem == nullptr)
			{
				mRenderingSystem = (EngineController::GameEngine::isEngineInitialized()) ?
					new (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(Renderables))) Renderables() : new Renderables();
			}
			
			return mRenderingSystem;
		}


		void Renderables::deleteRenderingSystem()
		{
			MessagedAssert(mRenderingSystem != nullptr, "RenderingSystem is either not instantiated or had been already deleted");
			EngineController::GameEngine::isEngineInitialized() ?
				EngineController::GameEngine::getMemoryManager()->__free(mRenderingSystem) :
				delete mRenderingSystem;

			mRenderingSystem = nullptr;
		}


		Renderables::~Renderables()
		{
			while (mRenderables.size() != 0)
			{
				mRenderables.at(0).deleteObject();
				mRenderables.erase(mRenderables.begin());
			}
		}

		Renderables::Renderables()
		{
			mRenderables.reserve(10);
			isInitialized = true;
		}

		
		void Renderables::addToRenderables(SharedPointer<GameObject> &i_GameObject)
		{
			size_t objecIndex;
			if (!i_GameObject.isNull())
			{
				if (!isObjectRenderable(i_GameObject, objecIndex))
					mRenderables.push_back(i_GameObject);
			}			
		}//addToRenderables


		bool Renderables::removeFromRenderables(SharedPointer<GameObject> &i_GameObject)
		{
			size_t objectIndex = 0x0f0f0f0f;
			if ((!i_GameObject.isNull()) && isObjectRenderable(i_GameObject, objectIndex) && (objectIndex != 0x0f0f0f0f))
			{
				mRenderables.erase(mRenderables.begin() + objectIndex);
				return true;
			}
			return false;
		}//removeFromRenderables


		bool Renderables::isObjectRenderable(SharedPointer<GameObject>&i_GameObject, size_t & o_index)
		{
			bool isObjectFound = false;
			if (!i_GameObject.isNull())
			{
				for (size_t i = 0; i < mRenderables.size() && isObjectFound == false; i++)
				{
					if (mRenderables[i].isEqual(i_GameObject))
					{
						mRenderables[i].isNull();
						o_index = i;
						isObjectFound = true;
					} //if
				} // for
			}
			
			return isObjectFound;
		} //isObjectRenderable


		void Renderables::drawRenderables()
		{
			bool bQuit = EngineController::GameEngine::cheesyServiceQuit;
			Cheesy::Service(bQuit);
			if (Cheesy::BeginFrame(myEngine::getAsCheesyRGBA(EngineController::GameEngine::getWorldController()->getWindowColor())))
			{
				for (size_t i = 0; i < mRenderables.size(); i++)
				{
					if (mRenderables[i]->isRenderable())
						mRenderables[i]->getSprite()->draw(mRenderables[i]->getPosition());
					else removeFromRenderables(mRenderables[i]);
				}//for loop	
				Cheesy::EndFrame();
			}
				
		}//draw Renderables
	} //namespace Rendering
} // namespace myEngine