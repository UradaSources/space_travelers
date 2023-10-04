#pragma once
#include <cmath>

namespace urd
{
	namespace mathf
	{
		constexpr float MPI = 3.14125f;

		constexpr float Deg2Rad = (mathf::MPI * 2.0f) / 360.0f;
		constexpr float Rad2Deg = 360.0f / (mathf::MPI * 2.0f);

		using std::abs;

		using std::ceil;
		using std::floor;
		using std::round;

		using std::fmax;
		using std::fmin;

		using std::acos;
		using std::asin;
		using std::atan;
		using std::cos;
		using std::sin;
		using std::tan;

		using std::pow;
		using std::sqrt;

		constexpr float clamp(float v, float min, float max)
		{
			return v < min ? min : v > max ? max : v;
		}
		constexpr float clamp01(float v) { return clamp(v, 0, 1); }

		constexpr float lerpUnclamp(float a, float b, float t) { return (b - a) * t + a; }
		constexpr float lerp(float a, float b, float t) { return clamp01(lerpUnclamp(a, b, t)); }

		constexpr float sign(float v) { return v > 0 ? 1 : v == 0 ? 0.f : -1.f; }

		float moveTowards(float from, float target, float maxDelta);

		float random(float min, float max);
		float random(float max);
		float random01();

		int random(int min, int max);
		int random(int max);

		void seed();
		void seed(int seed);
		void seed(float seed);
	} // namespace mathf
} // namespace urd