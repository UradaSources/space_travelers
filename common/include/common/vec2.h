#pragma once
#include <cstdint>
#include <ostream>

namespace urd
{
	struct vec2i;

	struct vec2
	{
		static const vec2 up;
		static const vec2 down;
		static const vec2 left;
		static const vec2 right;
		static const vec2 zero;
		static const vec2 one;

		static constexpr float Dot(vec2 l, vec2 r) { return l.x * r.x + l.y * r.y; }

		static float Angle(vec2 from, vec2 to);

		static float SignedAngle(vec2 from, vec2 to);

		static float Distance(vec2 a, vec2 b);

		static vec2 Rotate(vec2 v, float angle, vec2 pivot = vec2::zero);

		static vec2 Min(vec2 lhs, vec2 rhs);
		static vec2 Max(vec2 lhs, vec2 rhs);

		static vec2 Lerp(vec2 a, vec2 b, float t);

		static vec2 MoveTowards(vec2 current, vec2 target, float maxDistanceDelta);

		float x, y;

		vec2& operator+=(vec2 r);
		vec2& operator-=(vec2 r);
		vec2& operator*=(float r);
		vec2& operator/=(float r);
		vec2& operator*=(vec2 r);
		vec2& operator/=(vec2 r);

		explicit operator vec2i() const;

		constexpr vec2 operator+(vec2 r) const { return vec2{x + r.x, y + r.y}; }
		constexpr vec2 operator-(vec2 r) const { return vec2{x - r.x, y - r.y}; }
		constexpr vec2 operator*(float r) const { return vec2{x * r, y * r}; }
		constexpr vec2 operator/(float r) const { return vec2{x / r, y / r}; }
		constexpr vec2 operator*(vec2 r) const { return vec2{x * r.x, y * r.y}; }
		constexpr vec2 operator/(vec2 r) const { return vec2{x / r.x, y / r.y}; }

		constexpr float sqrMagnitude() const { return x * x + y * y; }

		void set(float x, float y);
		void normalize();
		vec2 normalized() const;
		float magnitude() const;
	};

	constexpr vec2 operator*(float l, vec2 r) { return vec2{l * r.x, l * r.y}; }
	constexpr vec2 operator/(float l, vec2 r) { return vec2{l / r.x, l / r.y}; }

	constexpr bool operator==(vec2 l, vec2 r) { return l.x == r.x && l.y == r.y; }
	constexpr bool operator!=(vec2 l, vec2 r) { return l.x != r.x || l.y != r.y; }

	std::ostream& operator<<(std::ostream& os, vec2 v);
} // namespace urd
