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
		class Stamina;
		class MovimientoJugador;
		class Sound;
		class Salud;
		class AtaqueJugador : public Component {

		private:

			Input::InputManager* input;
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

			Transform* bossTr = nullptr;
			Transform* tr;

			float attackDuration = 1;
			float currentDuration = 1;

			float attackStamina = 0;
			Stamina* sta;
			Sound* attackSound;
			Salud* bossHealth;

		public:
			static int dmg;
			static int initial_dmg;

			void init() override;
			void postInit() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& message) override;
			void receiveComponent(int, Component*) override;

			void startAttack();
			void attack();
			bool bossOnRange();
			inline void setDmg(int dmg_) { dmg = dmg_; };
			inline int getDmg() { return dmg; };

			bool currentlyAttacking();
		};
	}
}
