#include "ComponenteDeContar.h"
#include <iostream>
#include <SceneManager.h>
#include <GameTime.h>
#include <Timer.h>
#include <GameObject.h>

void ComponenteDeContar::init() {
	//Timer::deleteComponent(this, 1);
	//Timer::deleteGameObject(gameObject, 1);
	//Timer::invoke([&]() {std::cout << (scene == nullptr ? "sii" : "nooo"); }, 1);
}

void ComponenteDeContar::update() {
	std::cout << "Frame numero: " << ++count << "\n";

	if (count > 15) {
		SceneManager::getInstance()->changeScene(1, SceneLoad::SWAP);
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
