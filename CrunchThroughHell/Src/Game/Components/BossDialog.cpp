#include "BossDialog.h"
#include "StringFormatter.h"
#include "Input.h"
#include "Conversation.h"
#include "ShowText.h"
#include "SceneManager.h"
#include "Definitions.h"
#include "Timer.h"
#include "SaveData.h"
#include "Shop.h"

bool LoveEngine::ECS::BossDialog::boss1Defeated = false;

void LoveEngine::ECS::BossDialog::init()
{
	Interactable::init();


	if (Shop::SAVEDATA) {
		Utilities::SaveData sd;
		auto sf = sd.readData("boss");
		sf.tryGetBool("defeated", boss1Defeated);
	}
}

void LoveEngine::ECS::BossDialog::use()
{
	if ((bossNum == 1 && converBoss1 == nullptr) || (bossNum == 2 && (converBoss2 == nullptr || alternateConverBoss2 == nullptr)))return;

	if (input->keyJustPressed((Input::InputKeys)interactKey)) {
		texto->changeText(" ");
		if (bossNum == 1) {
			if (!boss1Defeated && !converBoss1->isActive())
				Timer::invoke([&](Timer*) {converBoss1->start(); }, 0.5f);

			else if (boss1Defeated && !alternateConverBoss1->isActive())
				Timer::invoke([&](Timer*) {alternateConverBoss1->start(); }, 0.5f);

		}
		else if (bossNum == 2) {
			if (boss1Defeated && !converBoss2->isActive())
				Timer::invoke([&](Timer*) {converBoss2->start(); }, 0.5f);
			else if (!boss1Defeated && !alternateConverBoss2->isActive())
				Timer::invoke([&](Timer*) {alternateConverBoss2->start(); }, 0.5f);

		}
	}
}


void LoveEngine::ECS::BossDialog::receiveMessage(Utilities::StringFormatter& message)
{
	message.tryGetFloat("interactDistance", interactDistance);

	message.tryGetInt("bossNum", bossNum);

	message.tryGetBool("boss1Defeated", boss1Defeated);
}

void LoveEngine::ECS::BossDialog::receiveComponent(int i, Component* c)
{

	if (i == 2) {
		converBoss1 = (Conversation*)c;
		converBoss1->enabled = false;
		converBoss1->setCallBack([&]() {
			SceneManagement::changeScene((int)SceneOrder::Boss1,SceneManagement::SceneLoad::CLEAR);
			});
	}

	if (i == 3) {
		alternateConverBoss1 = (Conversation*)c;
		alternateConverBoss1->enabled = false;
	}

	if (i == 4) {
		converBoss2 = (Conversation*)c;
		converBoss2->enabled = false;
		converBoss2->setCallBack([&]() {
			SceneManagement::changeScene((int)SceneOrder::Boss2, SceneManagement::SceneLoad::CLEAR);
			});
	}

	if (i == 5) {
		alternateConverBoss2 = (Conversation*)c;
		alternateConverBoss2->enabled = false;

	}

	Interactable::receiveComponent(i, c);
}

void LoveEngine::ECS::BossDialog::notOnRangeCallBack()
{
	if ((bossNum == 1 && (converBoss1 == nullptr || alternateConverBoss1 == nullptr)) || (bossNum == 2 && (converBoss2 == nullptr || alternateConverBoss2 == nullptr)))return;

	if (bossNum == 1) {
		if (!boss1Defeated) {
			converBoss1->clearText();
			converBoss1->enabled = false;
		}
		else {
			alternateConverBoss1->clearText();
			alternateConverBoss1->enabled = false;
		}
	}
	else if (bossNum == 2) {
		if (boss1Defeated) {
			converBoss2->clearText();
			converBoss2->enabled = false;
		}
		else {
			alternateConverBoss2->clearText();
			alternateConverBoss2->enabled = false;
		}
	}
}
