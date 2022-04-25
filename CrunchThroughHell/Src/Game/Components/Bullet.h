#pragma once
#include <Component.h>


namespace LoveEngine {

	namespace ECS {
		class Timer;
		class RigidBody;
		class Bullet : public Component {
			
		private:
			Timer* lifetime = nullptr;
			RigidBody* mRb = nullptr;
			Utilities::Vector3<float>* vel;
		public:
			void init() override;
			void update() override;
		};
	}
}
