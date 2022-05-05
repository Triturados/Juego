#pragma once
#include <Component.h>


namespace LoveEngine {

	namespace ECS {

		class Button;
		class Shop : public Component {

		public:

			Shop();
			~Shop();
			void receiveComponent(int, Component*) override;
			static bool SAVEDATA;

		private:
			const int maxPurchase = 3;
			const char* path = "shop";

			int currency;
			int health, damage, speed;

			void buyHealth();
			void buyDamage();
			void buySpeed();
		};
	}
}
