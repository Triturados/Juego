#include "MoveUI.h"
#include "GameObject.h"
#include "GameTime.h"
#include "UIElement.h"
#include "StringFormatter.h"
#include "Utils.h"
#include "Window.h"

namespace LoveEngine {


	LoveEngine::ECS::MoveUI::MoveUI()
	{
		t = 0;
		duration = 1;
		element = nullptr;

		destination = origin = Utilities::Vector3<int>();

		shouldcenterX = false;
		centerx = -1;
		enabled = false;
	}

	void LoveEngine::ECS::MoveUI::init()
	{
		element = gameObject->getComponent<UIElement>();
		origin = element->getPosition();
	}

	void ECS::MoveUI::setDuration(float newduration)
	{
		duration = newduration;
	}

	void LoveEngine::ECS::MoveUI::update()
	{
		t += Time::getInstance()->deltaTime;
		if (t >= duration)
		{
			enabled = false;
			return;
		}

		float tvalue = t / duration;

		auto v = origin;
		v.lerp(destination, Utilities::cubicEaseOut(tvalue));

		if (shouldcenterX)
			v.x = centerx - (element->getSize().x * 0.5f);
		element->setPosition(v);
	}

	void LoveEngine::ECS::MoveUI::receiveMessage(Utilities::StringFormatter& sf)
	{
		sf.tryGetFloat("duration", duration);

		Utilities::Vector3<float> dest;
		if (sf.tryGetVector3("destination", dest)) {
			destination = (Utilities::Vector3<int>)dest;
		}

		if (sf.tryGetInt("centerX", centerx)) {
			shouldcenterX = true;
		}

		sf.tryGetBool("enabled", enabled);
	}

	Utilities::Vector3<int> ECS::MoveUI::getDestination()
	{
		return destination;
	}

	void LoveEngine::ECS::MoveUI::changeDestination(Utilities::Vector3<int> dest)
	{
		t = 0;
		destination = dest;
		enabled = true;

		origin = element->getPosition();
	}

}