#include "DeadMenu.h"
#include <SceneManager.h>
#include <Button.h>
#include "Input.h"
#include <Definitions.h>

namespace LoveEngine {

	namespace ECS {
		DeadMenu::DeadMenu()
		{
			menuButton = restartButton = nullptr;
		}
		void DeadMenu::init()
		{
			std::cout << "Creando muerte" << std::endl;

			Input::InputManager::getInstance()->mouseVisibility(false);

			if (restartButton != nullptr) {
				restartButton->onClick([&]() {restartGame(); });
			}
			if (menuButton != nullptr) {
				menuButton->onClick([&]() {goBackMenu(); });
			}
		}
		void DeadMenu::receiveComponent(int i, Component* c)
		{
			switch (i)
			{
			case 0:
				restartButton = static_cast<Button*>(c);
				break;
			case 1:
				menuButton = static_cast<Button*>(c);
				break;
			default:
				break;
			}
		}


		void DeadMenu::restartGame() {
			std::cout << "Volvemos al juego" << std::endl;
			SceneManagement::changeScene((int)SceneOrder::Overworld, SceneManagement::SceneLoad::CLEAR);
		}


		void DeadMenu::goBackMenu() {
			SceneManagement::changeScene((int)SceneOrder::MainMenu, SceneManagement::SceneLoad::SWAP);//Borramos la escena del menu muerte y juego
		}

	}
}