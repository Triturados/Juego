#pragma once
#include <Component.h>
#include <vector>
namespace LoveEngine {
	namespace ECS {
		class Button;
		class MoveUI;
		class Sound;
		class MainMenu : public Component {
		public:
			MainMenu();

			void postInit() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter&) override;
			void receiveComponent(int, Component*) override;
		private:
			int centerButtonIdx;
			int centerx;
			float scrollTimer;
			float scrollInterval;
			Button *up, *down;
			std::vector<Button*> buttons;
			std::vector<MoveUI*> moveUIs;
			std::vector<int> positions;
			Sound* musicSound;
			int currentlySelected;

			int getButtonIdx(int i);

			void advance(int i, float t = -1);

			void newGame();
			void continueGame();
			void settings();
			void howToPlay();
			void about();
			void exit();

			void showMenu();
		};
	}
}
