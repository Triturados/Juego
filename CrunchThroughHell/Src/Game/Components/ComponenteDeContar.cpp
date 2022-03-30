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
			std::cout << "Frame numero: " << ++count << "\n";

			if (count > 15) {
				LoveEngine::SceneManagement::changeScene(1, 1);
			}
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