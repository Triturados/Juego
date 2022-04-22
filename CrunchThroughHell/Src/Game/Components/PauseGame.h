#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace Input {
		class InputManager;
	}
	namespace ECS {
		class Button;

		class PauseGame : public Component {
			Input::InputManager* input;
		public:
			void init() override;
			void update() override;
		};
	}
}
