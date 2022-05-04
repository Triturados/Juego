#include "ScrollContainer.h"
#include "StringFormatter.h"
#include "GameTime.h"
#include "SceneManager.h"
#include <Input.h>

namespace LoveEngine {


	namespace ECS {


		ScrollContainer::ScrollContainer() {
			speed = 0;
			minHeight = 0;
			maxHeight = 1000;
			automatic = false;
		}

		void ScrollContainer::receiveMessage(Utilities::StringFormatter& sf) {
			int newspeed;
			sf.tryGetInt("maxHeight", maxHeight);
			sf.tryGetInt("minHeight", minHeight);

			if (sf.tryGetBool("automatic", automatic))
				if (sf.tryGetFloat("speed", speed)) {
					if (sf.tryGetInt("speed", newspeed)) {
						speed = newspeed;
					}
				}
		}


		void ScrollContainer::onMove() {
			if (!enabled) return;

			int& ypos = position.y;
			if (ypos < minHeight)
				ypos = minHeight;
			else if (ypos > maxHeight)
				ypos = maxHeight;
		}

#define input Input::InputManager::getInstance()
#define v3down(x) Utilities::Vector3<int>(0, x, 0)

		void ScrollContainer::update() {
			if (!automatic) {

				float mousewheel = input->mouseWheel();
				if (mousewheel != 0) {
					setPosition(position + v3down(speed));
				}
				return;
			}
			position = position + v3down(speed * Time::getInstance()->deltaTime);

			if (position.y > maxHeight) {
				automatic = false;

				//Cableo un poco esto aqui pero es un script del juego asi que no problem >n<
				SceneManagement::changeScene(0, SceneManagement::SceneLoad::POP);
			}
		}

	}

}