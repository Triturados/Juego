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
            };
#pragma endregion
		private:
			Transform* target;
            MeleeAttack* attack;
            Leap* leap;
            Idle* idle;
            Chase* chase;

		public:
            ComportamientoBoss();
            void init() override;
            void receiveComponent(int n, Component* b) override;
		};
	}
}
