#pragma once

#include <Component.h>
#include <string>

namespace LoveEngine {
	
	namespace ECS {

		enum soundType { effects, environment, voices, music };

		class  Sound : public Component
		{
		
		public:

			void init() override;
			void receiveValues(int gChannel, float f, Component* playerPos = nullptr, GameObject* g = nullptr) override;
			void receiveMessage(std::string s) override;
			void playSound();
			void releaseSound();
			void setSpeed(float s);
		};
	}
}
