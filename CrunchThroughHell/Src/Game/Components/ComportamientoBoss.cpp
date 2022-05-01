#include "ComportamientoBoss.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"
#include "Vector4.h"
#include "GameTime.h"
#include <StringFormatter.h>
#include <iostream>

namespace LoveEngine
{
    namespace ECS
    {
        using Vector3 = Utilities::Vector3<float>;

        ComportamientoBoss::ComportamientoBoss()
        {
        }

        void ComportamientoBoss::init()
        {
            tr = gameObject->getComponent<Transform>();
            Agent::init();
        }

        void ComportamientoBoss::postInit()
        {
            gameObject->getComponent<RigidBody>()->setAngularFactor(Utilities::Vector3<float>(0, 1, 0));
        }

        void ComportamientoBoss::receiveComponent(int n, Component* c)
        {
            target = static_cast<Transform*>(c);
            setTargets();
        }

        void ComportamientoBoss::update()
        {
            Agent::update();
            //esto esta aqui para poder hacer couts de debug
            //TO DO: remove this before final release
        }
    }
}

