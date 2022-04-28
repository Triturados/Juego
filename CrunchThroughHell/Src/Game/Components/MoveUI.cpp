#include "MoveUI.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Image.h"
#include "Button.h"
#include "StringFormatter.h"
#include "Utils.h"
#include "Window.h"

namespace LoveEngine {


	LoveEngine::ECS::MoveUI::MoveUI()
	{
		t = 0;
		duration = 1;
		img = nullptr;
		button = nullptr;

		destination = origin = Utilities::Vector3<int>();

		enabled = false;
	}

	void LoveEngine::ECS::MoveUI::init()
	{
		if ((img = gameObject->getComponent<Image>()) != nullptr) {
			origin = img->getPos();
		}
		else if ((button = gameObject->getComponent<Button>()) != nullptr) {
			origin = button->getPos();
		}
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

		if (img != nullptr) {
			auto v = origin;
			v.lerp(destination, Utilities::cubicEaseOut(tvalue));
			img->setPos(v);
		}

		if (button != nullptr) {
			auto v = origin;
			v.lerp(destination, Utilities::cubicEaseOut(tvalue));

			v.x = (Window::getInstance()->getWindowSize().x - button->getSize().x) * 0.5f;

			button->setPos(v);
		}

	}

	void LoveEngine::ECS::MoveUI::receiveMessage(Utilities::StringFormatter& sf)
	{
		sf.tryGetFloat("duration", duration);

		Utilities::Vector3<float> dest;
		if (sf.tryGetVector3("destination", dest)) {
			destination = (Utilities::Vector3<int>)dest;
		}
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

		if (img != nullptr)
			origin = img->getPos();
		else if (button != nullptr)
			origin = button->getPos();
	}

}