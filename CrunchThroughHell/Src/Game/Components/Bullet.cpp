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
#include "BossDistancia.h"
#include "BossMelee.h"
#include "MovimientoJugador.h"
#include "Timer.h"
#include "ParticleSystem.h"

void LoveEngine::ECS::Bullet::bulletDamage(GameObject* other)
{
	if(other->getComponent<Salud>())
		other->getComponent<Salud>()->takeDamage(damage);

	mesh->setVisibility(false);
	tr->setActive(false);
	rb->setActive(false);

	pSys->setActive(true);

	ECS::Timer::invoke([&](ECS::Timer*) {
		isDead = true;
		}, 0.8);
}

LoveEngine::ECS::Bullet::Bullet()
{
	dir = new Utilities::Vector3<float>(0, 0, 0);
	lastPos = new Utilities::Vector3<float>(0, 0, 0);
	damage = 0; tr = nullptr;
	vel = 0; mesh = nullptr;
	rb = nullptr; hitObject = nullptr;
	pSys = nullptr;
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
	pSys = gameObject->getComponent<ParticleSystem>();
}

void LoveEngine::ECS::Bullet::update()
{
	
	rb->setLinearVelocity(*dir * vel);

	Utilities::Vector3<float> angle = *lastPos - *tr->getPos();
	angle.normalize();
	float angleF = std::atan2(angle.x, angle.z);

	rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angleF);
	*lastPos = *tr->getPos();

	if (hit && rb->isActive()) bulletDamage(hitObject);
	if (isDead) gameObject->removeGameObject();
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

void LoveEngine::ECS::Bullet::setDir(Utilities::Vector3<float> dir_)
{
	*dir = dir_;
}

void LoveEngine::ECS::Bullet::enterCollision(GameObject* other)
{
	if (other->getComponent<BossDistancia>() ||
		other->getComponent<BossMelee>() || hit) return;

	hit = true;
	hitObject = other;
}
