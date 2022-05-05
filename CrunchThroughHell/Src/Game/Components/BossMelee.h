#pragma once
#include "ComportamientoBoss.h"


namespace LoveEngine {

	namespace ECS {
        class Timer;
        class Sound;
        class Salud;
		class BossMelee : public ComportamientoBoss {
		protected:
#pragma region Actions
            Sound* meleeSound;
            Sound* roarSound;
            Sound* deathSound;
			class MeleeAttack : public Action
			{
			public:
                bool damaging = true;   // controla que un solo ataque no dañe en cada frame

				MeleeAttack(Agent* agent_);
				void setTarget(Transform* t);
				void setTransform(Transform* t);
				void setRB(RigidBody* rb_);
                void setAnim(Animation* a);
				bool conditionsFulfilled() const final;
				void onActionStart() final;
                void setSound(Sound* s) { meleeSound = s; }
                void attackOnRange();

			protected:
				RigidBody* rb;
                Animation* anim = nullptr;
				Transform* target = nullptr;
				Transform* tr = nullptr;
                Sound* meleeSound;
                float attackRange = 45.0f;
                float attackDmg = 10.0f;

                struct AttackAnimation {
                    std::string animation;
                    float duration;
                };

                AttackAnimation attackAnimations[3] = { { "attack1", 2.4 }, { "attack2", 1.5 }, { "attack3", 2.66 } };
                int numAnimations = 3;
                int comboIndex = 0;
            private:
                void attackFinished();
			};

            class Chase : public Action
            {
            public:
                Chase(Agent* agent_);
                void setTarget(Transform* t);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                void setAnim(Animation* a);
                void activeUpdate() final;
            protected:
                float maxVel = 40;
                float acc = 40;
                RigidBody* rb = nullptr;
                Transform* target = nullptr;
                Transform* tr = nullptr;
                Animation* anim = nullptr;
            };

            class Leap : public Action
            {
            public:
                bool landingEnabled = false;    // justo después de saltar no debe detectar aterrizaje

                Leap(Agent* agent_);
                void setTarget(Transform* t);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                void setAnim(Animation* a);
                bool conditionsFulfilled() const final;
                void onActionStart() final;
                void activeUpdate() final;

                void land();
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
                Animation* anim = nullptr;
            private:
                float minLeapDistance = 90;     // distancia mínima para realizar un salto
                float jumpDuration = 2.0;       // duración fija de los saltos
                void enableLanding();
                void recover();                 // después de aterrizar, tarda un momento en levantarse
            };

            class Roar : public Action
            {
            public:
                Roar(Agent* agent_);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                void setTarget(Transform* t);
                void setAnim(Animation* a);
                void onActionStart() final;
                void setSound(Sound* s) { roarSound = s; }
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
                Animation* anim = nullptr;
                Sound* roarSound;
            private:
                void startRoar();
                void endRoar();
            };

            class Death : public Action
            {
            public:
                Death(Agent* agent_);
                void setDeath(int p);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                void setTarget(Transform* t);
                void setAnim(Animation* a);
                void onActionStart() final;
                void setSound(Sound* s) { deathSound = s; }
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
                Animation* anim = nullptr;
                Sound* deathSound;
            private:
                void startDeath();
                void Died();
            };

#pragma endregion
            void setTargets() override;
		private:
			Transform* tr;
            MeleeAttack* attack;
            Leap* leap;
            Chase* chase;
            Roar* roar;
            Death* death;
            Salud* salud;

		public:
            BossMelee();
            void init() override;
            void enterCollision(GameObject* other) override;
            void update() override;
		};
	}
}
