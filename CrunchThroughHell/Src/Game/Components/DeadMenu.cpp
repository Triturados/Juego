#include "DeadMenu.h"
#include <SceneManager.h>
#include <Button.h>
#include "Input.h"

namespace LoveEngine {

	namespace ECS {
		DeadMenu::DeadMenu()
		{
			menuButton = restartButton = nullptr;
		}
		void DeadMenu::init()
		{
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
			SceneManagement::changeScene(1, SceneManagement::SceneLoad::PUSH);
		}


		void DeadMenu::goBackMenu() {
			SceneManagement::changeScene(1, SceneManagement::SceneLoad::POP);//Borramos la escena del menu muerte y juego
			//SceneManagement::changeScene(3, SceneManagement::SceneLoad::POP);//Borramos la escena del menu muerte y juego
		}

	}
}