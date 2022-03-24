#include "ComponenteDeContar.h"
#include <iostream>
#include <SceneManager.h>
#include <GameTime.h>

void ComponenteDeContar::update() {

	std::cout << "Frame rate: " << 1.0f / LoveEngine::Time::getInstance()->deltaTime << "\n";
}
