#pragma once
#include <Agent.h>


namespace LoveEngine {

	namespace ECS {
		class Transform;
		class RigidBody;
		class Animation;
		class ComportamientoBoss : public Agent {
		protected:
			Transform* target;
			Transform* tr;
			Animation* anim;
			virtual void setTargets() = 0;

		public:
            ComportamientoBoss();
            void init() override;
            void postInit()override;
            void receiveComponent(int n, Component* b) override;
		};
	}
}
