#pragma once
#include <Component.h>

class string;
namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Transform;
		class ParticleSystem;
		class Animation;
		class MovimientoJugador;
		class AtaqueJugador : public Component {

		private:

			Input::InputManager* input;
			float dmg = 15;
			float attackDistance =45;
			float attackAngle = 45;
			int comboIndex = 0;

			float speedReductionFactor = 0.25;
			float originalSpeed;

			MovimientoJugador* movement;
			ParticleSystem* particleSys;
			Animation* anim;

			std::string attackAnimations[3] = {"attack1","attack2","attack3"};
			int numAnimations = 3;
			
			bool hit = false;
			bool isAttacking = false;

			Transform* bossTr;
			Transform* tr;

			float attackDuration = 1;
			float currentDuration = 1;

		public:
			void init() override;
			void postInit() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveComponent(int, Component*) override;

			void startAttack();
			void attack();
			bool bossOnRange();

			bool currentlyAttacking();
		};
	}
}
