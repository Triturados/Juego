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
	tr = gameObject->getComponent<Transform>();
	tr->translate(Utilities::Vector3<float>(0, 50, -50));
}

void LoveEngine::ECS::CamFollow::receiveMessage(Utilities::StringFormatter& sf)
{
	
}

void LoveEngine::ECS::CamFollow::update()
{
	cam->resetOrientation();
	cam->lookAt(*targetTr->getPos());
}

void LoveEngine::ECS::CamFollow::receiveComponent(int n, Component* c)
{
	if (dynamic_cast<Transform*>(c) != nullptr)
		targetTr = (Transform*)c;
}
