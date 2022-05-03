#include "CamRotate.h"
#include "GameObject.h"
#include "Transform.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Input.h"
#include "Vector4.h"
#include "GameTime.h"
#include <StringFormatter.h>
#include <iostream>
#include <math.h>
#include <Window.h>

#define PI 3.14159265

LoveEngine::ECS::CamRotate::~CamRotate()
{

}

void LoveEngine::ECS::CamRotate::init()
{
	input = Input::InputManager::getInstance();

	playerTr = player->getComponent<Transform>();
	if(boss != nullptr)
	bossTr = boss->getComponent<Transform>();
	camTr = cam->getComponent<Transform>();
	
	
	followBoss = false;
}

void LoveEngine::ECS::CamRotate::update()
{
	gameObject->getComponent<Transform>()->setPos(*playerTr->getPos());
	if (input->keyJustPressed(Input::InputKeys::B) || (input->isControllerButtonPressed(Input::ControllerButton::Y) && input->isControllerButtonState(Input::ControllerButtonState::DOWN)))
	{
		if(bossTr != nullptr) followBoss = !followBoss;
		if (followBoss)
		{
			antAngulo = 180;
			cont = 0;
		}
	}

	float dT = Time::getInstance()->deltaTime;
	Utilities::Vector3<float> rotation;

	if (followBoss) //Line between player - boss girar cam hasta que pase por al recta en x z que forma con el player y el boss
	{
		Utilities::Vector3<float> puntoA = *playerTr->getPos(); //x y z para la recta, altura da igual
		Utilities::Vector3<float> puntoB = *bossTr->getPos();


		Utilities::Vector2<float> direccionPB;
		direccionPB.x = puntoB.x - puntoA.x;
		direccionPB.y = puntoB.z - puntoA.z;
		Utilities::Vector2<float> direccionCP;
		direccionCP.x = puntoA.x - camTr->getPos()->x;
		direccionCP.y = puntoA.z - camTr->getPos()->z;

		float supElem = (direccionCP.x * direccionPB.x) + (direccionCP.y * direccionPB.y);
		float infElem = (direccionCP.magnitude() * direccionPB.magnitude());
		float angulo  = acosf(supElem/infElem) * 180.0 / PI;



		if (angulo > 2) //No esta colocado
		{
			float speed = angulo / 180;
			if (speed < 0.3) speed = 0.3;


			if (girarDer)
			{
				rotation.y = -horiSens * speed * dT;
			}
			else
			{
				rotation.y = horiSens * speed * dT;
			}

			//std::cout << angulo << std::endl;

			if (antAngulo > angulo && cont < 2) //ESTO ES HORRIBLE 
			{
				girarDer = !girarDer;
			}

			antAngulo = angulo;
		}
		else
		{
			std::cout << "CAM COLOCADA " << std::endl;
		}

		cont++;
		//Permitir ligero movimiento a los lados
		if (!input->controllerConected()) //pad and mouse
		{
			//if (angulo < 10) //rango maximo de 10 por cada lado
			//{
			//	std::cout << "movimiento solo" << std::endl;
			//	float speed = angulo / 10;

			//	Utilities::Vector2<float> antPos = *mousePos;
			//	delete mousePos;
			//	mousePos = new Utilities::Vector2<float>(input->mousePosition().x, input->mousePosition().y);

			//	float movementHorizontal = mousePos->x - antPos.x;
			//	float movementVertical = mousePos->y - antPos.y;

			//	rotation.y = horiSens * movementHorizontal * dT * 0.1 * speed;
			//	rotation.x = verSens * movementVertical * dT * 0.1 * speed;
			//}

		}
		
	}
	else
	{
		if (!input->controllerConected()) //pad and mouse
		{

			float movementHorizontal = (float)input->relativeMousePosition().x;
			//float movementVertical = (float)input->relativeMousePosition().y;


			if (movementHorizontal <= 1 && movementHorizontal >= -1) movementHorizontal = 0;
			//if (movementVertical <= 1 && movementVertical >= -1) movementVertical = 0;
			//Limitar altura
			/*Utilities::Vector3<float> playerPos = *playerTr->getPos();
			Utilities::Vector3<float> camPos = *camTr->getPos();

			Utilities::Vector3<float> direccionCP;
			direccionCP.x = camPos.x - playerPos.x;
			direccionCP.y = camPos.y - playerPos.y;
			direccionCP.z = camPos.z - playerPos.z;
			Utilities::Vector3<float> direccionPS;
			direccionPS.y = playerPos.y;
			direccionPS.x = camPos.x;
			direccionPS.z = camPos.z;

			float angulo = calculateAngle(direccionCP, direccionPS);*/

			//float anguloX = calculateAngle(Utilities::Vector3<float>(direccionCP.x, 0, direccionCP.z), Utilities::Vector3<float>(1, 0, 0));

			//if (anguloX > 90) anguloX = 180 - anguloX;

			////std::cout << "angulo " << angulo << "mov vertical " << movementVertical << std::endl;
			//
			//float valorX = 90 / anguloX;
			//float valorZ = 1 - valorX;

			////std::cout << "anguloX: " << anguloX << "seno del angulo: " << valorX << std::endl;

			//if (angulo >= 40  && movementVertical > 0) //Limite superior
			//{
			//	rotation.x =/* valorX **/ verSens * movementVertical * dT * 0.1;
			//	//rotation.z = valorZ * verSens * movementVertical * dT * 0.1;
			//}
			//else if (angulo <= 3  && movementVertical < 0) //Limite inferior
			//{
			//	rotation.x =/* valorX **/ verSens * movementVertical * dT * 0.1;
			//	//rotation.z = valorZ * verSens * movementVertical * dT * 0.1;
			//}
			//else if (angulo > 3 && angulo < 40)
			//{
			//	rotation.x =/* valorX **/ verSens * movementVertical * dT * 0.1;
			//	//rotation.z = valorZ * verSens * movementVertical * dT * 0.1;
			//}

			rotation.y = horiSens * movementHorizontal * dT * 0.1;

			
		}
		else //Controller
		{
			Utilities::Vector2 controller = input->getController().rightJoystick;

			rotation.y = horiSens * controller.x * dT * 0.1;
		}
	}

	gameObject->getComponent<Transform>()->rotate(rotation);
}

void LoveEngine::ECS::CamRotate::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("verSens", verSens);
	sf.tryGetFloat("horiSens", horiSens);
}

float LoveEngine::ECS::CamRotate::calculateAngle(Utilities::Vector3<float> vectorA, Utilities::Vector3<float> vectorB)
{
	float supElem = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y) + (vectorA.z * vectorB.z);
	float infElem = (vectorA.magnitude() * vectorB.magnitude());
	
	
	return acosf(supElem / infElem) * 180.0 / PI;
}

void LoveEngine::ECS::CamRotate::receiveGameObject(int n, GameObject* b)
{
	if (n == 0)
	{
		boss = b;
	}
	else if (n == 1)
	{
		player = b;
	}
	else if (n == 2)
	{
		cam = b;
	}
}

void LoveEngine::ECS::CamRotate::onSceneUp()
{
	Window::getInstance()->mouseVisibility(false);
}

void LoveEngine::ECS::CamRotate::onSceneDown()
{
	Window::getInstance()->mouseVisibility(true);
}
