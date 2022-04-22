#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace ECS {
		class Button;

		class PauseMenu : public Component {
		public:
			PauseMenu();

			void init() override;
			void receiveComponent(int, Component*) override;
		private:

			Button* continuebutton;
			Button* exitbutton;

			void continueGame();
			void exit();
		};
	}
}
