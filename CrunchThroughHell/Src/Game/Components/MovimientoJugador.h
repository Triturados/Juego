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

			RigidBody* bossRb;
			Transform* bossTr;

			bool hasRigidBody;
			Transform* tr;
			Transform* trJefe = nullptr;

			ParticleSystem* dashParticles;
			RigidBody* rb;
			Input::InputManager* input;
			float speed = MAX_SPEED;

			float movementZ = 0;
			float movementX = 0;

			float dashDelay = 2; //Cada cuanto tiempo puedes dashear
			float lastDash = 2; //Conteo del ultimo dash para aplicar el delay
			float lastKnockback = 2;
			float knockbackDelay = 2;
			float impulsoKnock = 0.5;

			float dashDuration = 0.1; //Cuanto dura el movimiento del dash
			float currentDashDuration = 0; //Conteo de la duracion del dash
			float knockbackDuration = 0.1; //Cuanto dura el movimiento del dash
			float currentKnockbackDuration = 0; //Conteo de la duracion del dash
			float dashSpeed = 220; //Velocidad del dash
			bool isDashing = false;
			bool isKnockback = false;
	

		public:
			void init() override;
			void postInit() override;
			void update() override;
			void stepPhysics() override;
			void dash();
			void knockback();
			void move(float mvX, float mvZ);
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveComponent(int, Component*) override;

			inline float getSpeed() { return speed; };
			inline float getMaxSpeed() { return MAX_SPEED; };
			inline void setSpeed(float speed_) { speed = speed_; };
			void enterCollision(GameObject* other)override;
			void colliding(GameObject* other) override;
		};
	}
}
