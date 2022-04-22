#include <SceneManager.h>
#include <Button.h>
#include "PauseMenu.h"
#include "Input.h"

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
			}
			if (exitbutton != nullptr) {
				exitbutton->onClick([&]() {exit(); });
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
			SceneManagement::changeScene(1, SceneManagement::SceneLoad::POP);
		}


		void PauseMenu::exit() {
			SceneManagement::changeScene(0, SceneManagement::SceneLoad::EXIT);
		}

	}
}