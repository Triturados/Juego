#pragma once
#include <Agent.h>


namespace LoveEngine {

	namespace ECS {
		class Transform;
		class RigidBody;
		class ComportamientoBoss : public Agent {
		protected:
#pragma region Actions
			class MeleeAttack : public Action
			{
			public:
				MeleeAttack(Agent* agent_);
				void setTarget(Transform* t);
				bool conditionsFulfilled() const final;
				void onActionStart() final;
				void activeUpdate() final;
			protected:
				RigidBody* rb;
				Transform* target = nullptr;
				Transform* tr = nullptr;
			};
            class Idle : public Action
            {
            public:
                Idle(Agent* agent_);
                void activeUpdate() final;
            };

            class Chase : public Action
            {
            public:
                Chase(Agent* agent_);
                void setTarget(Transform* t);
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
                bool conditionsFulfilled() const final;
                void onActionStart() final;
                void activeUpdate() final;
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
            };
#pragma endregion
		private:
			Transform* target;

		public:
			void init() override;
		};
	}
}
