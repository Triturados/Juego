#include "BossMelee.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"
#include "Vector4.h"
#include "GameTime.h"
#include <StringFormatter.h>
#include <iostream>
#include <Animation.h>
#include <Timer.h>

namespace LoveEngine
{
    namespace ECS
    {
        using Vector3 = Utilities::Vector3<float>;

        void BossMelee::setTargets()
        {
            attack->setTarget(target);
            chase->setTarget(target);
            leap->setTarget(target);
        }

        BossMelee::BossMelee()
        {
            attack = new MeleeAttack(this);
            addAction(attack);
            chase = new Chase(this);
            addAction(chase);
            leap = new Leap(this);
            addAction(leap);
        }

        void BossMelee::init()
        {
            tr = gameObject->getComponent<Transform>();
            anim = gameObject->getComponent<Animation>();
            RigidBody* rb = gameObject->getComponent<RigidBody>();
            rb->setMass(1000);
            attack->setTransform(tr);
            attack->setRB(rb);
            attack->setAnim(anim);
            chase->setTransform(tr);
            chase->setRB(rb);
            chase->setAnim(anim);
            leap->setTransform(tr);
            leap->setRB(rb);
            leap->setAnim(anim);
            ComportamientoBoss::init();
        }

#pragma region acciones

        BossMelee::MeleeAttack::MeleeAttack(Agent* agent_) : Action(agent_, 10.0)
        {
            increasePrioOverTime = 10.0;
        }

        void BossMelee::MeleeAttack::setTarget(Transform* t) { target = t; };

        void BossMelee::MeleeAttack::setTransform(Transform* t) { tr = t; };

        void BossMelee::MeleeAttack::setRB(RigidBody* rb_) { rb = rb_; }
        void BossMelee::MeleeAttack::setAnim(Animation* a) { anim = a; };

        bool BossMelee::MeleeAttack::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return (*(target->getPos()) - *(tr->getPos())).magnitude() < 25;
        }

        void BossMelee::MeleeAttack::onActionStart()
        {
            std::cout << "\n\n\n\n\n\n\nAttacking\n\n\n\n\n\n\n\n";
            setPriority(30.0);
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                throw new std::exception("Faltan referencias para una accion");
                return;
            }
            // TO DO: start animation
            //if (comboIndex >= numAnimations) comboIndex = 0;
            AttackAnimation attack = attackAnimations[comboIndex++ % numAnimations];
            //++comboIndex;

            if (!anim->playingAnimation(attack.animation))
                anim->changeAnimation(attack.animation);

            lockAction = true;

            ECS::Timer::invoke([&](ECS::Timer*) {
                attackFinished();
                }, attack.duration);
        }

        void BossMelee::MeleeAttack::attackFinished()
        {
            lockAction = false;
        }

        BossMelee::Chase::Chase(Agent* agent_) : Action(agent_, 0.0) { };

        void BossMelee::Chase::setTarget(Transform* t) { target = t; };

        void BossMelee::Chase::setTransform(Transform* t) { tr = t; };

        void BossMelee::Chase::setRB(RigidBody* rb_) { rb = rb_; };
        void BossMelee::Chase::setAnim(Animation* a) { anim = a; };

        void BossMelee::Chase::activeUpdate()
        {
            if ((*(rb->getVelocity())).magnitude() < maxVel)
            {
                Vector3 targetPos = *(target->getPos());
                Vector3 pos = *(tr->getPos());

                Vector3 force = (targetPos - pos).getNormalized() * (acc / 10.0) * rb->getMass();
                rb->addForce(force, Vector3(0, 0, 0), ForceMode::IMPULSE);
                
                //lookat target
                Utilities::Vector3<float> dir = targetPos - pos;
                dir.normalize();
                float angle = std::atan2(dir.x, dir.z);
                rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);

                anim->changeAnimation("walk");
                anim->setLoop(true);
            }
        }

        BossMelee::Leap::Leap(Agent* agent_) : Action(agent_, 80)
        {
            increasePrioOverTime = 10;
        }

        void BossMelee::Leap::setTarget(Transform* t) { target = t; };

        void BossMelee::Leap::setTransform(Transform* t) { tr = t; };

        void BossMelee::Leap::setRB(RigidBody* rb_) { rb = rb_; };
        void BossMelee::Leap::setAnim(Animation* a) { anim = a; };

        bool BossMelee::Leap::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return (*(target->getPos()) - *(tr->getPos())).magnitude() > 50;
        }

        void BossMelee::Leap::onActionStart()
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
            Utilities::Vector3<float> dir = *target->getPos() - *tr->getPos();
            dir.normalize();
            float angle = std::atan2(dir.x, dir.z);
            rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);

            anim->resetAnim();

            lockAction = true;
        }

        void BossMelee::Leap::activeUpdate()
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
            anim->changeAnimation("jump");
            anim->setLoop(true);
        }
#pragma endregion
    }
}

