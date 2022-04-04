#include "MovimientoJugador.h"
#include "GameObject.h"
#include "Transform.h"
#include "Vector3.h"
#include "Vector4.h"
#include "GameTime.h"
#include "Input.h"
#include <StringFormater.h>
#include <iostream>
void LoveEngine::ECS::MovimientoJugador::init()
{
	input = Input::InputManager::getInstance();
	//assert

	player = gameObject->getComponent<Transform>();
	//assert
}

void LoveEngine::ECS::MovimientoJugador::update()
{
	float movement = 0;
	Utilities::Vector4 rotation;

	float dT = Time::getInstance()->deltaTime;

	if (input->isKeyPressed(Input::InputKeys::W)) movement = speed * dT;
	if (input->isKeyPressed(Input::InputKeys::S)) movement = -speed * dT;
	if (input->isKeyPressed(Input::InputKeys::A)) rotation.y = rotSpeed * dT;
	if (input->isKeyPressed(Input::InputKeys::D)) rotation.y = -rotSpeed * dT;

	player->translate(player->forward() * movement);
	player->rotate(rotation);

}

void LoveEngine::ECS::MovimientoJugador::receiveMessage(std::string message)
{
	StringFormatter sf(message);

	sf.tryGetFloat("speed", speed);
	sf.tryGetFloat("rotSpeed", rotSpeed);

}


