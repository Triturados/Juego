#include "Shop.h"
#include <Button.h>
#include <SaveData.h>
#include <StringFormatter.h>
#include <sstream>

#include "Salud.h"
#include "AtaqueJugador.h"
#include "MovimientoJugador.h"
#include "Text.h"

bool LoveEngine::ECS::Shop::SAVEDATA = false;
bool LoveEngine::ECS::Shop::boss1justdefeated = false;

LoveEngine::ECS::Shop::Shop()
{
	currency = 2;
	health = speed = damage = 0;

	healthIncrement = 10;
	speedIncrement = 10;
	damageIncrement = 10;

	text = nullptr;

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

	if (boss1justdefeated)
		currency += 2;
}


LoveEngine::ECS::Shop::~Shop()
{
	LoveEngine::Utilities::SaveData data;
	std::cout << "Guardando la partida...\n";
	std::stringstream ss;
	ss << "saved:true;health:" << health << " ;speed: " << speed << ";damage:" << damage << ";currency:" << currency;
	data.saveData(path, ss.str());
}

void LoveEngine::ECS::Shop::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetInt("healthIncrement", healthIncrement);
	sf.tryGetInt("damageIncrement", damageIncrement);
	sf.tryGetInt("speedIncrement", speedIncrement);

	MovimientoJugador::MAX_SPEED = MovimientoJugador::initial_MAX_SPEED + speedIncrement * speed;
	AtaqueJugador::dmg = AtaqueJugador::initial_dmg + damageIncrement * damage;
	Salud::_MAX_HEALTH = Salud::initial_MAX_HEALTH + healthIncrement * health;
}

void LoveEngine::ECS::Shop::receiveComponent(int i, Component* b)
{
	Button* button = static_cast<Button*>(b);

	if (i == 0) {
		button->onClick([&]() {buyHealth(); });
		buttons.push_back(button);
		buttonsPos.push_back(button->getPosition().y);
	}
	else if (i == 1) {
		button->onClick([&]() {buyDamage(); });
		buttons.push_back(button);
		buttonsPos.push_back(button->getPosition().y);
	}
	else if (i == 2) {
		button->onClick([&]() {buySpeed(); });
		buttons.push_back(button);
		buttonsPos.push_back(button->getPosition().y);
	}
	else if (i == 3) {
		text = static_cast<Text*>(b);
	}

}

void LoveEngine::ECS::Shop::postInit()
{
	text->changeText("Souls: " + std::to_string(currency));
}

void LoveEngine::ECS::Shop::buyHealth()
{
	if (health >= maxPurchase || currency <= 0) return;
	health++;
	currency--;
	text->changeText("Souls: " + std::to_string(currency));

	Salud::_MAX_HEALTH = Salud::initial_MAX_HEALTH + healthIncrement * health;

}

void LoveEngine::ECS::Shop::buyDamage()
{
	if (damage >= maxPurchase || currency <= 0) return;
	damage++;
	currency--;
	text->changeText("Souls: " + std::to_string(currency));

	AtaqueJugador::dmg = AtaqueJugador::initial_dmg + damageIncrement * damage;
}

void LoveEngine::ECS::Shop::buySpeed()
{
	if (speed >= maxPurchase || currency <= 0) return;
	speed++;
	currency--;
	text->changeText("Souls: " + std::to_string(currency));


	MovimientoJugador::MAX_SPEED = MovimientoJugador::MAX_SPEED + speedIncrement * speed;
	MovimientoJugador::updateMaxSpeed();
}

void LoveEngine::ECS::Shop::setButtonsActive(bool set)
{

	if (!buttonsActive && set) {
		std::cout << "ACTIVANDO\n";
		int i = 0;
		for (Button* b : buttons) {
			Utilities::Vector3<int> currentPos = b->getPosition();
			Utilities::Vector3<int> newPos(currentPos.x, buttonsPos[i], currentPos.z);
			b->setPosition(newPos);
			i++;
		}
	}
	else if(buttonsActive && !set){
		std::cout << "DESACTIVANDO\n";
		int i = 0;
		for (Button* b : buttons) {
			Utilities::Vector3<int> currentPos = b->getPosition();
			Utilities::Vector3<int> newPos(currentPos.x, -3000, currentPos.z);
			b->setPosition(newPos);
			i++;
		}
	}
	buttonsActive = set;
}
