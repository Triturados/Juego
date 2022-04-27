#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Button;

		class DeadMenu : public Component {
		public:
			DeadMenu();
			void init() override;
			void update() override;
		private:
			Input::InputManager* input;
			void goBackMenu();
		};
	}
}

