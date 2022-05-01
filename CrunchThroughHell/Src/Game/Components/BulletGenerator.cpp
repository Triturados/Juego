#include "BulletGenerator.h"
#include "Bullet.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Mesh.h"
#include <GameTime.h>
#include <StringFormatter.h>
#include <Timer.h>

void LoveEngine::ECS::BulletGenerator::createBullet()
{
}

void LoveEngine::ECS::BulletGenerator::init()
{
	lastBullet = count = random = 0;
}

void LoveEngine::ECS::BulletGenerator::update()
{
	count = Time::getInstance()->frameCount;

	if (count >= lastBullet + interval) {
		count = lastBullet;
		createBullet();
	}
}

void LoveEngine::ECS::BulletGenerator::receiveMessage(Utilities::StringFormatter& message)
{
	message.tryGetInt("interval", interval);
}
