#include "SaludJugador.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"
#include "Vector4.h"
#include "GameTime.h"
#include "Input.h"
#include <StringFormatter.h>
#include <iostream>

void LoveEngine::ECS::SaludJugador::receiveMessage(Utilities::StringFormatter& sf)
{
	/*sf.tryGetFloat("speed", speed);
	sf.tryGetFloat("rotSpeed", rotSpeed);*/
}

void LoveEngine::ECS::SaludJugador::init()
{
	input = Input::InputManager::getInstance();
	//assert

	tr = gameObject->getComponent<Transform>();
	//assert
}

void LoveEngine::ECS::SaludJugador::update()
{
	

}




