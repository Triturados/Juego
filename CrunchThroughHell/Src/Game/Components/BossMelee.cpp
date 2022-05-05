#include "BossMelee.h"
#include <SceneManager.h>
#include <Definitions.h>
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
#include "Salud.h"
#include <Sound.h>

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
            roar->setTarget(target);
            death->setTarget(target);
        }

        BossMelee::BossMelee()
        {
            attack = new MeleeAttack(this);
            addAction(attack);
            chase = new Chase(this);
            addAction(chase);
            leap = new Leap(this);
            addAction(leap);
            roar = new Roar(this);
            addAction(roar);
            death = new Death(this);
            addAction(death);
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
            roar->setTransform(tr);
            roar->setRB(rb);
            roar->setAnim(anim);
            death->setTransform(tr);
            death->setRB(rb);
            death->setAnim(anim);
            ComportamientoBoss::init();

            Sound* meleeSound = gameObject->addComponent<Sound>();
            meleeSound->sendFormattedString("soundName: meleeSound.wav; channel: effects; loop: false; volume: 0.5; playNow: false;");
            meleeSound->init();

            attack->setSound(meleeSound);

            roarSound = gameObject->addComponent<Sound>();
            roarSound->sendFormattedString("soundName: roar.ogg; channel: effects; loop: false; volume: 0.5; playNow: false;");
            roarSound->init();

            roar->setSound(roarSound);

            deathSound = gameObject->addComponent<Sound>();
            deathSound->sendFormattedString("soundName: death.wav; channel: effects; loop: false; volume: 0.5; playNow: false;");
            deathSound->init();

            death->setSound(deathSound);

            salud = gameObject->getComponent<Salud>();
        }

        void BossMelee::enterCollision(GameObject* other)
        {
            //Esto tiene que estar aquí porque las acciones no pueden detectar colisiones
            
            // Descomentar esto si se arreglan las colisiones
            /*if (currentAction == leap && leap->landingEnabled)
            {
                std::cout << "Maybe landing?\n";
                auto otherTr = other->getComponent<Transform>();
                if (otherTr->getPos()->y < tr->getPos()->y)
                    leap->land();
            }
            else */if (currentAction == attack && attack->damaging)
            {
                auto hp = other->getComponent<Salud>();
                if (hp != nullptr)
                {
                    attack->damaging = false;
                    hp->takeDamage(10);
                }
            }
        }

        void BossMelee::update() {
            ComportamientoBoss::update();
            if (salud->isDead())
                death->setDeath(-1);
        }

#pragma region acciones


        BossMelee::MeleeAttack::MeleeAttack(Agent* agent_) : Action(agent_, 10.0)
        {
            increasePrioOverTime = 10.0;
        }

        void BossMelee::MeleeAttack::setTarget(Transform* t) { target = t; };

        void BossMelee::MeleeAttack::setTransform(Transform* t) { tr = t; };

        void BossMelee::MeleeAttack::setRB(RigidBody* rb_) { rb = rb_; }
        void BossMelee::MeleeAttack::setAnim(Animation* a) { anim = a; }

        bool BossMelee::MeleeAttack::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return (*(target->getPos()) - *(tr->getPos())).magnitude() < 25;
        }

        void BossMelee::MeleeAttack::onActionStart()
        {
            //std::cout << "\n\n\n\n\n\n\nAttacking\n\n\n\n\n\n\n\n";

            Timer::invoke([&](Timer*) {
                meleeSound->playSound();
                }, 1.0);

            rb->setLinearVelocity(Vector3(0, 0, 0));

            setPriority(30.0);
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                throw new std::exception("Faltan referencias para una accion");
                return;
            }

            AttackAnimation attack = attackAnimations[comboIndex++ % numAnimations];

            if (!anim->playingAnimation(attack.animation))
                anim->changeAnimation(attack.animation);

            anim->resetAnim();

            lockAction = true;

            ECS::Timer::invoke([&](ECS::Timer*) {
                attackFinished();
                }, attack.duration);

            std::cout << "ataque boss aaa" << std::endl;
            ECS::Timer::invoke([&](ECS::Timer*) {
                attackOnRange();
                }, attack.duration / 2.0f);

        }

        void BossMelee::MeleeAttack::attackOnRange()
        {
            if (!target) return;
            float distance = std::abs((*target->getPos() - *tr->getPos()).magnitude());
            if (distance < attackRange) {
                std::cout << "hit\n";
                Salud* playerHealth = target->gameObject->getComponent<Salud>();
                if (playerHealth) playerHealth->takeDamage(attackDmg);
            }
        }

        void BossMelee::MeleeAttack::attackFinished()
        {
            lockAction = false;
            damaging = true;
        }

        //-----------------------------------------------------------------------------------------------

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

        //-----------------------------------------------------------------------------------------------

        BossMelee::Leap::Leap(Agent* agent_) : Action(agent_, 140)
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
            return (*(target->getPos()) - *(tr->getPos())).magnitude() > minLeapDistance;
        }

        void BossMelee::Leap::onActionStart()
        {
            //std::cout << "\n\n\n\n\n\n\nLeaping: distance " << (*(target->getPos()) - *(tr->getPos())).magnitude() <<"\n\n\n\n\n\n\n\n";
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                throw new std::exception("Faltan referencias para una accion");
                return;
            }

            Vector3 hrzDistance = (*(target->getPos()) - *(tr->getPos()));
            hrzDistance.y = 0;
            Vector3 hrzImpulse = hrzDistance * (1 / jumpDuration);

            // calculado despejando ecuaciones del MRUA
            float gravity = rb->getGravity()->y;

            float vrtImpulse = -gravity * jumpDuration / 2;
            
            auto force = Vector3(hrzImpulse.x, vrtImpulse, hrzImpulse.z);
            rb->addForce(force * rb->getMass(), Vector3(0, 0, 0), ForceMode::IMPULSE);

            //start animation
            Utilities::Vector3<float> dir = *target->getPos() - *tr->getPos();
            dir.normalize();
            float angle = std::atan2(dir.x, dir.z);
            rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);

            anim->changeAnimation("jumpstart");
            anim->resetAnim();

            lockAction = true;

            // aseguramos que no detecte aterrizaje nada más saltar
            landingEnabled = false;
            ECS::Timer::invoke([&](ECS::Timer*) {
                enableLanding();
                }, 0.1);
        }

        void BossMelee::Leap::activeUpdate()
        {
            //std::cout << "Current height: " << tr->getPos()->y;
            if (rb->getVelocity()->y < 0 && tr->getPos()->y < 22)
                land();
        }

        void BossMelee::Leap::land()
        {
            landingEnabled = false;
            //std::cout << "Grounded\n";
            rb->setLinearVelocity(Vector3(0, 0, 0));

            ECS::Timer::invoke([&](ECS::Timer*) {
                recover();
                }, 2.5);
            //end animation
            anim->changeAnimation("jumpend");
            anim->setLoop(true);
        }

        void BossMelee::Leap::enableLanding()
        {
            //std::cout << "able to land\n";
            landingEnabled = true;
        }

        void BossMelee::Leap::recover()
        {
            setPriority(80);
            lockAction = false;
        }

        //-----------------------------------------------------------------------------------------------

        BossMelee::Roar::Roar(Agent* agent_) : Action(agent_, -10) { }

        void BossMelee::Roar::setTransform(Transform* t) { tr = t; };

        void BossMelee::Roar::setRB(RigidBody* rb_) { rb = rb_; };

        void BossMelee::Roar::setTarget(Transform* t) { target = t; }

        void BossMelee::Roar::setAnim(Animation* a) { anim = a; }
        
        void BossMelee::Roar::onActionStart()
        {
            std::cout << "Roaring\n\n\n\n\n\n\n\n";
            lockAction = true;
            Vector3 targetPos = *(target->getPos());
            Vector3 pos = *(tr->getPos());

            Utilities::Vector3<float> dir = targetPos - pos;
            dir.normalize();
            float angle = std::atan2(dir.x, dir.z);
            rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);

            anim->changeAnimation("idle");
            ECS::Timer::invoke([&](ECS::Timer*) {
                startRoar();
                }, 2.0);
        }

        void BossMelee::Roar::startRoar()
        {
            anim->changeAnimation("battlecry");
            roarSound->playSound();
            ECS::Timer::invoke([&](ECS::Timer*) {
                endRoar();
                }, 2.8);
        }

        void BossMelee::Roar::endRoar()
        {
            lockAction = false;
            // Solo se realiza esta acción una vez
            setPriority(LONG_MAX);
        }

        //---------------------------------------------------------------------------

        BossMelee::Death::Death(Agent* agent_) : Action(agent_, 300) { }

        void BossMelee::Death::setDeath(int p) { setPriority(p); };

        void BossMelee::Death::setTransform(Transform* t) { tr = t; };

        void BossMelee::Death::setRB(RigidBody* rb_) { rb = rb_; };

        void BossMelee::Death::setTarget(Transform* t) { target = t; }

        void BossMelee::Death::setAnim(Animation* a) { anim = a; }

        void BossMelee::Death::onActionStart()
        {
            std::cout << "Dying\n\n\n\n\n\n\n\n";
            lockAction = true;
            Vector3 targetPos = *(target->getPos());
            Vector3 pos = *(tr->getPos());

            Utilities::Vector3<float> dir = targetPos - pos;
            dir.normalize();
            float angle = std::atan2(dir.x, dir.z);
            rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);

            startDeath();
        }

        void BossMelee::Death::startDeath()
        {
            anim->changeAnimation("death");
            anim->setLoop(false);
            deathSound->playSound();
            ECS::Timer::invoke([&](ECS::Timer*) {
                Died();
                }, 4.5);
        }

        void BossMelee::Death::Died()
        {
            lockAction = true;
            // Solo se realiza esta acción una vez
            setPriority(-1);

            SceneManagement::changeScene((int)SceneOrder::Overworld, SceneManagement::SceneLoad::SWAP);
        }
#pragma endregion
}
}

