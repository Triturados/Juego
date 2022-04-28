#pragma once
#include <Component.h>
#include <Vector3.h>

namespace LoveEngine {
	namespace ECS {
		class Image;
		class Button;

		class MoveUI : public Component {
		private:
			Utilities::Vector3<int> origin;
			Utilities::Vector3<int> destination;
			Image* img;
			Button* button;
			float t;
			float duration;
		public:
			MoveUI();
			void init() override;
			void setDuration(float newduration);
			void update() override;
			void receiveMessage(Utilities::StringFormatter& sf);
			void changeDestination(Utilities::Vector3<int> dest);
		};

	}
}