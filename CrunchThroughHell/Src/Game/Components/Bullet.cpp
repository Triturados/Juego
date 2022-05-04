#include "Bullet.h"
#include "Timer.h"
#include <iostream>
#include <string>
#include "GameObject.h"
#include "Transform.h"
#include "StringFormatter.h"
#include "Vector3.h"
#include "Salud.h"
#include <RigidBody.h>
#include "Mesh.h"

void LoveEngine::ECS::Bullet::bulletDamage(GameObject* other)
{
	other->getComponent<Salud>()->takeDamage(damage);
	mesh->setVisibility(false);
	gameObject->removeGameObject();
}

LoveEngine::ECS::Bullet::Bullet()
{
	dir = new Utilities::Vector3<float>(0, 0, 0);
	lastPos = new Utilities::Vector3<float>(0, 0, 0);
	damage = 0; tr = nullptr;
	vel = 0; mesh = nullptr;
	rb = nullptr; hitObject = nullptr;
}

LoveEngine::ECS::Bullet::~Bullet()
{
	delete dir;
}

void LoveEngine::ECS::Bullet::init()
{
	lifetime = Timer::deleteGameObject(gameObject, 20);
	tr = gameObject->getComponent<Transform>();
	*lastPos = *tr->getPos();
	dir->normalize();
	mesh = gameObject->getComponent<Mesh>();
	rb = gameObject->getComponent<RigidBody>();
}

void LoveEngine::ECS::Bullet::update()
{
	//std::cout << "Este componente se autodestruira en: " << lifetime->timeLeft() << "\n";
	
	rb->setLinearVelocity(*dir * vel);

	Utilities::Vector3<float> angle = *lastPos - *tr->getPos();
	angle.normalize();
	float angleF = std::atan2(angle.x, angle.z);

	rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angleF);
	*lastPos = *tr->getPos();

	if (hit) bulletDamage(hitObject);
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

void LoveEngine::ECS::Bullet::colliding(GameObject* other)
{
	if (!other->getComponent<Salud>()) return;

	hit = true;
	hitObject = other;
}

void LoveEngine::ECS::Bullet::setDir(Utilities::Vector3<float> dir_)
{
	*dir = dir_;
}

void LoveEngine::ECS::Bullet::enterCollision(GameObject* other)
{
	if (!other->getComponent<Salud>()) return;

	hit = true;
	hitObject = other;
}
