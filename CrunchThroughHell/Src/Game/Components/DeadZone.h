#pragma once
#include <Component.h>


namespace LoveEngine {

	namespace ECS {
		class Transform;
		class RigidBody;
		class DeadZone : public Component {
			
		private:
			

		public:
			void enterCollision(GameObject* other) override;
		};
	}
}
