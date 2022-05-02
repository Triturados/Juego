#pragma once
#include "ComportamientoBoss.h"


namespace LoveEngine {

	namespace ECS {
        class Timer;

		class BossMelee : public ComportamientoBoss {
		protected:
#pragma region Actions
			class MeleeAttack : public Action
			{
			public:
				MeleeAttack(Agent* agent_);
				void setTarget(Transform* t);
				void setTransform(Transform* t);
				void setRB(RigidBody* rb_);
                void setAnim(Animation* a);
				bool conditionsFulfilled() const final;
				void onActionStart() final;
               

			protected:
				RigidBody* rb;
                Animation* anim = nullptr;
				Transform* target = nullptr;
				Transform* tr = nullptr;

                struct AttackAnimation {
                    std::string animation;
                    float duration;
                };

                AttackAnimation attackAnimations[3] = { { "attack1", 1.3 }, { "attack2", 1.3 }, { "attack3", 1.3 } };
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
                float maxVel = 10;
                float acc = 10;
                RigidBody* rb = nullptr;
                Transform* target = nullptr;
                Transform* tr = nullptr;
                Animation* anim = nullptr;
            };

            class Leap : public Action
            {
            public:
                Leap(Agent* agent_);
                void setTarget(Transform* t);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                void setAnim(Animation* a);
                bool conditionsFulfilled() const final;
                void onActionStart() final;
                void activeUpdate() final;
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
                Animation* anim = nullptr;
            private:
                float hrzImpulse = 40.0;        // velocidad inicial en horizontal
                float jumpZenith = 20.0;        // altura del punto mas alto del salto
            };
#pragma endregion
            void setTargets() override;
		private:
			Transform* tr;
            MeleeAttack* attack;
            Leap* leap;
            Chase* chase;

		public:
            BossMelee();
            void init() override;
		};
	}
}
