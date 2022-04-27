#include "DeadMenu.h"
#include <SceneManager.h>
#include <Button.h>
#include "Input.h"
#include <Definitions.h>
#include <Timer.h>

namespace LoveEngine {

	namespace ECS {
		DeadMenu::DeadMenu()
		{
			
		}
		void DeadMenu::init()
		{
			input = Input::InputManager::getInstance();
			input->mouseVisibility(false);

			ECS::Timer::invoke([&](ECS::Timer*) {
				goBackMenu();
				}, 5.0f);
		}

		void DeadMenu::update()
		{
			if (input->isControllerButtonState(Input::ControllerButtonState::DOWN) || input->mousePressed(Input::MouseState::CLICK_L))
			{
				goBackMenu();
			}
		}

		void DeadMenu::goBackMenu() {
			SceneManagement::changeScene((int)SceneOrder::MainMenu, SceneManagement::SceneLoad::SWAP);//Borramos la escena del menu muerte y juego
		}

	}
}