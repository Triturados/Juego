#pragma once
#include <Agent.h>


namespace LoveEngine {

	namespace ECS {
		class Transform;
		class RigidBody;
		class ComportamientoBoss : public Agent {
		private:
			Transform* target;

		public:
			void init() override;
		};
	}
}
