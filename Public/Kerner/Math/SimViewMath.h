/**************************************************
outher: LJ
time: 2016-03-25
use: 数学头文件
from: osg
chanage:
change outher :
**************************************************/

#ifndef _PUBLIC_SIMVIEWMATH_H_
#define _PUBLIC_SIMVIEWMATH_H_

namespace SimView
{

#ifdef PI
#undef PI
#undef PI_2
#undef PI_4
#endif
	const double PI = 3.14159265358979323846;
	const double PI_2 = 1.57079632679489661923;
	const double PI_4 = 0.78539816339744830962;
	const double LN_2 = 0.69314718055994530942;
	const double INVLN_2 = 1.0 / LN_2;


	template<typename T>
	inline T absolute(T v) { return v < (T)0 ? -v : v; }

	/** return true if float lhs and rhs are equivalent,
	* meaning that the difference between them is less than an epsilon value
	* which defaults to 1e-6.
	*/
	inline bool equivalent(float lhs, float rhs, float epsilon = 1e-6)
	{
		float delta = rhs - lhs; return delta < 0.0f ? delta >= -epsilon : delta <= epsilon;
	}

	/** return true if double lhs and rhs are equivalent,
	* meaning that the difference between them is less than an epsilon value
	* which defaults to 1e-6.
	*/
	inline bool equivalent(double lhs, double rhs, double epsilon = 1e-6)
	{
		double delta = rhs - lhs; return delta < 0.0 ? delta >= -epsilon : delta <= epsilon;
	}

	/** return the minimum of two values, equivalent to std::min.
	* std::min not used because of STL implementation under IRIX not containing
	* std::min.
	*/
	template<typename T>
	inline T minimum(T lhs, T rhs) { return lhs < rhs ? lhs : rhs; }

	/** return the maximum of two values, equivalent to std::max.
	* std::max not used because of STL implementation under IRIX not containing
	* std::max.
	*/
	template<typename T>
	inline T maximum(T lhs, T rhs) { return lhs > rhs ? lhs : rhs; }

	template<typename T>
	inline T clampTo(T v, T minimum, T maximum) { return v<minimum ? minimum : v>maximum ? maximum : v; }

	template<typename T>
	inline T clampAbove(T v, T minimum) { return v < minimum ? minimum : v; }

	template<typename T>
	inline T clampBelow(T v, T maximum) { return v > maximum ? maximum : v; }

	template<typename T>
	inline T clampBetween(T v, T minimum, T maximum)
	{
		return clampBelow(clampAbove(v, minimum), maximum);
	}

	template<typename T>
	inline T sign(T v) { return v < (T)0 ? (T)-1 : (T)1; }

	template<typename T>
	inline T signOrZero(T v) { return v<(T)0 ? (T)-1 : (v>(T)0 ? (T)1 : 0); }

	template<typename T>
	inline T square(T v) { return v*v; }

	template<typename T>
	inline T signedSquare(T v) { return v < (T)0 ? -v*v : v*v;; }

	inline float inDegrees(float angle) { return angle*(float)PI / 180.0f; }
	inline double inDegrees(double angle) { return angle*PI / 180.0; }

	template<typename T>
	inline T inRadians(T angle) { return angle; }

	inline float DegreesToRadians(float angle) { return angle*(float)PI / 180.0f; }
	inline double DegreesToRadians(double angle) { return angle*PI / 180.0; }

	inline float RadiansToDegrees(float angle) { return angle*180.0f / (float)PI; }
	inline double RadiansToDegrees(double angle) { return angle*180.0 / PI; }

	inline float round(float v) { return v >= 0.0f ? floorf(v + 0.5f) : ceilf(v - 0.5f); }
	inline double round(double v) { return v >= 0.0 ? floor(v + 0.5) : ceil(v - 0.5); }

#if defined(_MSC_VER)
	inline bool isNaN(double v) { return _isnan(v) != 0; }
#elif defined(__ANDROID__)
	inline bool isNaN(float v) { return isnan(v); }
	inline bool isNaN(double v) { return isnan(v); }
#else
	inline bool isNaN(float v) { return std::isnan(v); }
	inline bool isNaN(double v) { return std::isnan(v); }
#endif


	/** compute the volume of a tetrahedron. */
	template<typename T>
	inline float computeVolume(const T& a, const T& b, const T& c, const T& d)
	{
		return fabsf(((b - c) ^ (a - b))*(d - b));
	}

	/** compute the volume of a prism. */
	template<typename T>
	inline float computeVolume(const T& f1, const T& f2, const T& f3,
		const T& b1, const T& b2, const T& b3)
	{
		return computeVolume(f1, f2, f3, b1) +
			computeVolume(b1, b2, b3, f2) +
			computeVolume(b1, b3, f2, f3);
	}

	/** Convert a ascii number to a double, ignoring locale settings.*/
	extern KERNER_EXPORT double asciiToDouble(const char* str);

	/** Convert a ascii number to a float, ignoring locale settings.*/
	inline float asciiToFloat(const char* str) { return static_cast<float>(asciiToDouble(str)); }

	/** Detect first ascii POSITIVE number in string and convert to double.*/
	extern KERNER_EXPORT double findAsciiToDouble(const char* str);

	/** Detect first ascii POSITIVE number in string and convert to double.*/
	inline float findAsciiToFloat(const char* str) { return static_cast<float>(findAsciiToDouble(str)); }
	//}
}

#endif // !_PUBLIC_SIMVIEWMATH_H_
