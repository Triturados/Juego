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

void LoveEngine::ECS::ScaleMainMenuButton::update()
{
	float dist = Utilities::abs(button->getPos().y - height);

	if (dist > maxDistance)
		return;

	float t = dist / maxDistance;

	Utilities::Vector2<int> size = originalScale;
	button->setSize(size);
}

void LoveEngine::ECS::ScaleMainMenuButton::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("height", height);
	sf.tryGetFloat("maxDistance", maxDistance);
}
