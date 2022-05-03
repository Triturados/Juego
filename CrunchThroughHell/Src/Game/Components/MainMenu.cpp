#include "MainMenu.h"
#include <SceneManager.h>
#include <Definitions.h>
#include <Input.h>
#include <Button.h>
#include <Vector3.h>
#include <GameObject.h>
#include "MoveUI.h"
#include "GameTime.h"
#include "Window.h"
#include <StringFormatter.h>
#include "ScaleMainMenuButton.h"
#include <Sound.h>
#include <SoundButton.h>

namespace LoveEngine {


	enum MenuButtons {
		NewGame, Continue, HowToPlay, Settings, About, Exit, NumButtons
	};


	namespace ECS {

		Utilities::Vector2<int> mousepos;

		MainMenu::MainMenu()
		{
			centerButtonIdx = 2;
			centerx = Window::getInstance()->getWindowSize().x * .5f;
			currentlySelected = 0;
			buttons = std::vector<Button*>(MenuButtons::NumButtons, nullptr);
			moveUIs = std::vector<MoveUI*>(MenuButtons::NumButtons, nullptr);
			positions = std::vector<int>(MenuButtons::NumButtons, 0);

			scrollTimer = 0;
			scrollInterval = 0.2f;
		}
		void MainMenu::postInit()
		{
			buttons[MenuButtons::NewGame]->onClick([&]() {newGame(); });
			buttons[MenuButtons::Continue]->onClick([&]() {continueGame(); });
			buttons[MenuButtons::HowToPlay]->onClick([&]() {howToPlay(); });
			buttons[MenuButtons::Settings]->onClick([&]() {settings(); });
			buttons[MenuButtons::About]->onClick([&]() {about(); });
			buttons[MenuButtons::Exit]->onClick([&]() {exit(); });

			std::vector<ScaleMainMenuButton*> scales;
			for (int i = 0; i < buttons.size(); i++) {
				Button* button = buttons[i];
				auto pos = button->getPos();
				positions[i] = pos.y;

				auto scale = button->gameObject->addComponent<ScaleMainMenuButton>();
				scale->sendFormattedString("maxDistance: 700.0; height: 545.0;");
				scale->init();
				scales.push_back(scale);

				auto move = button->gameObject->addComponent<MoveUI>(true);
				move->sendFormattedString("centerX: " + std::to_string(centerx));
				move->init();
				move->changeDestination(pos);
				move->setActive(false);
				moveUIs[i] = move;
				
				auto sound = button->gameObject->addComponent<Sound>();
				sound->sendFormattedString("soundName: ClickSound.wav; channel: effects; loop: false; volume: 0.5; playNow: false; ");
				sound->init();

				auto soundController = button->gameObject->addComponent<SoundButton>();
				soundController->init();
				soundController->postInit();
			}

			up->onClick([&]() {advance(1, 1); });
			down->onClick([&]() {advance(-1, 1); });

			for (int i = 0; i < 4; i++) {
				advance(-1, 1);
			}
			int height = moveUIs[0]->getDestination().y + std::round(buttons[0]->getSize().y * 0.5f);

			for (auto scale : scales) {
				scale->setHeight(height);
				//scale->enabled = false;
			}
		}

		void MainMenu::update() {

			Input::InputManager* input = Input::InputManager::getInstance();

			if (input->justClicked()) {
				auto p = input->mousePosition();
				if (true || mousepos != Utilities::Vector2<int>()) {
					std::cout << p - mousepos << "\n";
				}
				mousepos = p;
			}

			if (scrollTimer > scrollInterval) {
				float scroll = input->mouseWheel();
				if (scroll != 0) {
					int dir = -1;
					if (scroll > 0) {
						dir = 1;
					}

					advance(dir);
					scrollTimer = 0;
				}
			}
			else {
				scrollTimer += Time::getInstance()->deltaTime;
			}
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

		void MainMenu::receiveMessage(Utilities::StringFormatter& sf) {

			sf.tryGetInt("centerX", centerx);

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

		void MainMenu::advance(int idx, float time) {
			currentlySelected += idx;

			if (currentlySelected < 0)
				currentlySelected = NumButtons - 1;
			else if (currentlySelected >= NumButtons) {
				currentlySelected = 0;
			}

			for (int i = 0; i < NumButtons; i++) {
				auto pos = buttons[i]->getPos();
				int buttonidx = getButtonIdx(i);

				buttons[i]->setInteractable(buttonidx == centerButtonIdx);
				pos.x = centerx - (buttons[i]->getSize().x * 0.5f);
				pos.y = positions[buttonidx];
				if ((buttonidx == 0 && idx == 1) || (buttonidx == NumButtons - 1 && idx == -1)) {
					moveUIs[i]->setActive(false);
					buttons[i]->setPos(pos);
				}
				if (time > 0)
					moveUIs[i]->setDuration(time);
				moveUIs[i]->changeDestination(pos);
			}

		}


	}
}