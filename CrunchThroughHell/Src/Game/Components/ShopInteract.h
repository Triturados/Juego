#pragma once
#pragma once

#include <Components/Interactable.h>

class string;
namespace LoveEngine {
	namespace Input {
		class InputManager;
	}

	namespace ECS {
		class Interactable;
		class StringFormatter;
		class Shop;
		class ShopInteract : public Interactable {

		private:
			Shop* shop;
			void notOnRangeCallBack();
			void use() override;


		public:

			void receiveComponent(int, Component*) override;
		};
	}
}
