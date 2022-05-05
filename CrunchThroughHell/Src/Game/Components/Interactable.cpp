#include "Interactable.h"
#include "Input.h"
#include "GameObject.h"
#include "Transform.h"
#include "StringFormatter.h"
#include "ShowText.h"

void LoveEngine::ECS::Interactable::init()
{
	input = Input::InputManager::getInstance();
	interactKey = (int)Input::InputKeys::E;

	tr = gameObject->getComponent<Transform>();
}

void LoveEngine::ECS::Interactable::update()
{
	if (playerTr != nullptr && tr != nullptr) {
		if (checkDistance()) {
			showMessage();
			use();
		}
	}
}

bool LoveEngine::ECS::Interactable::checkDistance()
{
		if ((*playerTr->getPos() - *tr->getPos()).magnitude() <= interactDistance) {
			return true;
		}

		return false;
}

void LoveEngine::ECS::Interactable::showMessage()
{

}

void LoveEngine::ECS::Interactable::receiveMessage(Utilities::StringFormatter& message)
{
	message.tryGetFloat("interactDistance", interactDistance);
}

void LoveEngine::ECS::Interactable::receiveComponent(int i , Component* c)
{
	if (i == 0)
		if (dynamic_cast<Transform*>(c) != nullptr)
			playerTr = (Transform*)c;

	if (i == 1)
		if (dynamic_cast<ShowText*>(c) != nullptr)
			texto= (ShowText*)c;
}
