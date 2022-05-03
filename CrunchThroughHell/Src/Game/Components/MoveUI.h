#pragma once
#include <Component.h>
#include <Vector3.h>

namespace LoveEngine {
	namespace ECS {
		class UIElement;
		class MoveUI : public Component {
		private:
			Utilities::Vector3<int> origin;
			Utilities::Vector3<int> destination;
			UIElement* element;
			float t;
			float duration;
			bool shouldcenterX;
			int centerx;
		public:
			MoveUI();
			void init() override;
			void setDuration(float newduration);
			void update() override;
			void receiveMessage(Utilities::StringFormatter& sf);
			Utilities::Vector3<int> getDestination();
			void changeDestination(Utilities::Vector3<int> dest);
		};

	}
}