#include "CamFollow.h"
#include "GameObject.h"
#include "Transform.h"
#include "CameraComponent.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Input.h"
#include "Vector4.h"
#include "GameTime.h"
#include <StringFormatter.h>
#include <iostream>
#include <math.h>

void LoveEngine::ECS::CamFollow::init()
{
	cam = gameObject->getComponent<Camera>();
}

void LoveEngine::ECS::CamFollow::receiveMessage(Utilities::StringFormatter& sf)
{
	
}

void LoveEngine::ECS::CamFollow::update()
{
	cam->lookAt(*playerTr->getPos());
}

void LoveEngine::ECS::CamFollow::receiveGameObject(int n, GameObject* b)
{
	playerTr = b->getComponent<Transform>();
	std::cout << "hola entra COMPOENNTE escean dani" << std::endl;
}