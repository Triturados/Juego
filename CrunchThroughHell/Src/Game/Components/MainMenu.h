#pragma once
#include <Component.h>
#include <vector>
namespace LoveEngine {
	namespace ECS {
		class Button;

		class MainMenu : public Component {
		public:
			MainMenu();

			void init() override;
			void receiveComponent(int, Component*) override;
		private:

			std::vector<Button*> buttons;

			void newGame();
			void continueGame();
			void settings();
			void howToPlay();
			void about();
			void exit();
		};
	}
}
