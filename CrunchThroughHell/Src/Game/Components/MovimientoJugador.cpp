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
		if (input->isKeyPressed(Input::InputKeys::W)) movement = speed;
		if (input->isKeyPressed(Input::InputKeys::S)) movement = -speed;
		if (input->isKeyPressed(Input::InputKeys::A)) rotation.y = rotSpeed;
		if (input->isKeyPressed(Input::InputKeys::D)) rotation.y = -rotSpeed;
	}
	else {
		Utilities::Vector2 controller = input->getController().leftJoystick;

		movement = controller.y * speed ;
		rotation.y = controller.x * rotSpeed;

		//std::cout << controller << "\n";
	}

	std::cout << tr->getRot()->y << std::endl;
	if (hasRigidBody)moveRigidbody(movement, rotation);
	else moveTransform(movement, rotation, dT);

}

void LoveEngine::ECS::MovimientoJugador::moveTransform(float mv, Utilities::Vector4<float> rt, float dT)
{
	tr->translate(tr->forward() * mv * dT);
	rt.y *= dT;
	tr->rotate(rt);
}

void LoveEngine::ECS::MovimientoJugador::moveRigidbody(float mv, Utilities::Vector4<float> rt)
{
	rb->setLinearVelocity(tr->forward() * mv);

	Utilities::Vector3<float> rtToV3(rt.x, rt.y, rt.z);

	rb->setAngularVelocity(rtToV3);
}

void LoveEngine::ECS::MovimientoJugador::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("speed", speed);
	sf.tryGetFloat("rotSpeed", rotSpeed);
}


