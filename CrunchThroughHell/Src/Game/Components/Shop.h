#pragma once
#include <Component.h>


namespace LoveEngine {

	namespace ECS {

		class Text;
		class Button;
		class Shop : public Component {

		public:

			Shop();
			~Shop();
			void receiveMessage(Utilities::StringFormatter&) override;
			void receiveComponent(int, Component*) override;
			static bool SAVEDATA;

			void postInit() override;

		private:
			const int maxPurchase = 3;
			const char* path = "shop";

			int currency;
			int health, damage, speed;

			int healthIncrement, damageIncrement, speedIncrement;

			Text* text;

			void buyHealth();
			void buyDamage();
			void buySpeed();
		};
	}
}
