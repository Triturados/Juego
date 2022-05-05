#pragma once
#include <Component.h>
#include <vector>
namespace LoveEngine {
	namespace ECS {

		class Button;
		class Sound;
		class Settings : public Component {
		public:
			Settings();

			void init() override;
			void receiveMessage(Utilities::StringFormatter&) override;
			void receiveComponent(int, Component*) override;
		private:

			std::vector<Utilities::Vector3<int>> resolutions;
			Button* buttons[5];
			Sound* sButton1;
			Sound* sButton2;
			Sound* sButton3;

			void alternateFullScreen();
			void changeResolution(Utilities::Vector3<int> res);
			void changeResolution0();
			void lowVolume();
			void mediumVolume();
			void highVolume();
			void backtomenu();
		};
	}
}