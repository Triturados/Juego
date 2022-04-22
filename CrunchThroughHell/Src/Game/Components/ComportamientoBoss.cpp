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
            attack = new MeleeAttack(this);
            addAction(attack);
            chase = new Chase(this);
            addAction(chase);
            leap = new Leap(this);
            addAction(leap);
        }

        void ComportamientoBoss::init()
        {
            tr = gameObject->getComponent<Transform>();
            RigidBody* rb = gameObject->getComponent<RigidBody>();
            attack->setTransform(tr);
            attack->setRB(rb);
            chase->setTransform(tr);
            chase->setRB(rb);
            leap->setTransform(tr);
            leap->setRB(rb);
            Agent::init();
        }

        void ComportamientoBoss::receiveComponent(int n, Component* c)
        {
            auto playerTr = static_cast<Transform*>(c);
            chase->setTarget(playerTr);
            attack->setTarget(playerTr);
            leap->setTarget(playerTr);
        }

        void ComportamientoBoss::update()
        {
            Agent::update();
            //esto esta aqui para poder hacer couts de debug
            //TO DO: remove this before final release
        }

#pragma region acciones

        ComportamientoBoss::MeleeAttack::MeleeAttack(Agent* agent_) : Action(agent_, 10.0)
        {
            increasePrioOverTime = 10.0;
        }

        void ComportamientoBoss::MeleeAttack::setTarget(Transform* t) { target = t; };

        void ComportamientoBoss::MeleeAttack::setTransform(Transform* t) { tr = t; };

        void ComportamientoBoss::MeleeAttack::setRB(RigidBody* rb_) { rb = rb_; };

        bool ComportamientoBoss::MeleeAttack::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return (*(target->getPos()) - *(tr->getPos())).magnitude() < 25;
        }

        void ComportamientoBoss::MeleeAttack::onActionStart()
        {
            std::cout << "\n\n\n\n\n\n\nAttacking at melee\n\n\n\n\n\n\n\n";
            setPriority(30.0);
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                throw new std::exception("Faltan referencias para una accion");
                return;
            }
            // TO DO: start animation
        }

        void ComportamientoBoss::MeleeAttack::activeUpdate()
        {
            // TO DO: lookat target
        }

        ComportamientoBoss::Chase::Chase(Agent* agent_) : Action(agent_, 0.0) { };

        void ComportamientoBoss::Chase::setTarget(Transform* t) { target = t; };

        void ComportamientoBoss::Chase::setTransform(Transform* t) { tr = t; };

        void ComportamientoBoss::Chase::setRB(RigidBody* rb_) { rb = rb_; };

        void ComportamientoBoss::Chase::activeUpdate()
        {
            if ((*(rb->getVelocity())).magnitude() < maxVel)
            {
                Vector3 targetPos = *(target->getPos());
                Vector3 pos = *(tr->getPos());

                //Vector3 vel = (targetPos - pos).getNormalized() * acc;
                //rb->setLinearVelocity(vel);

                Vector3 force = (targetPos - pos).getNormalized() * (acc / 10.0) * rb->getMass();
                rb->addForce(force, Vector3(0, 0, 0), ForceMode::IMPULSE);
                
                //lookat target
            }
        }

        ComportamientoBoss::Leap::Leap(Agent* agent_) : Action(agent_, 80)
        {
            increasePrioOverTime = 10;
        }

        void ComportamientoBoss::Leap::setTarget(Transform* t) { target = t; };

        void ComportamientoBoss::Leap::setTransform(Transform* t) { tr = t; };

        void ComportamientoBoss::Leap::setRB(RigidBody* rb_) { rb = rb_; };

        bool ComportamientoBoss::Leap::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return (*(target->getPos()) - *(tr->getPos())).magnitude() > 50;
        }

        void ComportamientoBoss::Leap::onActionStart()
        {
            std::cout << "\n\n\n\n\n\n\nLeaping\n\n\n\n\n\n\n\n";
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                throw new std::exception("Faltan referencias para una accion");
                return;
            }
            Vector3 hrzDistance = (*(target->getPos()) - *(tr->getPos()));
            hrzDistance.y = 0;

            // calculado despejando ecuaciones del MRUA
            // TO DO: calibrate calculation to fit game gravity
            float gravity = -1;
            float vertImpulse = jumpZenith * hrzImpulse / hrzDistance.magnitude() + (-1/2 * gravity) / hrzImpulse * hrzDistance.magnitude();
            
            hrzDistance.normalize();
            auto force = Vector3(hrzDistance.x * hrzImpulse, vertImpulse, hrzDistance.z * hrzImpulse);
            rb->addForce(force * rb->getMass(), Vector3(0, 0, 0), ForceMode::IMPULSE);

            //start animation

            lockAction = true;
        }

        void ComportamientoBoss::Leap::activeUpdate()
        {
            //TO DO: make height calculation relative to hitbox size, or some other way entirely
            if (rb->getVelocity()->y < 0 && tr->getPos()->y < 22) 
            {
                std::cout << "Grounded";
                rb->setLinearVelocity(Vector3(0, 0, 0));
                //TO DO: add recovery timer on landing
                setPriority(80);
                lockAction = false;
            }
            //end animation
        }
#pragma endregion
    }
}

