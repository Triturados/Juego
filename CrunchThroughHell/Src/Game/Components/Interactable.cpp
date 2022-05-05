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

void LoveEngine::ECS::Interactable::postInit()
{
	textoOri = "PRESS \"E\" TO INTERACT";
	texto->changeText(" ");

}

void LoveEngine::ECS::Interactable::update()
{

	if (checkDistance()) {

		if (!justEntered) {
			justEntered = true;
			showMessage();
		}
		use();
	}
	else {
		notOnRangeCallBack();
		if (justEntered) {
			texto->changeText(" ");
			justEntered = false;
		}
	}

}

bool LoveEngine::ECS::Interactable::checkDistance()
{
	float distance = (*playerTr->getPos() - *tr->getPos()).magnitude();
	if (distance <= interactDistance) {
		return true;
	}

	return false;
}

void LoveEngine::ECS::Interactable::showMessage()
{
	texto->changeText(textoOri);

}

void LoveEngine::ECS::Interactable::receiveMessage(Utilities::StringFormatter& message)
{
	message.tryGetFloat("interactDistance", interactDistance);
}

void LoveEngine::ECS::Interactable::receiveComponent(int i, Component* c)
{
	if (i == 0)
		playerTr = (Transform*)c;

	if (i == 1)
		texto = (ShowText*)c;
}
