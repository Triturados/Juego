#include "ScrollContainer.h"
#include "StringFormatter.h"
#include "GameTime.h"
#include "SceneManager.h"
#include <Input.h>
#include "Utils.h"
#include "GameObject.h"
#include "MoveUI.h"
#include "Timer.h"
#include "Window.h"

namespace LoveEngine {


	namespace ECS {


		ScrollContainer::ScrollContainer() {
			speed = 0;
			minHeight = 0;
			maxHeight = 1000;
			automatic = false;
			timeToEnable = -1;
			currentHeight = 0;
		}

		void ScrollContainer::receiveMessage(Utilities::StringFormatter& sf) {
			int newspeed;
			sf.tryGetInt("maxHeight", maxHeight);
			sf.tryGetInt("minHeight", minHeight);

			if (sf.tryGetBool("automatic", automatic))
				if (!sf.tryGetFloat("speed", speed)) {
					if (sf.tryGetInt("speed", newspeed)) {
						speed = newspeed;
					}
				}

			if (!sf.tryGetFloat("timeToEnable", timeToEnable)) {
				if (sf.tryGetInt("timeToEnable", newspeed)) {
					timeToEnable = newspeed;
				}
			}
		}

		void ScrollContainer::receiveComponent(int i, Component* c)
		{
			if (i >= 0)
				UIContainer::receiveComponent(i, c);
			else
				cont = static_cast<UIContainer*>(c);
		}

		void ScrollContainer::leaveAndCloseScene()
		{
			int xpos = cont->getPosition().x;
			int ypos = Window::getInstance()->getWindowSize().y;
			cont->gameObject->getComponent<MoveUI>()->changeDestination(Utilities::Vector3(xpos, ypos, 0));
			Timer::invoke([&](Timer*) {
				SceneManagement::changeScene(0, SceneManagement::SceneLoad::POP); }, 2.0);
		}


		void ScrollContainer::onMove() {
			int posy = position.y;
			position.y += std::round(currentHeight);;
			UIContainer::onMove();
			position.y = posy;
		}


		void ScrollContainer::init()
		{
			if (timeToEnable > 0) {
				enabled = false;
				Timer::invoke([&](Timer*) {enabled = true; }, timeToEnable);
			}
		}
		void ScrollContainer::update() {
			auto input = Input::InputManager::getInstance();

			if (input->isKeyPressed(Input::InputKeys::ESCAPE)) {
				leaveAndCloseScene();
				return;
			}

			float dt = Time::getInstance()->deltaTime;
			if (!automatic) {

				float mousewheel = -input->mouseWheel();
				if (mousewheel != 0) {

					currentHeight += mousewheel * dt * speed;
				}

				ScrollContainer::onMove();
				return;
			}
			currentHeight += speed * dt;

			if (currentHeight > maxHeight) {
				automatic = false;

				//Cableo un poco esto aqui pero es un script del juego asi que no problem >n<
				leaveAndCloseScene();
			}

			ScrollContainer::onMove();
		}

	}

}