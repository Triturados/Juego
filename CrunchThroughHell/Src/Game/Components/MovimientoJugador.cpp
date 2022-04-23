#include "MovimientoJugador.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"
#include "Vector4.h"
#include "GameTime.h"
#include "Input.h"
#include "ParticleSystem.h"
#include <StringFormatter.h>
#include <iostream>
#include "SceneManager.h"

void LoveEngine::ECS::MovimientoJugador::init()
{
	input = Input::InputManager::getInstance();
	//assert

	tr = gameObject->getComponent<Transform>();
	//assert

	rb = gameObject->getComponent<RigidBody>();
	hasRigidBody = rb != nullptr;

	if(hasRigidBody)rb->setAngularFactor(Utilities::Vector3<float>(0, 1, 0));
	
	dashParticles = tr->getChild(1)->gameObject->getComponent<ParticleSystem>();
}

void LoveEngine::ECS::MovimientoJugador::update()
{
	float movement = 0;
	Utilities::Vector4<float> rotation;
	float dT = Time::getInstance()->deltaTime;
	lastDash += dT;

	if (!input->controllerConected()) {
		if (input->isKeyPressed(Input::InputKeys::W)) movement = speed;
		if (input->isKeyPressed(Input::InputKeys::S)) movement = -speed;
		if (input->isKeyPressed(Input::InputKeys::A)) rotation.y = rotSpeed;
		if (input->isKeyPressed(Input::InputKeys::D)) rotation.y = -rotSpeed;
		if (input->isKeyPressed(Input::InputKeys::SPACE) && lastDash >= dashDelay) isDashing = true;
		if (input->isKeyPressed(Input::InputKeys::R))
		{
			SceneManagement::changeScene(5, SceneManagement::SceneLoad::SWAP); //Ir escena muerte
		}
	}
	else {
		Utilities::Vector2 controller = input->getController().leftJoystick;

		movement = controller.y * speed;
		rotation.y = controller.x * rotSpeed;

		//std::cout << controller << "\n";
	}

	if (isDashing) {
		dash(dT);
	}
	else if (hasRigidBody) {
		moveRigidbody(movement, rotation);
	}
	else moveTransform(movement, rotation, dT);

}

void LoveEngine::ECS::MovimientoJugador::dash(float dT)
{
	if (!dashParticles->isEmitting()) dashParticles->setActive(true);

	currentDashDuration += dT;

	rb->setLinearVelocity(tr->forward() * dashSpeed);

	if (currentDashDuration >= dashDuration) {
		lastDash = 0;
		currentDashDuration = 0;
		isDashing = false;
		dashParticles->setActive(false);
	}
}

void LoveEngine::ECS::MovimientoJugador::moveTransform(float mv, Utilities::Vector4<float> rt, float dT)
{
	tr->translate(tr->forward() * mv * dT);
	rt.y *= dT;
	tr->rotate(rt);
}

void LoveEngine::ECS::MovimientoJugador::moveRigidbody(float mv, Utilities::Vector4<float> rt)
{
	Utilities::Vector3<float>newVelocity((tr->forward() * mv).x, (tr->forward() * mv).y + rb->getVelocity()->y, (tr->forward() * mv).z);

	rb->setLinearVelocity(newVelocity);

	Utilities::Vector3<float> rtToV3(rt.x, rt.y, rt.z);

	rb->setAngularVelocity(rtToV3);
}

void LoveEngine::ECS::MovimientoJugador::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("speed", speed);
	MAX_SPEED = speed;
	sf.tryGetFloat("rotSpeed", rotSpeed);
	sf.tryGetFloat("dashSpeed", dashSpeed);
	sf.tryGetFloat("dashDuration", dashDuration);
	sf.tryGetFloat("dashDelay", dashDelay);
}


