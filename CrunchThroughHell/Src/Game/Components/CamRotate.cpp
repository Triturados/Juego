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

#define PI 3.14159265

LoveEngine::ECS::CamRotate::~CamRotate()
{
	delete mousePos;
}

void LoveEngine::ECS::CamRotate::init()
{
	input = Input::InputManager::getInstance();

	playerTr = player->getComponent<Transform>();
	bossTr = boss->getComponent<Transform>();
	camTr = cam->getComponent<Transform>();
	
	mousePos = new Utilities::Vector2<float>(input->mousePosition().x, input->mousePosition().y);
	
	followBoss = false;
}

void LoveEngine::ECS::CamRotate::update()
{
	gameObject->getComponent<Transform>()->setPos(*playerTr->getPos());
	if (input->keyJustPressed(Input::InputKeys::B)) followBoss = !followBoss;

	float dT = Time::getInstance()->deltaTime;
	Utilities::Vector4<float> rotation;

	if (followBoss) //Line between player - boss girar cam hasta que pase por al recta en x z que forma con el player y el boss
	{
		std::cout << "movimiento boss" << std::endl;
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

		if (angulo > 0.15) //No esta colocado
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

			//if (antAngulo < angulo) //ESTO ES HORRIBLE 
			//{
			//	std::cout << antAngulo << " < " << angulo << std::endl;
			//	girarDer = !girarDer;
			//}
			antAngulo = angulo;
		}


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
		else
		{

		}
	}
	else
	{
		if (!input->controllerConected()) //pad and mouse
		{
			Utilities::Vector2<float> antPos = *mousePos;
			delete mousePos;
			mousePos = new Utilities::Vector2<float>(input->mousePosition().x, input->mousePosition().y);

			float movementHorizontal = mousePos->x - antPos.x;
			float movementVertical = mousePos->y - antPos.y;

			//Limitar altura
			Utilities::Vector3<float> playerPos = *playerTr->getPos();
			Utilities::Vector3<float> camPos = *camTr->getPos();

			Utilities::Vector3<float> direccionCP;
			direccionCP.x = camPos.x - playerPos.x;
			direccionCP.y = camPos.y - playerPos.y;
			direccionCP.z = camPos.z - playerPos.z;
			Utilities::Vector3<float> direccionPS;
			direccionPS.y = playerPos.y;
			direccionPS.x = camPos.x;
			direccionPS.z = camPos.z;

			float supElem = (direccionCP.x * direccionPS.x) + (direccionCP.y * direccionPS.y) + (direccionCP.z * direccionPS.z);
			float infElem = (direccionCP.magnitude() * direccionPS.magnitude());
			float angulo = acosf(supElem / infElem) * 180.0 / PI;

			//std::cout << angulo << std::endl;
			if (angulo >= 40 && camPos.y > playerPos.y && movementVertical > 0) //Limite superior
			{
				rotation.x = verSens * movementVertical * dT * 0.1;
			}
			else if (angulo <= 3 && camPos.y > playerPos.y && movementVertical < 0) //Limite inferior
			{
				rotation.x = verSens * movementVertical * dT * 0.1;
			}
			else if (angulo >= 3 && angulo <= 40)
			{
				rotation.x = verSens * movementVertical * dT * 0.1;
			}

			rotation.y = horiSens * movementHorizontal * dT * 0.1;

			std::cout << "rot hori: " << rotation.y << " rot vertical: " << rotation.x << std::endl;
		}
		else //Controller
		{

		}
	}

	gameObject->getComponent<Transform>()->rotate(rotation);
}

void LoveEngine::ECS::CamRotate::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetFloat("verSens", verSens);
	sf.tryGetFloat("horiSens", horiSens);
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
