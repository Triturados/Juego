#pragma once

#include <Component.h>
#include <string>



namespace LoveEngine {
	namespace ECS {

		class lovexport Animation : public Component
		{

		public:
			void setActive(bool activated = true);
			void setLoop(bool activated = true);

			bool playingAnimation(std::string animationName);
		};
	}
}
