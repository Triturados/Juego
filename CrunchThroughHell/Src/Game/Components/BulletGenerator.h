#pragma once
#include <Component.h>
#include <vector>


namespace LoveEngine {
	namespace Utilities {
		template<typename T>
		class Vector3;
	}

	namespace ECS {
		class Transform;
		class Timer;

		class BulletGenerator : public Component {

		private:
			Timer* timer;
			Transform* tr;
			int interval;
			Utilities::Vector3<float>* area;

			void createBullet();
		public:
			BulletGenerator();
			void init() override;
			void update() override;
			void receiveMessage(Utilities::StringFormatter& message) override;
		};
	}
}
