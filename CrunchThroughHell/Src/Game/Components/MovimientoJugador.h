#pragma once
#include <Component.h>


namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Transform;
		class RigidBody;
		class MovimientoJugador : public Component {
			
		private:
			bool hasRigidBody;
			Transform* tr;
			RigidBody* rb;
			Input::InputManager* input;
			float speed = 15;
			float rotSpeed = 5;

		public:
			void init() override;
			void update() override;
			void moveTransform(float mv, Utilities::Vector4<float> rt, float dT);
			void moveRigidbody(float mv, Utilities::Vector4<float> rt);
			void receiveMessage(Utilities::StringFormatter& message) override;
		};
	}
}
