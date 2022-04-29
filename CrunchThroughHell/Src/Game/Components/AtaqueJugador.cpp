#include "AtaqueJugador.h"
#include "GameObject.h"
#include "Vector3.h"
#include "Input.h"
#include <StringFormatter.h>
#include <iostream>
#include "SceneManager.h"
#include "ComportamientoBoss.h"
#include "ParticleSystem.h"
#include "GameTime.h"
#include "Animation.h"
#include "Transform.h"
#include "MovimientoJugador.h"
#include "Random.h"


void LoveEngine::ECS::AtaqueJugador::init()
{
	input = Input::InputManager::getInstance();

	movement = gameObject->getComponent<MovimientoJugador>();

	particleSys = gameObject->getComponent<ParticleSystem>();

	anim = gameObject->getComponent<Animation>();

	tr = gameObject->getComponent<Transform>();
}

void LoveEngine::ECS::AtaqueJugador::postInit() {

	anim->changeAnimation("attack1");
	anim->setActive(false);
	anim->setLoop(false);

	attackDuration = anim->getDuration();
}

void LoveEngine::ECS::AtaqueJugador::update()
{
	float dT = Time::getInstance()->deltaTime;
	currentDuration += dT;

	if (isAttacking) attack();

	if (!input->controllerConected()) {
		if (input->mousePressed(Input::MouseState::CLICK_L) && currentDuration > attackDuration) startAttack();
	}
	else {
		//Utilities::Vector2 controller = input->getController().leftJoystick;


		//std::cout << controller << "\n";

		if (input->isControllerButtonPressed(Input::ControllerButton::A))
		{
			startAttack();
		}
	}


}


void LoveEngine::ECS::AtaqueJugador::receiveMessage(Utilities::StringFormatter& sf)
{
	//sf.tryGetFloat("speed", speed);
}

void LoveEngine::ECS::AtaqueJugador::receiveComponent(int i, Component* c)
{
	if (i == 0)
		if (dynamic_cast<Transform*>(c) != nullptr)
			bossTr = (Transform*)c;

}

void LoveEngine::ECS::AtaqueJugador::startAttack()
{

	std::string attackRnd = attackAnimations[Utilities::Random::randomBetween(0, 3)];
	anim->changeAnimation(attackRnd);
	attackDuration = anim->getDuration();
	anim->setActive(true);
	anim->setLoop(false);
	anim->resetAnim();
	currentDuration = 0;
	isAttacking = true;

	originalSpeed = movement->getSpeed();
	movement->setSpeed(originalSpeed * speedReductionFactor);
}

void LoveEngine::ECS::AtaqueJugador::attack()
{
	if (currentDuration >= attackDuration / 2 && !hit) {
		hit = true;
		if (bossOnRange())
			std::cout << "hit\n";
	}
	if (currentDuration >= attackDuration) {
		isAttacking = false;
		hit = false;
		anim->setActive(false);

		movement->setSpeed(originalSpeed);
	}
}

bool LoveEngine::ECS::AtaqueJugador::bossOnRange()
{
	Utilities::Vector3<float> bossPos = *bossTr->getPos();
	Utilities::Vector3<float> playerPos = *tr->getPos();
	Utilities::Vector3<float> dir = bossPos - playerPos;

	std::cout << dir.magnitude() << "\n";

	if (dir.magnitude() > attackDistance) return false;

	dir.normalize();

	//HACER SOLO SI EL MOVIMIENTO ES LIBRE
	//float angle = std::atan2(dir.x, dir.z) * 180 / 3.1416;
	//angle = angle % 360;
	//std::cout << angle << "\n\n\n";
	//
	//if (angle < -attackAngle || angle > attackAngle) return false;

	return true;;
}

bool LoveEngine::ECS::AtaqueJugador::currentlyAttacking()
{
	return isAttacking;
}


