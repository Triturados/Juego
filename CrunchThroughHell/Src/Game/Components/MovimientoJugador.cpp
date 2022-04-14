#include "MovimientoJugador.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"
#include "Vector4.h"
#include "GameTime.h"
#include "Input.h"
#include <StringFormatter.h>
#include <iostream>

void LoveEngine::ECS::MovimientoJugador::init()
{
	input = Input::InputManager::getInstance();
	//assert

	tr = gameObject->getComponent<Transform>();
	//assert

	rb = gameObject->getComponent<RigidBody>();
	hasRigidBody = rb != nullptr;
}

void LoveEngine::ECS::MovimientoJugador::update()
{
	float movement = 0;
	Utilities::Vector4<float> rotation;

	float dT = Time::getInstance()->deltaTime;

	if (!input->controllerConected()) {
		if (input->isKeyPressed(Input::InputKeys::W)) movement = speed * dT;
		if (input->isKeyPressed(Input::InputKeys::S)) movement = -speed * dT;
		if (input->isKeyPressed(Input::InputKeys::A)) rotation.y = rotSpeed * dT;
		if (input->isKeyPressed(Input::InputKeys::D)) rotation.y = -rotSpeed * dT;
	}
	else {
		Utilities::Vector2 controller = input->getController().leftJoystick;

		movement = controller.y * speed * dT;
		rotation.y = controller.x * rotSpeed * dT;

		//std::cout << controller << "\n";
	}
	tr->translate(tr->forward() * movement);
	tr->rotate(rotation);

}

void LoveEngine::ECS::MovimientoJugador::moveTransform(float mv, Utilities::Vector4<float> rt)
{

}

void LoveEngine::ECS::MovimientoJugador::moveRigidbody(float mv, Utilities::Vector4<float> rt)
{

}

void LoveEngine::ECS::MovimientoJugador::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("speed", speed);
	sf.tryGetFloat("rotSpeed", rotSpeed);
}


