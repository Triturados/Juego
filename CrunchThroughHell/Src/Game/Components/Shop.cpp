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

	if (SAVEDATA) {

		LoveEngine::Utilities::SaveData data;
		auto sf = data.readData(path);
		bool safeGameExist = false;

		if (sf.tryGetBool("saved", safeGameExist)) {


			std::cout << "Si que hay partida guardada\n";
			std::cout << sf.getRawMessage() << "\n";
			sf.tryGetInt("health", health);
			sf.tryGetInt("speed", speed);
			sf.tryGetInt("damage", damage);
			sf.tryGetInt("currency", currency);
		}
	}

	std::cout << "health: " << health << "\n";
	std::cout << "speed: " << speed << "\n";
	std::cout << "damage: " << damage << "\n";
	std::cout << "currency: " << currency << "\n";
}

LoveEngine::ECS::Shop::~Shop()
{
	LoveEngine::Utilities::SaveData data;
	std::cout << "Guardando la partida...\n";
	std::stringstream ss;
	ss << "saved:true;health:" << health << " ;speed: " << speed << ";damage:" << damage << ";currency:" << currency;
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
	else if (i == 2) {
		button->onClick([&]() {buySpeed(); });
	}
}

void LoveEngine::ECS::Shop::buyHealth()
{
	if (health >= maxPurchase || currency <= 0) return;
	health++;
	currency--;
	std::cout << "comprada vida\n";
}

void LoveEngine::ECS::Shop::buyDamage()
{
	if (damage >= maxPurchase || currency <= 0) return;
	damage++;
	currency--;
	std::cout << "comprado daño\n";
}

void LoveEngine::ECS::Shop::buySpeed()
{
	if (speed >= maxPurchase || currency <= 0) return;
	speed++;
	currency--;
	std::cout << "comprada velocidad\n";
}
