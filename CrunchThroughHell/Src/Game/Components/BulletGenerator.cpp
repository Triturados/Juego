#include "BulletGenerator.h"
#include "Bullet.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Mesh.h"
#include "Material.h"
#include <GameTime.h>
#include <StringFormatter.h>
#include <Timer.h>
#include <Vector3.h>
#include <SceneManager.h>
#include <Scene.h>
#include <Sound.h>
#include <GameObject.h>
#include "ParticleSystem.h"

void LoveEngine::ECS::BulletGenerator::createBullet()
{
	Utilities::Vector3<float> pos;
	pos.x = area->x + rand() % ((int)area->z * 2);
	pos.z = tr->getPos()->z;
	pos.y = tr->getPos()->y;

	GameObject* bullet = LoveEngine::SceneManagement::SceneManager::getInstance()->getCurrentScene()->createGameObject("bullet");
	auto bulletTr = bullet->addComponent<Transform>();
	bulletTr->sendFormattedString("position: 0,0,0; scale: 3,3,3; rotation: 0,0,0");
	bulletTr->setPos(pos);
	auto bulletMesh = bullet->addComponent<Mesh>();
	bulletMesh->sendFormattedString("meshName: fireball.mesh");
	auto bulletRigid = bullet->addComponent<RigidBody>();
	bulletRigid->sendFormattedString("trigger: true; state: dynamic; mass: 1.0; shape: cube; restitution: 1.0; colliderScale: 3, 3, 3;");
	auto bulletB = bullet->addComponent<Bullet>();
	bulletB->sendFormattedString("direction: 0,0,1; velocity: 30.0; damage: 10;");
	auto bulletMat = bullet->addComponent<Material>();
	bulletMat->receiveComponent(0, bulletMesh);
	bulletMat->sendFormattedString("materialName: lava;");
	auto bulletSys = bullet->addComponent<ParticleSystem>();
	bulletSys->sendFormattedString("particleName: explosion; emitting: false");
	auto bulletSound = bullet->addComponent<Sound>();
	bulletSound->sendFormattedString("soundName: fireballimpact.wav; channel: music; loop: true; volume: 0.5; playNow: false;");
	bulletTr->init(); bulletMesh->init(); bulletRigid->init(); bulletB->init(); 
	bulletMat->init(); bulletSys->init(); bulletSound->init();
}

LoveEngine::ECS::BulletGenerator::BulletGenerator() : interval(0)
{
	area = new Utilities::Vector3<float>(0,0,0);
	timer = nullptr; tr = nullptr;
}

void LoveEngine::ECS::BulletGenerator::init()
{
	tr = gameObject->getComponent<Transform>();
	timer = ECS::Timer::repeat([&](ECS::Timer*) { createBullet(); }, interval);
}

void LoveEngine::ECS::BulletGenerator::update()
{
}

void LoveEngine::ECS::BulletGenerator::receiveMessage(Utilities::StringFormatter& message)
{
	Utilities::Vector3<float> v = *area;

	message.tryGetInt("interval", interval);
	message.tryGetVector3("area", v);

	area->x = v.x;
	area->y = v.y;
	area->z = v.z;
}
