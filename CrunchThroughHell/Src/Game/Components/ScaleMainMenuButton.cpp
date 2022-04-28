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
	float dist = Utilities::abs(button->getPos().y - height);

	if (dist > maxDistance) {
		button->setSize(Utilities::Vector2(0, 0));

		return;
	}

	float t = dist / maxDistance;

	Utilities::Vector2<int> size = originalScale;
	size = size * ( 1 - t );

	Utilities::Vector2<int> offset = Utilities::Vec3toVec2Int(button->getPos());



	button->setSize(size);
}

void LoveEngine::ECS::ScaleMainMenuButton::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("height", height);
	std::cout << height << "\n";
	sf.tryGetFloat("maxDistance", maxDistance);
}
