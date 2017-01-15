#ifndef __FSVECTOR_HPP__
#define __FSVECTOR_HPP__

namespace sf {
	template <class T> struct Vector2 {
	public:
		T x, y;
		Vector2() {
			x = 0;
			y = 0;
		}
		Vector2(const T& _x, const T& _y) {
			x = _x;
			y = _y;
		}

		Vector2 < T >& operator=(const Vector2 < T >& vector);
		Vector2 < T > operator+(const Vector2 < T >& vector);
		Vector2 < T > operator-(const Vector2 < T >& vector);

		inline T dotProduct(const Vector2 < T >& v) { return T(x * v.x + y * v.y); }
	};

	template <class T> struct Vector3 {
	public:
		T x, y, z;
		Vector3() {
			x = 0;
			y = 0;
			z = 0;
		}
		Vector3(const T& _x, const T& _y, const T& _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		void reset() {
			x = y = z = 0;
		}
		Vector3 < T >& operator= (const Vector3 < T >& vector);
		Vector3 < T > operator+(const Vector3 < T >& vector);
		Vector3 < T > operator-(const Vector3 < T >& vector);

		inline T dotProduct(const Vector3 < T >& v) { return T(x * v.x + y * v.y + z * v.z); }
	};


	template <class T> Vector2<T>& Vector2<T>:: operator= (const Vector2<T>& vector) {
		x = vector.x;
		y = vector.y;
		return *this;
	}

	template <class T> Vector2<T>  Vector2<T>:: operator+ (const Vector2<T>& vector) {
		return Vector2<T>(x + vector.x, y + vector.y);
	}

	template <class T> Vector2<T> Vector2<T>:: operator- (const Vector2<T>& vector) {
		return Vector2<T>(x - vector.x, y - vector.y);
	}

	template <class T> Vector3<T>& Vector3<T>:: operator= (const Vector3<T>& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
	}

	template <class T> Vector3<T> Vector3<T>:: operator+ (const Vector3<T>& vector) {
		return Vector3<T>(x + vector.x, y + vector.y, z + vector.z);
	}

	template <class T> Vector3<T> Vector3<T>:: operator- (const Vector3<T>& vector) {
		return Vector3<T>(x - vector.x, y - vector.y, z - vector.z);
	}
}
#endif //__FSVECTOR_HPP__