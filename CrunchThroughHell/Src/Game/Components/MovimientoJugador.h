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

			float dashDelay = 2; //Cada cuanto tiempo puedes dashear
			float lastDash = 2;

			float dashDuration = 0.1; //Cuanto dura el movimiento del dash
			float currentDashDuration = 0;
			float dashSpeed = 220; //Velocidad del dash
			bool isDashing = false;

		public:
			void init() override;
			void update() override;
			void dash(float dT);
			void moveTransform(float mv, Utilities::Vector4<float> rt, float dT);
			void moveRigidbody(float mv, Utilities::Vector4<float> rt);
			void receiveMessage(Utilities::StringFormatter& message) override;
		};
	}
}
