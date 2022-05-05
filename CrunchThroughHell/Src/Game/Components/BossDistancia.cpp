#include "BossDistancia.h"
#include "GameObject.h"
#include "Transform.h"
#include "SceneManager.h"
#include "Definitions.h"
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
#include "Sound.h"
#include "ParticleSystem.h"

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
            death->setTarget(target);
        }

        BossDistancia::BossDistancia()
        {
            attack = new RangedAttack(this);
            addAction(attack);
            keepDistance = new KeepDistance(this);
            addAction(keepDistance);
            teleport = new Teleport(this);
            addAction(teleport);
            death = new Death(this);
            addAction(death);
        }

        void BossDistancia::init()
        {
            tr = gameObject->getComponent<Transform>();
            RigidBody* rb = gameObject->getComponent<RigidBody>();
            anim = gameObject->getComponent<Animation>();
            int indx = 0;
            //DO: codigo defensivo --> tiene q ser hijo del boss las particulas
            while (tr->getChild(indx)->gameObject->getComponent<ParticleSystem>() == nullptr)
                indx++;

            ParticleSystem* ps = tr->getChild(indx)->gameObject->getComponent<ParticleSystem>();
            indx++;

            while (tr->getChild(indx)->gameObject->getComponent<ParticleSystem>() == nullptr)
                indx++;
            pSys = tr->getChild(indx)->gameObject->getComponent<ParticleSystem>();

            rb->setMass(1000);
            attack->setTransform(tr);
            attack->setAnim(anim);
            attack->setParticleSys(pSys);
            keepDistance->setTransform(tr);
            keepDistance->setRB(rb);
            keepDistance->setAnim(anim);
            teleport->setTransform(tr);
            teleport->setRB(rb);
            teleport->setAnim(anim);
            teleport->setPartSys(ps);
            death->setTransform(tr);
            death->setRB(rb);
            death->setAnim(anim);

            
            ComportamientoBoss::init();
            vida = gameObject->getComponent<Salud>()->getHealth();
            lastVd = vida;

            deathSound = gameObject->addComponent<Sound>();
            deathSound->sendFormattedString("soundName: boss2death.mp3; channel: effects; loop: false; volume: 0.5; playNow: false;");
            deathSound->init();

            death->setSound(deathSound);

            teleportSound = gameObject->addComponent<Sound>();
            teleportSound->sendFormattedString("soundName: Teleport.wav; channel: effects; loop: false; volume: 0.8; playNow: false;");
            teleportSound->init();

            teleport->setSound(teleportSound);

            salud = gameObject->getComponent<Salud>();
        }

        void BossDistancia::update()
        {
            ComportamientoBoss::update();
            if (salud->isDead())
                death->setDeath(-1);
        }


#pragma region acciones

        BossDistancia::RangedAttack::RangedAttack(Agent* agent_) : Action(agent_, 10.0)
        {
            // Aquí le asignais la velocidad de refresco del cooldown por segundo (más o menos) 
            //(lo será cuando meta bien el deltatime en agente)
            increasePrioOverTime = 10.0;
        }

        void BossDistancia::RangedAttack::setTarget(Transform* t) { target = t; };

        void BossDistancia::RangedAttack::setTransform(Transform* t) { tr = t; };


        bool BossDistancia::RangedAttack::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return true; //dispara siempre
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

            SpellAnimation spell = spellAnimations[comboIndex++ % numAnimations];

            if (!anim->playingAnimation(spell.animation))
                anim->changeAnimation(spell.animation);

            anim->resetAnim();

            lockAction = true;

            if(!pSys->isEmitting())
            pSys->setActive(true);

            ECS::Timer::invoke([&](ECS::Timer*) {
                attackFinished();
                }, spell.duration);

            ECS::Timer::invoke([&](ECS::Timer*) {
                createBullets();
                }, spell.duration / 2);
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

        void BossDistancia::RangedAttack::setParticleSys(ParticleSystem* p) { pSys = p; };

        void BossDistancia::RangedAttack::shotOneBullet(Utilities::Vector3<float> dir_)
        {
            GameObject* bullet = LoveEngine::SceneManagement::SceneManager::getInstance()->getCurrentScene()->createGameObject("bullet");
            auto bulletTr = bullet->addComponent<Transform>();
            bulletTr->sendFormattedString("position: 0,0,0; scale: 3,3,3; rotation: 0,0,0");
            bulletTr->setPos(*tr->getPos() + (dir_ * 10));
            auto bulletMesh = bullet->addComponent<Mesh>();
            bulletMesh->sendFormattedString("meshName: fireball.mesh");
            auto bulletRigid = bullet->addComponent<RigidBody>();
            bulletRigid->sendFormattedString("trigger: true; mass: 1.0; shape: cube; restitution: 1.0; colliderScale: 5, 5, 5;");
            auto bulletB = bullet->addComponent<Bullet>();
            bulletB->sendFormattedString("velocity: 30.0; damage: 10;");
            dir_.y += 0.05;
            bulletB->setDir(dir_);
            auto bulletMat = bullet->addComponent<Material>();
            bulletMat->receiveComponent(0, bulletMesh);
            bulletMat->sendFormattedString("materialName: lava;");
            auto bulletSys = bullet->addComponent<ParticleSystem>();
            bulletSys->sendFormattedString("particleName: explosion; emitting: false");
            auto bulletSound = bullet->addComponent<Sound>();
            bulletSound->sendFormattedString("soundName: Bullet.wav; channel: music; loop: true; volume: 0.5; playNow: false;");
            bulletTr->init(); bulletMesh->init(); bulletRigid->init(); bulletB->init(); bulletMat->init();
            bulletSys->init(); bulletSound->init();
        }

        void BossDistancia::RangedAttack::createBullets()
        {
            //calculamos la direccion de la bala

            Utilities::Vector3<float> dir = (*target->getPos() - *tr->getPos());
            Utilities::Vector3<float> dir1 = dir;
            Utilities::Vector3<float> dir2 = dir;

            float theta = 20 * 3.14 / 180.0;

            float cs = cos(theta);
            float sn = sin(theta);

            dir1.x = dir.x * cs - dir.z * sn;
            dir1.z = dir.x * sn + dir.z * cs;

            float theta1 = -20 * 3.14 / 180.0;

            float cs1 = cos(theta1);
            float sn1 = sin(theta1);

            dir2.x = dir.x * cs1 - dir.z * sn1;
            dir2.z = dir.x * sn1 + dir.z * cs1;

            dir.normalize();
            shotOneBullet(dir);

            dir1.normalize();
            shotOneBullet(dir1);

            dir2.normalize();
            shotOneBullet(dir2);

            pSys->setActive(false);
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
            increasePrioOverTime = 3.0;
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
            anim->changeAnimation("teleport");
            float dur = anim->getDuration();
            anim->setLoop(true);
            particleTP();

            teleportSound->playSound();

            ECS::Timer::invoke([&](ECS::Timer*) {
                startTP();
            }, dur);

            // Suponiendo que el teleport es instantáneo, no hay que bloquear la acción, y se puede poner en cd desde el
            // momento que empieza
        }
        void BossDistancia::Teleport::setAnim(Animation* a)
        {
            anim = a;
        }

        void BossDistancia::Teleport::setPartSys(ParticleSystem* ps_)
        {
            tpParticles = ps_;
        }

        void BossDistancia::Teleport::particleTP()
        {
            if (!tpParticles->isEmitting()) tpParticles->setActive(true);
        }

        void BossDistancia::Teleport::startTP()
        {
            Utilities::Vector2<float> nv = posRand();
            Utilities::Vector3<float> np(nv.x, tr->getPos()->y, nv.y);
            tpParticles->setActive(false);
            tr->setPos(np);
            rb->setTransform(tr);
            Vector3 targetPos = *(target->getPos());
            Vector3 pos = *(tr->getPos());
            Utilities::Vector3<float> dir = targetPos - pos;
            dir.normalize();
            float angle = std::atan2(dir.x, dir.z);
            rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);
            //animacion
            anim->changeAnimation("idle");
            endTP();
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

        //---------------------------------------------------------------------------

        BossDistancia::Death::Death(Agent* agent_) : Action(agent_, 300) { }

        void BossDistancia::Death::setDeath(int p) { setPriority(p); };

        void BossDistancia::Death::setTransform(Transform* t) { tr = t; };

        void BossDistancia::Death::setRB(RigidBody* rb_) { rb = rb_; };

        void BossDistancia::Death::setTarget(Transform* t) { target = t; }

        void BossDistancia::Death::setAnim(Animation* a) { anim = a; }

        void BossDistancia::Death::onActionStart()
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

        void BossDistancia::Death::startDeath()
        {
            anim->changeAnimation("death");
            anim->setLoop(false);
            deathSound->playSound();
            ECS::Timer::invoke([&](ECS::Timer*) {
                Died();
                }, 3.8);
        }

        void BossDistancia::Death::Died()
        {
            lockAction = true;
            // Solo se realiza esta acción una vez
            setPriority(-1);

            SceneManagement::changeScene((int)SceneOrder::Victory, SceneManagement::SceneLoad::SWAP);
        }
#pragma endregion
    }
}

