#pragma once

namespace LoveEngine {
	namespace Singleton {

		enum class positions {
			SceneManager, Time, Input, ComponentFactory, Physics, Renderer, SoundManager
		};

		void* getElement(positions pos);
		void  addElement(void* elem, positions pos);
	}
}