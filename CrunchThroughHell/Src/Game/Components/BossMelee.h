#pragma once
#include "ComportamientoBoss.h"


namespace LoveEngine {

	namespace ECS {
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
				bool conditionsFulfilled() const final;
				void onActionStart() final;
				void activeUpdate() final;
               

			protected:
				RigidBody* rb;
				Transform* target = nullptr;
				Transform* tr = nullptr;
			};

            class Chase : public Action
            {
            public:
                Chase(Agent* agent_);
                void setTarget(Transform* t);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                void activeUpdate() final;
            protected:
                float maxVel = 10;
                float acc = 10;
                RigidBody* rb = nullptr;
                Transform* target = nullptr;
                Transform* tr = nullptr;
            };

            class Leap : public Action
            {
            public:
                Leap(Agent* agent_);
                void setTarget(Transform* t);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                bool conditionsFulfilled() const final;
                void onActionStart() final;
                void activeUpdate() final;
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
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