#pragma once
#include <Component.h>


namespace LoveEngine {

	namespace ECS {

		class Button;
		class Shop : public Component {

		public:

			Shop();
			~Shop();
			void receiveMessage(Utilities::StringFormatter&) override;
			void receiveComponent(int, Component*) override;
			static bool SAVEDATA;

		private:
			const int maxPurchase = 3;
			const char* path = "shop";

			int currency;
			int health, damage, speed;

			int healthIncrement, damageIncrement, speedIncrement;

			void buyHealth();
			void buyDamage();
			void buySpeed();
		};
	}
}
