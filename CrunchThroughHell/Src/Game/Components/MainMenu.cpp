#include "MainMenu.h"
#include <SceneManager.h>
#include <Button.h>

namespace LoveEngine {

	namespace ECS {
		MainMenu::MainMenu()
		{
			exitbutton = startbutton = nullptr;
		}
		void MainMenu::init()
		{
			if (startbutton != nullptr) {
				startbutton->onClick([&]() {startGame(); });
			}
			if (exitbutton != nullptr) {
				exitbutton->onClick([&]() {exit(); });
			}
		}
		void MainMenu::receiveComponent(int i, Component* c)
		{
			switch (i)
			{
			case 0:
				startbutton = static_cast<Button*>(c);
				break;
			case 1:
				exitbutton = static_cast<Button*>(c);
				break;
			default:
				break;
			}
		}


		void MainMenu::startGame() {
			SceneManagement::changeScene(1, SceneManagement::SceneLoad::PUSH);
		}


		void MainMenu::exit() {
			SceneManagement::changeScene(0, SceneManagement::SceneLoad::EXIT);
		}

	}
}