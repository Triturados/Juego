#include "SaludJugador.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"

#include <StringFormatter.h>
#include <iostream>
#include <Slider.h>


#include <Input.h>
#include <GameTime.h>

void LoveEngine::ECS::SaludJugador::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("cooldownTime", cooldownTime);
	sf.tryGetInt("maxHealth", _MAX_HEALTH);
}

void LoveEngine::ECS::SaludJugador::addHealth()
{
	actHealth++;
	if (actHealth > _MAX_HEALTH) actHealth = _MAX_HEALTH;
}

void LoveEngine::ECS::SaludJugador::init()
{
	input = Input::InputManager::getInstance();
	//assert

	tr = gameObject->getComponent<Transform>();
	slider = gameObject->getComponent<Slider>();
	//assert

	actHealth = _MAX_HEALTH;
	slider->setDetectInput(false);
	slider->setPos(Utilities::Vector3<int>(100,100, 1));	
}

void LoveEngine::ECS::SaludJugador::setHealth(int health)
{
	if (health < 0) health = 0;
	else if (health > _MAX_HEALTH) health = _MAX_HEALTH;
	actHealth = health;	


}

void LoveEngine::ECS::SaludJugador::addMaxHealth()
{
	_MAX_HEALTH++;
}

// Metodo que tiene en cuenta el cooldown para afcetar a la vida
void LoveEngine::ECS::SaludJugador::takeDamage(int damage)
{
	if (hitCooldown) return;

	setHealth(getHealth() - damage);
	hitCooldown = true;
	cooldownTime = _MAX_COOLDOWN_TIME;
}

LoveEngine::ECS::SaludJugador::~SaludJugador()
{

}


float naive_lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void LoveEngine::ECS::SaludJugador::update()
{
	//testeo
	if(input->keyJustPressed(Input::InputKeys::B)) {
		takeDamage(1);
	}

	int barProgress = actHealth * slider->MAX_VALUE / _MAX_HEALTH;
	
	barProgress = naive_lerp(slider->getProgress(), barProgress, Time::getInstance()->deltaTime);
	slider->setProgress(barProgress);
}

void LoveEngine::ECS::SaludJugador::stepPhysics()
{
	if (!hitCooldown) return;
	cooldownTime -= Time::getInstance()->deltaTime;
	if (cooldownTime < 0) hitCooldown = false;
}




