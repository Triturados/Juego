#include "ComponenteDeContar.h"
#include <iostream>
#include <SceneManager.h>
#include <GameTime.h>
#include <Timer.h>
#include <GameObject.h>
#include <StringFormatter.h>
#include <Window.h>
#include <Input.h>

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

		void EscribirNumero::receiveMessage(Utilities::StringFormatter& sf)
		{
			numerito = sf.getInt("numerito");
		}

		void Moverpanatalla::moverPantalla()
		{
			int x = rand() % 1920;
			int y = rand() % 1080;

			Window::getInstance()->repositionWindow(Utilities::Vector2<int>(x, y));
		}

		Moverpanatalla::Moverpanatalla()
		{
			srand(std::time(NULL));
			rand();
			inicial = 3;
			repeticion = 2;
			size = Utilities::Vector2<int>();
		}

		void Moverpanatalla::init()
		{
			size = Window::getInstance()->getWindowSize();
			//timer = Timer::repeat([&](Timer*) { moverPantalla(); }, inicial);
		}

		void Moverpanatalla::update()
		{
			float dt = Time::getInstance()->deltaTime;

			bool change = false;
			if (Input::InputManager::getInstance()->isKeyPressed(Input::InputKeys::A))
			{
				change = true;
				size.x++;
			}
			else if (Input::InputManager::getInstance()->isKeyPressed(Input::InputKeys::S))
			{
				change = true;
				size.y++;
			}

			std::cout << size << "\n";
			if (change) {
				Window::getInstance()->setWindowSize(size);
			}
		}

		void Moverpanatalla::receiveMessage(Utilities::StringFormatter& sf)
		{
			if (!sf.tryGetFloat("inicial", inicial)) {
				int ini;
				if (sf.tryGetInt("inicial", ini))
					inicial = ini;
			}
			if (!sf.tryGetFloat("repeticion", repeticion)) {
				int repe;
				if (sf.tryGetInt("repeticion", repe))
					repeticion = repe;
			}
		}

		/*void EscribirNumero::receiveValues(int i, float f, Component* c, GameObject* o)
		{

		}*/
	}
}