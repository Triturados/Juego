#include "PauseGame.h"
#include "Input.h"
#include "SceneManager.h"
#include <iostream>
#include <Definitions.h>

void LoveEngine::ECS::PauseGame::init() {
	input = Input::InputManager::getInstance();
}

void LoveEngine::ECS::PauseGame::update() {
	std::cout << "ASDASD";
	if (input->keyJustPressed(Input::InputKeys::ESCAPE)) {
		SceneManagement::changeScene((int)SceneOrder::Pause, SceneManagement::SceneLoad::PUSH);
	}
}