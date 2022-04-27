#include "AtaqueJugador.h"
#include "GameObject.h"
#include "Vector3.h"
#include "Input.h"
#include <StringFormatter.h>
#include <iostream>
#include "SceneManager.h"
#include "ComportamientoBoss.h"
#include "ParticleSystem.h"
#include "Animation.h"


void LoveEngine::ECS::AtaqueJugador::init()
{
	input = Input::InputManager::getInstance();

}

void LoveEngine::ECS::AtaqueJugador::postInit() {


}

void LoveEngine::ECS::AtaqueJugador::update()
{
		if (!input->controllerConected()) {
			//if (input->isKeyPressed(Input::InputKeys::W)) movementZ = speed;
	
		}
		else {
			Utilities::Vector2 controller = input->getController().leftJoystick;


			//std::cout << controller << "\n";

			if (input->isControllerButtonPressed(Input::ControllerButton::B))
			{
			
			}
		}


}


void LoveEngine::ECS::AtaqueJugador::receiveMessage(Utilities::StringFormatter& sf)
{
	//sf.tryGetFloat("speed", speed);
}

void LoveEngine::ECS::AtaqueJugador::receiveComponent(int i, Component* c)
{
	//if (i == 0)
	//	if (dynamic_cast<RigidBody*>(c) != nullptr)
	//		bossRb = (RigidBody*)c;

}




