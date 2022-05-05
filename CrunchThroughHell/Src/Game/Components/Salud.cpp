#include "Salud.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"

#include <StringFormatter.h>
#include <iostream>
#include <Slider.h>


#include <Input.h>
#include <GameTime.h>

void LoveEngine::ECS::Salud::receiveMessage(Utilities::StringFormatter& sf)
{
	pos = new Utilities::Vector3<int>();
	sf.tryGetFloat("cooldownTime", cooldownTime);
	sf.tryGetInt("maxHealth", _MAX_HEALTH);
	sf.tryGetInt("posX", pos->x);
	sf.tryGetInt("posY", pos->y);
	sf.tryGetInt("posZ", pos->z);
}

void LoveEngine::ECS::Salud::addHealth()
{
	actHealth++;
	if (actHealth > _MAX_HEALTH) actHealth = _MAX_HEALTH;
}

void LoveEngine::ECS::Salud::init()
{
	input = Input::InputManager::getInstance();
	//assert

	tr = gameObject->getComponent<Transform>();
	//sliderBehind = gameObject->getComponent<Slider>();
	//assert

	actHealth = _MAX_HEALTH;
	//sliderBehind->setDetectInput(false);
	//sliderBehind->setPos(Utilities::Vector3<int>(100,100, 1));


}

void LoveEngine::ECS::Salud::postInit()
{
	sliderTop->setDetectInput(false);
	sliderBehind->setDetectInput(false);
}

void LoveEngine::ECS::Salud::setHealth(int health)
{
	if (health < 0) health = 0;
	else if (health > _MAX_HEALTH) health = _MAX_HEALTH;
	actHealth = health;	
	if (actHealth == 0) dead = true;
}

void LoveEngine::ECS::Salud::receiveComponent(int i, Component* c)
{
	if (i == 0)
	{
		std::cout << "Meto el  slider arriba" << "\n";
		sliderTop = static_cast<Slider*>(c);
	}
	else if (i == 1)
	{
		std::cout << "Meto el slider abajo" << "\n";
		sliderBehind = static_cast<Slider*>(c);
	}
}

void LoveEngine::ECS::Salud::addMaxHealth()
{
	_MAX_HEALTH++;
}

// Metodo que tiene en cuenta el cooldown para afcetar a la vida
void LoveEngine::ECS::Salud::takeDamage(int damage)
{
 	if (hitCooldown) return;

	setHealth(getHealth() - damage);
	hitCooldown = true;
	cooldownTime = _MAX_COOLDOWN_TIME;
}

LoveEngine::ECS::Salud::~Salud()
{

}


float naive_lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void LoveEngine::ECS::Salud::update()
{
	int barProgress = actHealth * sliderBehind->MAX_VALUE / _MAX_HEALTH;

	sliderTop->setProgress(barProgress);
	
	barProgress = naive_lerp(sliderBehind->getProgress(), barProgress, Time::getInstance()->deltaTime);
	sliderBehind->setProgress(barProgress);
}

void LoveEngine::ECS::Salud::stepPhysics()
{
	if (!hitCooldown) return;
	cooldownTime -= Time::getInstance()->deltaTime;
	if (cooldownTime < 0) hitCooldown = false;
}




