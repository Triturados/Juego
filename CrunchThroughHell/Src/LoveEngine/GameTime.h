#pragma once

namespace LoveEngine {

	class Time {
	public:
		Time();

		static Time* getInstance();

		float deltaTime;
		float unscaledTime;
		float physicsTime;
		float timeSinceStart;
		float timeScale;
		unsigned long frameCount;
		float calculateFrameRate();
	};

}