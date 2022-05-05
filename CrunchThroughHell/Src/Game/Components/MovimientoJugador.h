#pragma once
#include <Component.h>

namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Transform;
		class RigidBody;
		class Animation;
		class ParticleSystem;
		class Stamina;
		class Sound;

		class AtaqueJugador;
		class Salud;
		class MovimientoJugador : public Component {
		public:
			static float MAX_SPEED;
			static float initial_MAX_SPEED;
		private:

			RigidBody* bossRb;
			Transform* bossTr;
			
			Transform* camTr;

			bool hasRigidBody;
			Transform* tr;
			Transform* trJefe = nullptr;

			AtaqueJugador* ataque;
			Salud* salud;
			Animation* anim;
			ParticleSystem* dashParticles;
			RigidBody* rb;
			Input::InputManager* input;
			float speed;

			float movementZ = 0;
			float movementX = 0;

			float dashDelay = 1; //Cada cuanto tiempo puedes dashear
			float lastDash = 1; //Conteo del ultimo dash para aplicar el delay
			float lastKnockback = 2;
			float knockbackDelay = 2;
			float impulsoKnock = 0.5;

			float dashDuration = 0.1; //Cuanto dura el movimiento del dash
			float currentDashDuration = 0; //Conteo de la duracion del dash
			float knockbackDuration = 0.1; //Cuanto dura el movimiento del knockback
			float currentKnockbackDuration = 0; //Conteo de la duracion del knockback
			float dashSpeed = 220; //Velocidad del dash
			bool isDashing = false;
			bool isKnockback = false;
	
			int dashStamina = 0;
			Stamina* sta;
			Sound* dashSound;

			bool overWorld = false;
		public:
			void init() override;
			void postInit() override;
			void update() override;
			void stepPhysics() override;
			void dash();
			void knockback();
			void changeAnimations();
			void freeMovement(float mvX, float mvZ);
			void aimedMovement(float mvX, float mvZ);
			void disablePlayer();
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
