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

}

void LoveEngine::ECS::MovimientoJugador::postInit() {

	if (hasRigidBody)rb->setAngularFactor(Utilities::Vector3<float>(0, 0, 0));

	dashParticles = tr->getChild(1)->gameObject->getComponent<ParticleSystem>();

	if (bossRb != nullptr) bossTr = bossRb->gameObject->getComponent<Transform>();
}

void LoveEngine::ECS::MovimientoJugador::update()
{
	movementZ = 0;
	movementX = 0;

	float dT = Time::getInstance()->deltaTime;
	lastDash += dT;

	if (!input->controllerConected()) {
		if (input->isKeyPressed(Input::InputKeys::W)) movementZ = speed;
		if (input->isKeyPressed(Input::InputKeys::S)) movementZ = -speed;
		if (input->isKeyPressed(Input::InputKeys::A)) movementX = speed;
		if (input->isKeyPressed(Input::InputKeys::D)) movementX = -speed;
		if (input->isKeyPressed(Input::InputKeys::SPACE) && lastDash >= dashDelay) isDashing = true;
		if (input->isKeyPressed(Input::InputKeys::R))
		{
			SceneManagement::changeScene(7, SceneManagement::SceneLoad::SWAP); //Ir escena muerte
		}
	}
	else {
		Utilities::Vector2 controller = input->getController().leftJoystick;

		movementZ = controller.y * speed;
		movementX = controller.x * speed;

		//std::cout << controller << "\n";

		if (input->isControllerButtonPressed(Input::ControllerButton::B) && input->isControllerButtonState(Input::ControllerButtonState::DOWN) && lastDash >= dashDelay)
		{
			isDashing = true;
		}
	}

	
	if (isDashing) currentDashDuration += dT;

}

void LoveEngine::ECS::MovimientoJugador::stepPhysics()
{
	if (isDashing)
		dash();
	else move(movementX, movementZ);
}

void LoveEngine::ECS::MovimientoJugador::dash()
{
	if (!dashParticles->isEmitting()) dashParticles->setActive(true);

	Utilities::Vector3<float> dashDir = *rb->getVelocity();
	dashDir.y = 0;
	dashDir.normalize();
	rb->setLinearVelocity(dashDir * dashSpeed);

	if (currentDashDuration >= dashDuration) {
		lastDash = 0;
		currentDashDuration = 0;
		isDashing = false;
		dashParticles->setActive(false);
	}
}


void LoveEngine::ECS::MovimientoJugador::move(float mvX, float mvZ)
{
	Utilities::Vector3<float>newVelocity = tr->forward() * mvZ + tr->right() * mvX;
	newVelocity.y = rb->getVelocity()->y;

	rb->setLinearVelocity(newVelocity);


	Utilities::Vector3<float> bossPos = *bossTr->getPos();
	Utilities::Vector3<float> playerPos = *tr->getPos();

	Utilities::Vector3<float> dir = bossPos - playerPos;
	dir.normalize();

	float angle = std::atan2(dir.x, dir.z);

	rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);
}

void LoveEngine::ECS::MovimientoJugador::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("speed", speed);
	MAX_SPEED = speed;
	sf.tryGetFloat("dashSpeed", dashSpeed);
	sf.tryGetFloat("dashDuration", dashDuration);
	sf.tryGetFloat("dashDelay", dashDelay);
}

void LoveEngine::ECS::MovimientoJugador::receiveComponent(int i, Component* c)
{
	if (dynamic_cast<RigidBody*>(c) != nullptr)
		bossRb = (RigidBody*)c;
}


