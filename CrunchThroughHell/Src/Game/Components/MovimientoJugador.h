#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Transform;
		class RigidBody;
		class ParticleSystem;
		class MovimientoJugador : public Component {
			
		private:
			float MAX_SPEED = 15;

			bool hasRigidBody;
			Transform* tr;
			ParticleSystem* dashParticles;
			RigidBody* rb;
			Input::InputManager* input;
			float speed = MAX_SPEED;
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
			void moveTransform(float mv, Utilities::Vector3<float> rt, float dT);
			void moveRigidbody(float mv, Utilities::Vector3<float> rt);
			void receiveMessage(Utilities::StringFormatter& message) override;

			inline float getSpeed() { return speed; };
			inline float getMaxSpeed() { return MAX_SPEED; };
			inline void setSpeed(float speed_) { speed = speed_; };
		};
	}
}
