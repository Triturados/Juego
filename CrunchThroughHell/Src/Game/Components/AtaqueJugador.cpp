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
#include "Stamina.h"
#include <Sound.h>
#include "Salud.h"


void LoveEngine::ECS::AtaqueJugador::init()
{
	input = Input::InputManager::getInstance();

	movement = gameObject->getComponent<MovimientoJugador>();

	particleSys = gameObject->getComponent<ParticleSystem>();

	anim = gameObject->getComponent<Animation>();

	tr = gameObject->getComponent<Transform>();

	sta = gameObject->getComponent<Stamina>();


	attackSound = gameObject->addComponent<Sound>();
	attackSound->sendFormattedString("soundName: dash.wav; channel: effects; loop: false; volume: 0.5; playNow: false;");
	attackSound->init();

}

void LoveEngine::ECS::AtaqueJugador::postInit() {
	comboIndex = 0;

	anim->setActive(false);
	anim->changeAnimation("attack3");
	anim->setActive(false);
	anim->setLoop(false);

	attackDuration = anim->getDuration();
	attackStamina = sta->getMaxStamina() / 6;
}

void LoveEngine::ECS::AtaqueJugador::update()
{
	float dT = Time::getInstance()->deltaTime;
	currentDuration += dT;

	if (isAttacking) attack();

	if (!input->controllerConected()) {
		if (input->mousePressed(Input::MouseState::CLICK_L) && currentDuration > attackDuration && sta->getStamina() >= attackStamina) startAttack();
	}
	else {
		//Utilities::Vector2 controller = input->getController().leftJoystick;


		//std::cout << controller << "\n";

		if (input->isControllerButtonPressed(Input::ControllerButton::A)&& sta->getStamina() >= attackStamina)
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

		else {}
	else if (i == 1)
		if (dynamic_cast<Salud*>(c) != nullptr)
			bossHealth = (Salud*)c;
		
}

void LoveEngine::ECS::AtaqueJugador::startAttack()
{
	if (comboIndex >= numAnimations) comboIndex = 0;
	std::string attackString = attackAnimations[comboIndex];
	++comboIndex;

	anim->changeAnimation(attackString);
	attackDuration = anim->getDuration();
	anim->resetAnim();

	currentDuration = 0;
	isAttacking = true;

	sta->loseStamina(attackStamina);

	originalSpeed = movement->getSpeed();
	movement->setSpeed(originalSpeed * speedReductionFactor);
}

void LoveEngine::ECS::AtaqueJugador::attack()
{
	if (currentDuration >= attackDuration / 2 && !hit) {
		hit = true;
		attackSound->playSound();
		if (bossOnRange()) {
			std::cout << "hit\n";
			bossHealth->takeDamage(dmg);
		}
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
	if (bossTr != nullptr) {
		Utilities::Vector3<float> bossPos = *bossTr->getPos();
		Utilities::Vector3<float> playerPos = *tr->getPos();
		Utilities::Vector3<float> dir = bossPos - playerPos;


		if (dir.magnitude() > attackDistance) return false;

		dir.normalize();
	}

	//CALCULAR ANGULO SOLO SI EL MOVIMIENTO ES LIBRE
	

	return true;;
}

bool LoveEngine::ECS::AtaqueJugador::currentlyAttacking()
{
	return isAttacking;
}


