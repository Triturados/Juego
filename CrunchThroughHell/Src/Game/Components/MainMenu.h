#pragma once
#include <Component.h>
#include <vector>
namespace LoveEngine {
	namespace ECS {
		class Button;
		class MoveUI;
		class MainMenu : public Component {
		public:
			MainMenu();

			void init() override;
			void receiveComponent(int, Component*) override;
		private:

			Button *up, *down;
			std::vector<Button*> buttons;
			std::vector<MoveUI*> moveUIs;
			std::vector<int> positions;
			int currentlySelected;

			int getButtonIdx(int i);

			void advance(int i);

			void newGame();
			void continueGame();
			void settings();
			void howToPlay();
			void about();
			void exit();
		};
	}
}
