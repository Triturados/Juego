#pragma once

#include <Component.h>


namespace LoveEngine {

	namespace Utilities {
		template<typename T>
		class Vector3;
		template<typename T>
		class Vector4;
	}
	
	namespace ECS {

		enum lightType { point, directional, spot };


		class Transform;
		class Light : public Component
		{
		
		public:

			void specularColor(float r, float g, float b);
			void diffuseColor(float r, float g, float b);
			void setDir(Utilities::Vector3<float> direction);
			void setRange(float startAngle, float endAngle, float desvanecimiento = 1.0);
			void setVisibility(bool active);
			void setPower(float power);

			Utilities::Vector3<float> getDiffuseColor();
			Utilities::Vector3<float> getSpecularColor();
			bool getVisibility();

		};

	}
}