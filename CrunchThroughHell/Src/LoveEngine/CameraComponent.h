#pragma once

#include <Component.h>

namespace LoveEngine {

	namespace Utilities {
		template<typename T>
		class Vector3;
	}

	namespace ECS {

		class Transform;

		class Camera : public Component
		{

		public:
			void lookAt(Utilities::Vector3<float> pos);
			void lookAtDir(float x, float y, float z);
		};
	}
}