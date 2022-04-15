#include "SaludJugador.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"

#include <StringFormatter.h>
#include <iostream>
#include <Slider.h>


#include <Input.h>

void LoveEngine::ECS::SaludJugador::receiveMessage(Utilities::StringFormatter& sf)
{
	/*sf.tryGetFloat("speed", speed);
	sf.tryGetFloat("rotSpeed", rotSpeed);*/
}

void LoveEngine::ECS::SaludJugador::addHealth()
{
	actHealth++;
	if (actHealth > _MAX_HEALTH) actHealth = _MAX_HEALTH;
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

void LoveEngine::ECS::SaludJugador::init()
{
	input = Input::InputManager::getInstance();
	//assert

	tr = gameObject->getComponent<Transform>();
	//assert
	slider = gameObject->getComponent<Slider>();

	actHealth = _MAX_HEALTH;
	slider->setDetectInput(false);
	slider->setPos(100, 100);	
}

void LoveEngine::ECS::SaludJugador::update()
{
	if(input->keyJustPressed(Input::InputKeys::A)) {
		setHealth(getHealth() - 1);
	}

	int barProgress = actHealth * slider->MAX_VALUE / _MAX_HEALTH;
	slider->setProgress(barProgress);
}




