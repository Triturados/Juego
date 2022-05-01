#pragma once
#include "ComportamientoBoss.h"


namespace LoveEngine {

	namespace ECS {
		class BossDistancia : public ComportamientoBoss {
		protected:
#pragma region Actions
			class RangedAttack : public Action
			{
			public:
                RangedAttack(Agent* agent_);
				void setTarget(Transform* t);
				void setTransform(Transform* t);
				bool conditionsFulfilled() const final;
				void onActionStart() final;
				void activeUpdate() final;
               

			protected:
				Transform* target = nullptr;
				Transform* tr = nullptr;
			};

            class KeepDistance : public Action
            {
            public:
                KeepDistance(Agent* agent_);
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

            class Teleport : public Action
            {
            public:
                Teleport(Agent* agent_);
                void setTarget(Transform* t);
                void setTransform(Transform* t);
                void setRB(RigidBody* rb_);
                bool conditionsFulfilled() const final;
                void onActionStart() final;
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
            };
#pragma endregion
            void setTargets() override;
		private:
			Transform* tr;
            RangedAttack* attack;
            KeepDistance* keepDistance;
            Teleport* teleport;

		public:
            BossDistancia();
            void init() override;
		};
	}
}
