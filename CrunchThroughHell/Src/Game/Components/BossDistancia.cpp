#include "BossDistancia.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "GameTime.h"
#include <StringFormatter.h>
#include <iostream>
#include <SceneManager.h>
#include <Scene.h>
#include "Bullet.h"
#include "Material.h"
#include "Mesh.h"
#include "Salud.h"
#include "Timer.h"
#include "Animation.h"

namespace LoveEngine
{
    namespace ECS
    {
        using Vector3 = Utilities::Vector3<float>;

        void BossDistancia::setTargets()
        {
            attack->setTarget(target);
            keepDistance->setTarget(target);
            teleport->setTarget(target);
        }

        BossDistancia::BossDistancia()
        {
            attack = new RangedAttack(this);
            addAction(attack);
            keepDistance = new KeepDistance(this);
            addAction(keepDistance);
            teleport = new Teleport(this);
            addAction(teleport);
        }

        void BossDistancia::init()
        {
            tr = gameObject->getComponent<Transform>();
            RigidBody* rb = gameObject->getComponent<RigidBody>();
            anim = gameObject->getComponent<Animation>();
            rb->setMass(1000);
            attack->setTransform(tr);
            attack->setAnim(anim);
            keepDistance->setTransform(tr);
            keepDistance->setRB(rb);
            keepDistance->setAnim(anim);
            teleport->setTransform(tr);
            teleport->setRB(rb);
            teleport->setAnim(anim);
            
            ComportamientoBoss::init();
            vida = gameObject->getComponent<Salud>()->getHealth();
            lastVd = vida;
        }

#pragma region acciones

        BossDistancia::RangedAttack::RangedAttack(Agent* agent_) : Action(agent_, 10.0)
        {
            // Aquí le asignais la velocidad de refresco del cooldown por segundo (más o menos) 
            //(lo será cuando meta bien el deltatime en agente)
            increasePrioOverTime = 5.0;
        }

        void BossDistancia::RangedAttack::setTarget(Transform* t) { target = t; };

        void BossDistancia::RangedAttack::setTransform(Transform* t) { tr = t; };


        bool BossDistancia::RangedAttack::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return true; //dispara siempre
            //(*(target->getPos()) - *(tr->getPos())).magnitude() > 25 &&
            //(*(target->getPos()) - *(tr->getPos())).magnitude() < 50;
        }

        void BossDistancia::RangedAttack::onActionStart()
        {
            // Aquí activais el cooldown del ataque
            setPriority(30.0);
            if (target == nullptr || tr == nullptr)
            {
                throw new std::exception("Faltan referencias para una accion");
                return;
            }


            // TO DO: start animation
            SpellAnimation spell = spellAnimations[comboIndex++ % numAnimations];

            if (!anim->playingAnimation(spell.animation))
                anim->changeAnimation(spell.animation);

            anim->resetAnim();

            lockAction = true;

            ECS::Timer::invoke([&](ECS::Timer*) {
                attackFinished();
                }, spell.duration);

            createBullet(); //dispara
        }

        void BossDistancia::RangedAttack::activeUpdate()
        {
            // Esto es más estética que nada, para que mientras dure la animación esté apuntando al jugador
            // TO DO: lookat target
        }

        void BossDistancia::RangedAttack::setAnim(Animation* a)
        {
            anim = a;
        }

        void BossDistancia::RangedAttack::createBullet()
        {
            //calculamos la direccion de la bala
            Utilities::Vector3<float> dir = (*target->getPos() - *tr->getPos());
            dir.normalize();

            GameObject* bullet = LoveEngine::SceneManagement::SceneManager::getInstance()->getCurrentScene()->createGameObject("bullet");
            auto bulletTr = bullet->addComponent<Transform>();
            bulletTr->sendFormattedString("position: 0,0,0; scale: 3,3,3; rotation: 0,0,0");
            bulletTr->setPos(*tr->getPos());
            auto bulletMesh = bullet->addComponent<Mesh>();
            bulletMesh->sendFormattedString("meshName: fireball.mesh");
            auto bulletRigid = bullet->addComponent<RigidBody>();
            bulletRigid->sendFormattedString("trigger: true; state: dynamic; mass: 1.0; shape: cube; restitution: 1.0; colliderScale: 3, 3, 3;");
            auto bulletB = bullet->addComponent<Bullet>();
            bulletB->sendFormattedString("velocity: 30.0; damage: 10;");
            bulletB->setDir(dir);
            auto bulletMat = bullet->addComponent<Material>();
            bulletMat->receiveComponent(0, bulletMesh);
            bulletMat->sendFormattedString("materialName: lava;");
            bulletTr->init(); bulletMesh->init(); bulletRigid->init(); bulletB->init(); bulletMat->init();
        }

        void BossDistancia::RangedAttack::attackFinished()
        {
            lockAction = false;
        }

        BossDistancia::KeepDistance::KeepDistance(Agent* agent_) : Action(agent_, 0.0) { };

        void BossDistancia::KeepDistance::setTarget(Transform* t) { target = t; };

        void BossDistancia::KeepDistance::setTransform(Transform* t) { tr = t; };

        void BossDistancia::KeepDistance::setRB(RigidBody* rb_) { rb = rb_; };

        void BossDistancia::KeepDistance::activeUpdate()
        {
            if ((*(rb->getVelocity())).magnitude() < maxVel)
            {
                Vector3 targetPos = *(target->getPos());
                Vector3 pos = *(tr->getPos());

                // Aquí aplicais las fuerzas necesarias para que se mueva
                if ((*(target->getPos()) - *(tr->getPos())).magnitude() < 50) {
                    Vector3 force = (pos - targetPos).getNormalized() * (acc / 10.0) * rb->getMass();
                    rb->addForce(force, Vector3(0, 0, 0), ForceMode::IMPULSE);
                }
                else if ((*(target->getPos()) - *(tr->getPos())).magnitude() > 60) {
                    Vector3 force = (targetPos - pos).getNormalized() * (acc / 10.0) * rb->getMass();
                    rb->addForce(force, Vector3(0, 0, 0), ForceMode::IMPULSE);
                }

                //lookat target
                Utilities::Vector3<float> dir = targetPos - pos;
                dir.normalize();
                float angle = std::atan2(dir.x, dir.z);
                rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);

                anim->changeAnimation("walk");
                anim->setLoop(true);
            }
        }

        void BossDistancia::KeepDistance::onActionStart()
        {
            rb->setKinematic(false);
        }

        void BossDistancia::KeepDistance::setAnim(Animation* a)
        {
            anim = a;
        }

        BossDistancia::Teleport::Teleport(Agent* agent_) : Action(agent_, 80)
        {
            increasePrioOverTime = 20.0;
        }

        void BossDistancia::Teleport::setTarget(Transform* t) { target = t; };

        void BossDistancia::Teleport::setTransform(Transform* t) { tr = t; };

        void BossDistancia::Teleport::setRB(RigidBody* rb_) { rb = rb_; };

        bool BossDistancia::Teleport::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return (true);
        }

        void BossDistancia::Teleport::onActionStart()
        {
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                throw new std::exception("Faltan referencias para una accion");
                return;
            }
            lockAction = true;
            // Aquí poneis el código del teleport
            Utilities::Vector2<float> nv = posRand();
            Utilities::Vector3<float> np(nv.x, tr->getPos()->y, nv.y);
            tr->setPos(np);
            rb->setTransform(tr);
            Vector3 targetPos = *(target->getPos());
            Vector3 pos = *(tr->getPos());
            Utilities::Vector3<float> dir = targetPos - pos;
            dir.normalize();
            float angle = std::atan2(dir.x, dir.z);
            rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);
            ECS::Timer::invoke([&](ECS::Timer*) {
                startTP();
            }, 1.5);

            // Suponiendo que el teleport es instantáneo, no hay que bloquear la acción, y se puede poner en cd desde el
            // momento que empieza
        }
        void BossDistancia::Teleport::setAnim(Animation* a)
        {
            anim = a;
        }

        void BossDistancia::Teleport::startTP()
        {
            //animacion
            ECS::Timer::invoke([&](ECS::Timer*) {
                endTP();
            }, 2.8);
        }
        void BossDistancia::Teleport::endTP()
        {
            lockAction = false;
            setPriority(80.0);
        }
        Utilities::Vector2<float> BossDistancia::Teleport::posRand()
        {
            int x, y;

            x = numRandNegPos(150);
            y = numRandNegPos(150);
            return Utilities::Vector2<float>(x, y);
        }

        int BossDistancia::Teleport::numRandNegPos(int maxRand)
        {
            int random_sign, cordR;
            random_sign = (rand() % 2); // this randomly produces 0 or 1. if 0, change number to negative
            cordR = (rand() % maxRand);

            if (random_sign == 0) {
                cordR = -cordR;
            }

            return cordR;
        }


#pragma endregion
    }
}

