#include "MoveUI.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Image.h"
#include "Button.h"
#include "StringFormatter.h"
//#include "Utils.h"

namespace LoveEngine {

	namespace Utilities {
		float cubicEaseOut(float t)
		{
			float inv = 1 - t;
			return 1 - (inv * inv * inv);
		}

		float lerp(float a, float b, float t)
		{
			return (1 - t) * a + t * b;
		}
	}

	LoveEngine::ECS::MoveUI::MoveUI()
	{
		t = 0;
		duration = 1;
		img = nullptr;
		button = nullptr;
	}

	void LoveEngine::ECS::MoveUI::init()
	{
		std::cout << "UNU";
		img = gameObject->getComponent<Image>();
		button = gameObject->getComponent<Button>();
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
			auto v = img->getPos();
			v.lerp(destination, Utilities::cubicEaseOut(tvalue));
			img->setPos(v);
		}

		if (button != nullptr) {
			auto v = button->getPos();
			v.lerp(destination, Utilities::cubicEaseOut(tvalue));
			button->setPos(v);
		}
	}

	void LoveEngine::ECS::MoveUI::receiveMessage(Utilities::StringFormatter& sf)
	{
		sf.tryGetFloat("duration", duration);
	}

	void LoveEngine::ECS::MoveUI::changeDestination(Utilities::Vector3<int> dest)
	{
		t = 0;
		destination = dest;
		enabled = true;
	}

}