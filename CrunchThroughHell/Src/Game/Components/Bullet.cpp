#include "Bullet.h"
#include "Timer.h"
#include <iostream>
#include <string>
#include "GameObject.h"
#include "Transform.h"
#include "StringFormatter.h"
#include "Vector3.h"
#include "SaludJugador.h"
#include <RigidBody.h>
#include "Mesh.h"

LoveEngine::ECS::Bullet::Bullet()
{
	dir = new Utilities::Vector3<float>(0, 0, 0);
	damage = 0; tr = nullptr;
	vel = 0; mesh = nullptr;
}

LoveEngine::ECS::Bullet::~Bullet()
{
	delete dir;
}

void LoveEngine::ECS::Bullet::init()
{
	lifetime = Timer::deleteGameObject(gameObject, 10);
	tr = gameObject->getComponent<Transform>();
	dir->normalize();
	mesh = gameObject->getComponent<Mesh>();
	rb = gameObject->getComponent<RigidBody>();
}

void LoveEngine::ECS::Bullet::update()
{
	std::cout << "Este componente se autodestruira en: " << lifetime->timeLeft() << "\n";
	
	dir->x = dir->x * vel;
	dir->y = dir->y * vel;
	dir->z = dir->z * vel;

	tr->translate(*dir);
}

void LoveEngine::ECS::Bullet::receiveMessage(Utilities::StringFormatter& sf)
{
	Utilities::Vector3<float> direction = *dir;
	sf.tryGetVector3("direction", direction);
	sf.tryGetFloat("velocity", vel);
	sf.tryGetInt("damage", damage);

	dir->x = direction.x;
	dir->y = direction.y;
	dir->z = direction.z;
}

void LoveEngine::ECS::Bullet::enterCollision(GameObject* other)
{
	if (!other->getComponent<SaludJugador>()) return;

	other->getComponent<SaludJugador>()->takeDamage(damage);
	mesh->setVisibility(false);
	gameObject->removeGameObject();
}
