#include "ScaleMainMenuButton.h"
#include "Button.h"
#include "GameObject.h"
#include "StringFormatter.h"
#include "Utils.h"


LoveEngine::ECS::ScaleMainMenuButton::ScaleMainMenuButton()
{
	height = maxDistance = 0;
	button = nullptr;
	originalScale = Utilities::Vector2<int>();
}

void LoveEngine::ECS::ScaleMainMenuButton::init()
{
	button = gameObject->getComponent<Button>();

	if (button == nullptr || maxDistance <= 0) {
		remove();
		return;
	}

	originalScale = button->getSize();
}

void LoveEngine::ECS::ScaleMainMenuButton::setHeight(float h)
{
	height = h;
}

void LoveEngine::ECS::ScaleMainMenuButton::update()
{
	float dist = Utilities::abs(std::round(button->getPos().y + button->getSize().y * 0.5f) - height);

	if (dist > maxDistance) {
		button->setSize(Utilities::Vector2(0, 0));

		return;
	}

	float t = dist / maxDistance;
	Utilities::Vector2<int> size = originalScale;

	size = size * ( 1 - t );
	
	button->setSize(size);
}

void LoveEngine::ECS::ScaleMainMenuButton::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("height", height);
	sf.tryGetFloat("maxDistance", maxDistance);
}
