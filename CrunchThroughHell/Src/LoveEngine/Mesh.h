#pragma once

#include <Component.h>

namespace LoveEngine {

	namespace ECS {

		class Transform;

		class Mesh : public Component
		{
		public:
			void setVisibility(bool mode = true);
		};
	}
}