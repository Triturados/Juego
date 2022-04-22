#include "EfectoEscenario.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"

#include <StringFormatter.h>
#include <iostream>
#include <Slider.h>

#include <Input.h>
#include <GameTime.h>
#include <Components/MovimientoJugador.h>
#include <Components/SaludJugador.h>

void LoveEngine::ECS::EfectoEscenario::receiveMessage(Utilities::StringFormatter& sf)
{
	int nEfect;
	sf.tryGetInt("type", nEfect);
	efect = (FloorEfects)nEfect;
}

void LoveEngine::ECS::EfectoEscenario::slowMovement(GameObject* jugador)
{
	MovimientoJugador* mj = jugador->getComponent<MovimientoJugador>();
	mj->setSpeed(mj->getSpeed() / 2.0f);
}

void LoveEngine::ECS::EfectoEscenario::doDamage(GameObject* jugador)
{
	//el metodo tiene cooldown
	jugador->getComponent<SaludJugador>()->takeDamage(1);
}

void LoveEngine::ECS::EfectoEscenario::recoverMovement(GameObject* jugador)
{
	MovimientoJugador* mj = jugador->getComponent<MovimientoJugador>();
	mj->setSpeed(mj->getMaxSpeed());
}

void LoveEngine::ECS::EfectoEscenario::init()
{
	tr = gameObject->getComponent<Transform>();
	//assert	
}

void LoveEngine::ECS::EfectoEscenario::colliding(GameObject* other)
{
	if (!other->getComponent<MovimientoJugador>()) return;
	switch (efect)
	{
	case LoveEngine::ECS::FloorEfects::LAVA:
		doDamage(other);
		break;
	case LoveEngine::ECS::FloorEfects::LODO:
		slowMovement(other);
		break;
	default:
		break;
	}

}

void LoveEngine::ECS::EfectoEscenario::exitCollision(GameObject* other)
{
	switch (efect)
	{
	case LoveEngine::ECS::FloorEfects::LAVA:
		break;
	case LoveEngine::ECS::FloorEfects::LODO:
		recoverMovement(other);
		break;
	default:
		break;
	}
}

LoveEngine::ECS::EfectoEscenario::~EfectoEscenario()
{

}

void LoveEngine::ECS::EfectoEscenario::update()
{

}




