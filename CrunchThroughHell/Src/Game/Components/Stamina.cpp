#include "Stamina.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"

#include <StringFormatter.h>
#include <iostream>
#include <Slider.h>


#include <Input.h>
#include <GameTime.h>

void LoveEngine::ECS::Stamina::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetInt("maxStamina", _MAX_STAMINA);
}

void LoveEngine::ECS::Stamina::addHealth()
{
	actStamina++;
	if (actStamina > _MAX_STAMINA) actStamina = _MAX_STAMINA;
}

void LoveEngine::ECS::Stamina::init()
{
	input = Input::InputManager::getInstance();
	//assert

	tr = gameObject->getComponent<Transform>();
	//sliderBehind = gameObject->getComponent<Slider>();
	//assert

	actStamina = _MAX_STAMINA;

	if (sliderTop != nullptr)
		sliderTop->setDetectInput(false);
	if (sliderBehind != nullptr)
		sliderBehind->setDetectInput(false);

	if (sliderTop != nullptr)
		sliderTop->setVisibilityBg(false);
}

void LoveEngine::ECS::Stamina::setStamina(int sta)
{
	if (sta < 0) sta = 0;
	else if (sta > _MAX_STAMINA) sta = _MAX_STAMINA;
	actStamina = sta;


}

void LoveEngine::ECS::Stamina::receiveComponent(int i, Component* c)
{
	if (i == 0)
	{
		sliderTop = static_cast<Slider*>(c);
	}
	else if (i == 1)
	{
		sliderBehind = static_cast<Slider*>(c);
	}
}

// Metodo que tiene en cuenta el cooldown para afcetar a la vida
void LoveEngine::ECS::Stamina::loseStamina(int damage)
{
	restartStamina = 0;
	setStamina(getStamina() - damage);
}

LoveEngine::ECS::Stamina::~Stamina()
{

}


float LoveEngine::ECS::Stamina::naive_lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void LoveEngine::ECS::Stamina::update()
{
	if (actStamina < _MAX_STAMINA)
	{
		restartStamina += Time::getInstance()->deltaTime;

		if (restartStamina >= staminaTime)
		{
			setStamina(actStamina + 3);
		}
	}
	if (sliderTop != nullptr && sliderBehind != nullptr) {
		int barProgress = actStamina * sliderBehind->MAX_VALUE / _MAX_STAMINA;

		sliderTop->setProgress(barProgress);



		barProgress = naive_lerp(sliderBehind->getProgress(), barProgress, Time::getInstance()->deltaTime);

		sliderBehind->setProgress(barProgress);


	}


}

void LoveEngine::ECS::Stamina::stepPhysics()
{

}




