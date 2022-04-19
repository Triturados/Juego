#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace ECS {
		class Button;

		class MainMenu : public Component {
		public:
			MainMenu();

			void init() override;
			void receiveComponent(int, Component*) override;
		private:

			Button* startbutton;
			Button* exitbutton;

			void startGame();
			void exit();
		};
	}
}
