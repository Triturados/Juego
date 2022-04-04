#pragma once
#include <math.h>

namespace LoveEngine {

	namespace Utilities
	{
		template<typename T = float>
		class  Vector2 {
		public:

			T x;
			T y;

			Vector2();

			Vector2(T prim, T sec);

			Vector2<T> operator+(Vector2<T> const& v2) const;
			Vector2<T> operator-(Vector2<T> const& v2) const;

			bool operator==(Vector2<T> const& v2) const ;

			bool operator!=(Vector2<T> const& v2) const;


			void inverse();

			void add(T sumX, T sumY);

			T magnitude() ;

			T magnitudeSqr();

			void normalize() ;

			T scalarProduct(Vector2<T> b);

			T getDistance(Vector2<T> b);
		};

		template <class T>
		std::ostream& operator<<(std::ostream& os, const Vector2<T>& v);
	}
}