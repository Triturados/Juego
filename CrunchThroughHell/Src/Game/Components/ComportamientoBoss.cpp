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
        void ComportamientoBoss::init()
        {
            auto meleeAttack = new MeleeAttack(this);
            addAction(meleeAttack);
            auto chase = new Chase(this);
            addAction(chase);
            auto leap = new Leap(this);
            addAction(leap);
            /*
            auto player = receiveGameObject();
            meleeAttack->setTarget(player);
            chase->setTarget(player);
            leap->setTarget(player);
            */
            Agent::init();
        }

        ComportamientoBoss::MeleeAttack::MeleeAttack(Agent* agent_) : Action(agent_, 10.0)
        {
            rb = agent->gameObject->getComponent<RigidBody>();
            tr = agent->gameObject->getComponent<Transform>();
            increasePrioOverTime = 10.0;
        };

        void ComportamientoBoss::MeleeAttack::setTarget(Transform* t)
        {
            target = t;
        }

        bool ComportamientoBoss::MeleeAttack::conditionsFulfilled() const
        {
            if (target == nullptr) return true; // TO DO: Change true to false
            return (*(target->getPos()) - *(tr->getPos())).magnitude() < 10;
        }

        void ComportamientoBoss::MeleeAttack::onActionStart()
        {
            std::cout << "\n\n\n\n\n\n\nAttacking at melee\n\n\n\n\n\n\n\n";
            setPriority(30.0);
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                //throw new std::exception("Faltan referencias para una acción");
                return;
            }
            // TO DO: start animation
        }

        void ComportamientoBoss::MeleeAttack::activeUpdate()
        {
            // TO DO: lookat target
        }


        ComportamientoBoss::Idle::Idle(Agent* agent_) : Action(agent_, 8.0) {}

        void ComportamientoBoss::Idle::activeUpdate() { std::cout << "Idle\n"; }

        ComportamientoBoss::Chase::Chase(Agent* agent_) : Action(agent_, 0.0) { };

        void ComportamientoBoss::Chase::setTarget(Transform* t)
        {
            target = t;
        }

        void ComportamientoBoss::Chase::activeUpdate()
        {
            if ((*(rb->getVelocity())).magnitude() < maxVel)
            {
                Utilities::Vector3<float> targetPos = *(target->getPos());
                Utilities::Vector3<float> pos = *(tr->getPos());

                rb->addForce((targetPos - pos).getNormalized() * acc * rb->getMass(), Utilities::Vector3<float>(0, 0, 0), (int)ForceMode::ACCELERATION);
                //lookat target
            }
        }

        ComportamientoBoss::Leap::Leap(Agent* agent_) : Action(agent_, 80)
        {
            rb = agent->gameObject->getComponent<RigidBody>();
            tr = agent->gameObject->getComponent<Transform>();
            increasePrioOverTime = 10;
        }

        void ComportamientoBoss::Leap::setTarget(Transform* t)
        {
            target = t;
        }

        bool ComportamientoBoss::Leap::conditionsFulfilled() const
        {
            if (target == nullptr) return true; // TO DO: Change true to false
            return (*(target->getPos()) - *(tr->getPos())).magnitude() > 40;
        }

        void ComportamientoBoss::Leap::onActionStart()
        {
            std::cout << "\n\n\n\n\n\n\nLeaping\n\n\n\n\n\n\n\n";
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                //throw new std::exception("Faltan referencias para una acción");
                return;
            }

            //start animation
            rb->addForce(*(target->getPos()) - *(tr->getPos()) + Utilities::Vector3<float>(0, 10, 0), Utilities::Vector3<float>(0, 0, 0), (int)ForceMode::IMPULSE);
        }

        void ComportamientoBoss::Leap::activeUpdate()
        {
            setPriority(80);
            if (target == nullptr || rb == nullptr || tr == nullptr) return;
            // TO DO: remove these lines ^^^^
            if (rb->getVelocity()->y > 0 && rb->getVelocity()->y < 0.02)
                setPriority(80);
            //end animation
        }
    }
}

