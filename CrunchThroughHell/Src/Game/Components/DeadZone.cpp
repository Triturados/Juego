#include "DeadZone.h"
#include "GameObject.h"
#include "MovimientoJugador.h"
#include <iostream>
void LoveEngine::ECS::DeadZone::enterCollision(GameObject* other) 
{
	if (other->getComponent<MovimientoJugador>()) {
		other->removeGameObject();
		
	}
}
