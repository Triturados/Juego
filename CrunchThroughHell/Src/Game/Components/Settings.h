#pragma once
#include <Component.h>
#include <vector>
namespace LoveEngine {
	namespace ECS {

		class Button;
		class Settings : public Component {
		public:
			Settings();

			void init() override;
			void receiveMessage(Utilities::StringFormatter&) override;
			void receiveComponent(int, Component*) override;
		private:
			
			std::vector<Utilities::Vector3<int>> resolutions;
			Button* buttons[5];

			void alternateFullScreen();
			void changeResolution(Utilities::Vector3<int> res);
			void changeResolution0();
			void changeResolution1();
			void changeResolution2();
			void changeResolution3();
			void backtomenu();
		};
	}
}
