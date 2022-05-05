#include "ShopInteract.h"
#include "Shop.h"
#include "ShowText.h"
#include "Input.h"

void LoveEngine::ECS::ShopInteract::receiveComponent(int i, Component*c)
{
	Interactable::receiveComponent(i, c);
	if (i == 2)
		shop = (Shop*)c;

}

void LoveEngine::ECS::ShopInteract::notOnRangeCallBack()
{
	shop->setButtonsActive(false);
}

void LoveEngine::ECS::ShopInteract::use()
{

	if (input->keyJustPressed((Input::InputKeys)interactKey)) {
		texto->changeText(" ");
		shop->setButtonsActive(true);
	}
}
