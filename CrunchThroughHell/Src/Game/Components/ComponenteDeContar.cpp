#include "ComponenteDeContar.h"
#include <iostream>
#include <SceneManager.h>
#include <GameTime.h>
#include <Timer.h>
#include <GameObject.h>

void ComponenteDeContar::init() {
	//Timer::deleteComponent(this, 1);
	Timer::deleteGameObject(gameObject, 1);
	//Timer::invoke([&]() {std::cout << (scene == nullptr ? "sii" : "nooo"); }, 1);
}

void ComponenteDeContar::update() {
	count++;
	//std::cout << "Frame rate: " << 1.0f / LoveEngine::Time::getInstance()->deltaTime << "\n";
}
