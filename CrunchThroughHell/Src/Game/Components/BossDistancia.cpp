#include "BossDistancia.h"
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
            rb->setMass(1000);
            attack->setTransform(tr);
            keepDistance->setTransform(tr);
            keepDistance->setRB(rb);
            teleport->setTransform(tr);
            teleport->setRB(rb);
            ComportamientoBoss::init();
        }

#pragma region acciones

        BossDistancia::RangedAttack::RangedAttack(Agent* agent_) : Action(agent_, 10.0)
        {
            // Aquí le asignais la velocidad de refresco del cooldown por segundo (más o menos) (lo será cuando meta bien el deltatime en agente)
            increasePrioOverTime = 10.0;
        }

        void BossDistancia::RangedAttack::setTarget(Transform* t) { target = t; };

        void BossDistancia::RangedAttack::setTransform(Transform* t) { tr = t; };


        bool BossDistancia::RangedAttack::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return (*(target->getPos()) - *(tr->getPos())).magnitude() > 25 &&
                (*(target->getPos()) - *(tr->getPos())).magnitude() < 50;
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
        }

        void BossDistancia::RangedAttack::activeUpdate()
        {
            // Esto es más estética que nada, para que mientras dure la animación esté apuntando al jugador
            // TO DO: lookat target
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

                //lookat target
                Utilities::Vector3<float> dir = targetPos - pos;
                dir.normalize();
                float angle = std::atan2(dir.x, dir.z);
                rb->setRotation(Utilities::Vector3<int>(0, 1, 0), angle);
            }
        }

        BossDistancia::Teleport::Teleport(Agent* agent_) : Action(agent_, 80)
        {
            increasePrioOverTime = 10.0;
        }

        void BossDistancia::Teleport::setTarget(Transform* t) { target = t; };

        void BossDistancia::Teleport::setTransform(Transform* t) { tr = t; };

        void BossDistancia::Teleport::setRB(RigidBody* rb_) { rb = rb_; };

        bool BossDistancia::Teleport::conditionsFulfilled() const
        {
            if (target == nullptr) return false;
            return (true /* Aquí poneis las condiciones necesarias para que haga teleport*/);
        }

        void BossDistancia::Teleport::onActionStart()
        {
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                throw new std::exception("Faltan referencias para una accion");
                return;
            }

            // Aquí poneis el código del teleport

            // Suponiendo que el teleport es instantáneo, no hay que bloquear la acción, y se puede poner en cd desde el
            // momento que empieza
            setPriority(80.0);
        }
#pragma endregion
    }
}

