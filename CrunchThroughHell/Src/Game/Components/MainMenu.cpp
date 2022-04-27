#include "MainMenu.h"
#include <SceneManager.h>
#include <Definitions.h>
#include <Button.h>
#include <Vector3.h>
#include <GameObject.h>
#include "MoveUI.h"
namespace LoveEngine {


	enum MenuButtons {
		NewGame, Continue, HowToPlay, Settings, About, Exit, NumButtons
	};

	namespace ECS {
		MainMenu::MainMenu()
		{
			currentlySelected = 0;
			buttons = std::vector<Button*>(MenuButtons::NumButtons, nullptr);
			moveUIs = std::vector<MoveUI*>(MenuButtons::NumButtons, nullptr);
			positions = std::vector<int>(MenuButtons::NumButtons, 0);
		}
		void MainMenu::init()
		{
			buttons[MenuButtons::NewGame]->onClick([&]() {newGame(); });
			buttons[MenuButtons::Continue]->onClick([&]() {continueGame(); });
			buttons[MenuButtons::HowToPlay]->onClick([&]() {howToPlay(); });
			buttons[MenuButtons::Settings]->onClick([&]() {settings(); });
			buttons[MenuButtons::About]->onClick([&]() {about(); });
			buttons[MenuButtons::Exit]->onClick([&]() {exit(); });

			for (int i = 0; i < buttons.size(); i++) {
				Button* button = buttons[i];
				auto pos = button->getPos();
				positions[i] = pos.y;
  
				auto move = button->gameObject->addComponent<MoveUI>();
				move->init();
				move->changeDestination(pos);
				move->setActive(false);
				moveUIs[i] = move;
			}

			up  ->onClick([&]() {advance( 1); });
			down->onClick([&]() {advance(-1); });
		}

		void MainMenu::receiveComponent(int i, Component* c)
		{
			if (i == -2) {
				down = static_cast<Button*>(c);
				return;
			}
			if (i == -1) {
				up = static_cast<Button*>(c);
				return;
			}
			buttons[i] = static_cast<Button*>(c);
		}

		int MainMenu::getButtonIdx(int i)
		{
			int nindex = i + currentlySelected;
			nindex %= NumButtons;

			return nindex;
		}

		void MainMenu::newGame() {
			SceneManagement::changeScene((int)SceneOrder::Overworld, SceneManagement::SceneLoad::SWAP);
		}

		void MainMenu::continueGame() {

		}

		void MainMenu::howToPlay() {

		}

		void MainMenu::settings() {

		}
		
		void MainMenu::about() {

		}

		void MainMenu::exit() {
			SceneManagement::changeScene(0, SceneManagement::SceneLoad::EXIT);
		}


		void MainMenu::advance(int idx) {
			currentlySelected += idx;

			if (currentlySelected < 0)
				currentlySelected = NumButtons - 1;
			else if (currentlySelected >= NumButtons) {
				currentlySelected = 0;
			}

			for (int i = 0; i < NumButtons; i++) {
				auto pos = buttons[i]->getPos();
				int buttonidx = getButtonIdx(i);
				pos.y = positions[buttonidx];
				if ((buttonidx == 0 && idx == 1) || (buttonidx == NumButtons - 1 && idx == -1)) {
					moveUIs[i]->setActive(false);
					buttons[i]->setPos(pos);
				}
				else
					moveUIs[i]->changeDestination(pos);
			}

		}

		
	}
}