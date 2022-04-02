#include "ComponenteDeContar.h"
#include <iostream>
#include <SceneManager.h>
#include <GameTime.h>
#include <Timer.h>
#include <GameObject.h>

namespace LoveEngine {
	namespace ECS {

		void ComponenteDeContar::init() {

		}

		void ComponenteDeContar::update() {
			int count = Time::getInstance()->frameCount;
			std::cout << "Frame numero: " << count << "\n";

			if (count > 15) {
				//std::cout << damenum() << "\n";
				LoveEngine::SceneManagement::SceneManager::getInstance()->changeScene(1,
					SceneManagement::SceneLoad::PUSH);
			}
		}

		void ComponenteDeContar::receiveMessage(std::string message)
		{
			std::cout << "He recibido el siguiente mensaje: " << message << "\n";
		}

		void FrameRate::init()
		{
		}

		void FrameRate::update()
		{
			std::cout << "Frame rate: " << 1.0f / LoveEngine::Time::getInstance()->deltaTime << "\n";
		}

		void Autodestruccion::init()
		{
			timer = Timer::deleteGameObject(gameObject, 1);
		}

		void Autodestruccion::update()
		{
			std::cout << "Este componente se autodestruira en: " << timer->timeLeft() << "\n";
		}


		void EscribirNumero::init()
		{
		}
		void EscribirNumero::update()
		{
			std::cout << "numerito numerito: " << numerito << "\n";
		}

		void EscribirNumero::sendValues(int i, float f, Component* c, GameObject* o)
		{
			numerito = i;
		}
	}
}