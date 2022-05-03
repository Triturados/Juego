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
#include "ComportamientoBoss.h"
#include "Animation.h"
#include "Definitions.h"
#include "Stamina.h"
#include "AtaqueJugador.h"
#include <Sound.h>


void LoveEngine::ECS::MovimientoJugador::init()
{
	input = Input::InputManager::getInstance();
	//assert

	tr = gameObject->getComponent<Transform>();
	//assert

	rb = gameObject->getComponent<RigidBody>();
	hasRigidBody = rb != nullptr;

	sta = gameObject->getComponent<Stamina>();
	anim = gameObject->getComponent<Animation>();
	ataque = gameObject->getComponent<AtaqueJugador>();


	dashSound = gameObject->addComponent<Sound>();
	dashSound->sendFormattedString("soundName:dash.wav; channel: effects; loop: false; volume: 0.1; playNow: false;");
	dashSound->init();


}

void LoveEngine::ECS::MovimientoJugador::postInit() {

	anim->setActive(false);

	if (hasRigidBody)rb->setAngularFactor(Utilities::Vector3<float>(0, 0, 0));

	//EL DASH TIENE QUE SER HIJO DEL JUGADOR
	int indx = 0;
	while (tr->getChild(indx)->gameObject->getComponent<ParticleSystem>() == nullptr)
		indx++;
	dashParticles = tr->getChild(indx)->gameObject->getComponent<ParticleSystem>();

	if (bossRb != nullptr) bossTr = bossRb->gameObject->getComponent<Transform>();

	dashStamina = sta->getMaxStamina() / 10;
}

void LoveEngine::ECS::MovimientoJugador::update()
{

	if (!ataque->currentlyAttacking()) changeAnimations();

	movementZ = 0;
	movementX = 0;
	float dT = Time::getInstance()->deltaTime;
	lastDash += dT;
	lastKnockback += dT;

	if (!input->controllerConected()) {
		if (input->isKeyPressed(Input::InputKeys::W)) movementZ = speed;
		if (input->isKeyPressed(Input::InputKeys::S)) movementZ = -speed;
		if (input->isKeyPressed(Input::InputKeys::A)) movementX = speed;
		if (input->isKeyPressed(Input::InputKeys::D)) movementX = -speed;
		if (input->isKeyPressed(Input::InputKeys::SPACE) && sta->getStamina() >= dashStamina && !isDashing && lastDash >= dashDelay && (movementX != 0 || movementZ != 0))
		{


			lastDash = 0;
			sta->loseStamina(dashStamina);
			isDashing = true;
			currentDashDuration = 0;
			dashSound->playSound();
		}
		if (input->isKeyPressed(Input::InputKeys::R))
		{
			std::cout << "cambiando de escena" << std::endl;
			SceneManagement::changeScene((int)SceneOrder::Defeat, SceneManagement::SceneLoad::SWAP); //Ir escena muerte
		}
	}
	else {
		Utilities::Vector2 controller = input->getController().leftJoystick;

		movementZ = controller.y * speed;
		movementX = controller.x * speed;

		//std::cout << controller << "\n";

		if (input->isControllerButtonPressed(Input::ControllerButton::B) &&
			input->isControllerButtonState(Input::ControllerButtonState::DOWN) && sta->getStamina() >= dashStamina && !isDashing && lastDash >= dashDelay && (movementX != 0 || movementZ != 0))
		{
			sta->loseStamina(dashStamina);
			isDashing = true;
			currentDashDuration = 0;
		}
	}



	if (isDashing) currentDashDuration += dT;
	if (isKnockback) currentKnockbackDuration += dT;
}

void LoveEngine::ECS::MovimientoJugador::stepPhysics()
{
	if (isDashing)
		dash();
	else if (isKnockback) {
		if (trJefe != nullptr)
			//throw std::exception("received negative value");
			knockback();
	}
	else {
		if(bossTr != nullptr)
			aimedMovement(movementX, movementZ);
		else {
			freeMovement(movementX, movementZ);
		}
	}
}

void LoveEngine::ECS::MovimientoJugador::dash()
{
	if (!dashParticles->isEmitting()) dashParticles->setActive(true);

	Utilities::Vector3<float> dashDir = *rb->getVelocity();
	dashDir.y = 0;
	dashDir.normalize();
	rb->setLinearVelocity(dashDir * dashSpeed);

	if (currentDashDuration >= dashDuration) {
		currentDashDuration = 0;
		isDashing = false;
		dashParticles->setActive(false);
	}
}

void LoveEngine::ECS::MovimientoJugador::knockback()
{
	Utilities::Vector3<float> targetPos = *(trJefe->getPos());
	Utilities::Vector3<float> pos = *(tr->getPos());

	Utilities::Vector3<float> force = (pos - targetPos);
	force.y = 0;
	//std::cout << "fuerza aplicada" << force << std::endl;

	rb->addForce(force, Utilities::Vector3<float>(0, 0, 0), ForceMode::ACCELERATION);

	if (currentKnockbackDuration >= knockbackDuration) {
		lastKnockback = 0;
		currentKnockbackDuration = 0;
		isKnockback = false;
	}
}

void LoveEngine::ECS::MovimientoJugador::changeAnimations()
{
	if (movementX == 0 && movementZ == 0) {
		anim->changeAnimation("idle");
	}
	else if (movementX > abs(movementZ)) {
		anim->changeAnimation("runright");
	}
	else if (movementX<0 && abs(movementX) > abs(movementZ)) {
		anim->changeAnimation("runleft");
	}
	else if (movementZ > 0)anim->changeAnimation("run");
	else anim->changeAnimation("walkback");

	anim->setLoop(true);

}


void LoveEngine::ECS::MovimientoJugador::freeMovement(float mvX, float mvZ)
{
	Utilities::Vector3<float>newVelocity = tr->forward() * mvZ + tr->right() * mvX;
	newVelocity.y = rb->getVelocity()->y;

	rb->setLinearVelocity(newVelocity);

	Utilities::Vector3<float> camRot = *camTr->getRot();

	float angle = camRot.y + 3.1416;


	rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);
}

void LoveEngine::ECS::MovimientoJugador::aimedMovement(float mvX, float mvZ)
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
}

void LoveEngine::ECS::MovimientoJugador::receiveComponent(int i, Component* c)
{
	if (i == 0)
		if (dynamic_cast<RigidBody*>(c) != nullptr)
			bossRb = (RigidBody*)c;
	if (i != 0)
		if (dynamic_cast<Transform*>(c) != nullptr)
			camTr = (Transform*)c;
}

void LoveEngine::ECS::MovimientoJugador::enterCollision(GameObject* other)
{
	if (other->getComponent<ComportamientoBoss>() != nullptr && !isDashing) //Si con lo que hemos chocado es el boss
	{
		if (trJefe == nullptr) {
			trJefe = other->getComponent<Transform>();
		}
		isKnockback = true;
	}
}

void LoveEngine::ECS::MovimientoJugador::colliding(GameObject* other)
{
	if (other->getComponent<ComportamientoBoss>() != nullptr && !isDashing) //Si con lo que hemos chocado es el boss
	{
		if (trJefe == nullptr) {
			trJefe = other->getComponent<Transform>();
		}
		isKnockback = true;
	}
}



