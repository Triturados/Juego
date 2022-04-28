#include "Bullet.h"
#include "Timer.h"
#include <iostream>
#include "GameObject.h"
#include "Transform.h"
#include "StringFormatter.h"
#include "Vector3.h"
#include "SaludJugador.h"
#include "Mesh.h"

void LoveEngine::ECS::Bullet::init()
{
	lifetime = Timer::deleteGameObject(gameObject, 10);
	tr = gameObject->getComponent<Transform>();
	dir->normalize();
	mesh = gameObject->getComponent<Mesh>();
}

void LoveEngine::ECS::Bullet::update()
{
	std::cout << "Este componente se autodestruira en: " << lifetime->timeLeft() << "\n";

	if (gameObject->isEnabled())
		tr->translate(*dir * vel);
}

void LoveEngine::ECS::Bullet::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetVector3("direction", *dir);
	sf.tryGetFloat("velocity", vel);
	sf.tryGetInt("damage", damage);
}

void LoveEngine::ECS::Bullet::enterCollision(GameObject* other)
{
	if (!other->getComponent<SaludJugador>()) return;

	other->getComponent<SaludJugador>()->takeDamage(damage);
	mesh->setVisibility(false);
	gameObject->removeGameObject();
}
