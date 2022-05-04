#pragma once
#include <Component.h>
#include <vector>
namespace LoveEngine {
	namespace ECS {

		class Button;
		class Settings : public Component {
		public:
			Settings();

			void postInit() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter&) override;
			void receiveComponent(int, Component*) override;
		private:
			Button *up, *down;
			std::vector<Button*> buttons;

		};
	}
}
