#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace ECS {
		class Button;

		class DeadMenu : public Component {
		public:
			DeadMenu();

			void init() override;
			void receiveComponent(int, Component*) override;
		private:

			Button* restartButton;
			Button* menuButton;

			void restartGame();
			void goBackMenu();
		};
	}
}

