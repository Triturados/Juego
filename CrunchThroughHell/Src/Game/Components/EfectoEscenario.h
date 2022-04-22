#pragma once
#include <Component.h>


namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Transform;
		class RigidBody;
		enum class FloorEfects {LAVA, LODO};
		class EfectoEscenario : public Component {
		private:
			Transform* tr = nullptr;
			RigidBody* rb = nullptr;
			FloorEfects efect = FloorEfects::LAVA;
		public:
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& message) override;

			void slowMovement(GameObject* jugador);
			void doDamage(GameObject* jugador);

			void recoverMovement(GameObject* jugador);


			void colliding(GameObject* other) override;
			void exitCollision(GameObject* other) override;
			~EfectoEscenario();
		};
	}
}
