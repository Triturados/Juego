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

	playerTr = player->getComponent<Transform>(); //COMO ACCEDO A DOS GAMEOBJECTS AAAAAAA ESCENA DANIEL
	bossTr = boss->getComponent<Transform>();
	camTr = cam->getComponent<Transform>();
	
	mousePos = new Utilities::Vector2<float>(input->mousePosition().x, input->mousePosition().y);
	
	followBoss = true;
}

void LoveEngine::ECS::CamRotate::update()
{
	if (input->isKeyPressed(Input::InputKeys::SPACE)) followBoss = !followBoss;

	float dT = Time::getInstance()->deltaTime;
	Utilities::Vector4<float> rotation;

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

		std::cout << angulo << std::endl;
		if (angulo > 1) //No esta colocado
		{
			float speed = angulo / 180;
			if (speed < 0.4) speed = 0.4;


			if (girarDer)
			{
				std::cout << "giro der" << std::endl;
				rotation.y = horiSens * speed * dT;
			}
			else
			{
				std::cout << "giro izq" << std::endl;
				rotation.y = -horiSens * speed * dT;
			}

			if (antAngulo > angulo) //ESTO ES HORRIBLE 
			{
				girarDer = !girarDer;
			}
			antAngulo = angulo;
		}
	}
	else
	{
		if (!input->controllerConected()) //pad and mouse
		{
			delete mousePos;
			mousePos = new Utilities::Vector2<float>(input->mousePosition().x, input->mousePosition().y);

			float movementHorizontal = mousePos->x - input->mousePosition().x; 

			float movementVertical = mousePos->y - input->mousePosition().y;
			

			rotation.y = horiSens * movementHorizontal * dT;
			rotation.x = verSens * movementVertical * dT;

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
