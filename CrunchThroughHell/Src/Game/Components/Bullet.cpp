#include "Bullet.h"
#include "Timer.h"
#include <iostream>
#include "GameObject.h"
#include "RigidBody.h"
#include "Vector3.h"

void LoveEngine::ECS::Bullet::init()
{
	lifetime = Timer::deleteGameObject(gameObject, 10);
	if (gameObject->getComponent<RigidBody>()) mRb = gameObject->getComponent<RigidBody>();
	vel = new Utilities::Vector3<float>( 0, 10, 0 );
}

void LoveEngine::ECS::Bullet::update()
{
	std::cout << "Este componente se autodestruira en: " << lifetime->timeLeft() << "\n";

	if (gameObject->isEnabled()) {
		if (mRb != nullptr) {
			mRb->addForce(*vel, Utilities::Vector3<float>(0, 0, 0), ForceMode::FORCE);
		}
	}
}
