#include <SceneManager.h>
#include <Button.h>
#include "PauseMenu.h"
#include "Input.h"
#include <Sound.h>
#include <SoundButton.h>
#include <GameObject.h>
#include <Definitions.h>

namespace LoveEngine {

	namespace ECS {
		PauseMenu::PauseMenu()
		{
			exitbutton = continuebutton = nullptr;
		}
		void PauseMenu::init()
		{
			if (continuebutton != nullptr) {
				continuebutton->onClick([&]() {continueGame(); });
				auto sound = continuebutton->gameObject->addComponent<Sound>();
				sound->sendFormattedString("soundName: ClickSound.wav; channel: effects; loop: false; volume: 0.5; playNow: false; ");
				sound->init();

				auto soundController = continuebutton->gameObject->addComponent<SoundButton>();
				soundController->init();
				soundController->postInit();
			}
			if (exitbutton != nullptr) {
				exitbutton->onClick([&]() {exit(); });
				auto sound = exitbutton->gameObject->addComponent<Sound>();
				sound->sendFormattedString("soundName: ClickSound.wav; channel: effects; loop: false; volume: 0.5; playNow: false; ");
				sound->init();

				auto soundController = exitbutton->gameObject->addComponent<SoundButton>();
				soundController->init();
				soundController->postInit();
			}


		}
		
		void PauseMenu::receiveComponent(int i, Component* c)
		{
			switch (i)
			{
			case 0:
				continuebutton = static_cast<Button*>(c);
				break;
			case 1:
				exitbutton = static_cast<Button*>(c);
				break;
			default:
				break;
			}
		}


		void PauseMenu::continueGame() {
			SceneManagement::changeScene(0, SceneManagement::SceneLoad::POP);
		}


		void PauseMenu::exit() {
			SceneManagement::changeScene((int)SceneOrder::MainMenu, SceneManagement::SceneLoad::CLEAR);
		}

	}
}