#include "Shop.h"
#include <Button.h>
#include <SaveData.h>
#include <StringFormatter.h>
#include <sstream>


bool LoveEngine::ECS::Shop::SAVEDATA = false;

LoveEngine::ECS::Shop::Shop()
{
	currency = 2;
	health = speed = damage = 0;

	if (!SAVEDATA) return;

	LoveEngine::Utilities::SaveData data;
	auto sf = data.readData(path);
	bool safeGameExist = false;

	if (sf.tryGetBool("saved", safeGameExist)) {

		sf.tryGetInt("health", health);
		sf.tryGetInt("speed", speed);
		sf.tryGetInt("damage", damage);
		sf.tryGetInt("currency", currency);
	}

}

LoveEngine::ECS::Shop::~Shop()
{
	LoveEngine::Utilities::SaveData data;

	std::stringstream ss;
	ss << "saved:true;health:" << health << " ;speed: " << speed << ";damage" << damage << ";currency:" << currency;
	data.saveData(path, ss.str());
}

void LoveEngine::ECS::Shop::receiveComponent(int i, Component* b)
{
	Button* button = static_cast<Button*>(b);

	if (i == 0) {
		button->onClick([&]() {buyHealth(); });
	}
	else if (i == 1) {
		button->onClick([&]() {buyDamage(); });
	}
	else if (i == 1) {
		button->onClick([&]() {buySpeed(); });
	}
}

void LoveEngine::ECS::Shop::buyHealth()
{
	if (health >= maxPurchase) return;
	health++;
}

void LoveEngine::ECS::Shop::buyDamage()
{
	if (health >= maxPurchase) return;
	damage++;
	
}

void LoveEngine::ECS::Shop::buySpeed()
{
	if (health >= maxPurchase) return;
	speed++;
}
