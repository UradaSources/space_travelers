#pragma once
#include <cstdint>
#include <ostream>

namespace urd
{
	struct vec2;

	struct vec2i
	{
		static const vec2i up;
		static const vec2i down;
		static const vec2i left;
		static const vec2i right;
		static const vec2i zero;
		static const vec2i one;

		static vec2i Min(vec2i lhs, vec2i rhs);
		static vec2i Max(vec2i lhs, vec2i rhs);

		std::int32_t x, y;

		vec2i& operator+=(vec2i r);
		vec2i& operator-=(vec2i r);
		vec2i& operator*=(std::int32_t r);
		vec2i& operator/=(std::int32_t r);
		vec2i& operator*=(vec2i r);
		vec2i& operator/=(vec2i r);

		operator vec2() const;

		constexpr vec2i operator+(vec2i r) const { return vec2i{x + r.x, y + r.y}; }
		constexpr vec2i operator-(vec2i r) const { return vec2i{x - r.x, y - r.y}; }
		constexpr vec2i operator*(std::int32_t r) const { return vec2i{x * r, y * r}; }
		constexpr vec2i operator/(std::int32_t r) const { return vec2i{x / r, y / r}; }
		constexpr vec2i operator*(vec2i r) const { return vec2i{x * r.x, y * r.y}; }
		constexpr vec2i operator/(vec2i r) const { return vec2i{x / r.x, y / r.y}; }

		constexpr float sqrMagnitude() const { return (float)(x * x + y * y); }

		void set(std::int32_t x, std::int32_t y);
		float magnitude() const;
	};

	constexpr vec2i operator*(std::int32_t l, vec2i r) { return vec2i{l * r.x, l * r.y}; }
	constexpr vec2i operator/(std::int32_t l, vec2i r) { return vec2i{l / r.x, l / r.y}; }

	constexpr bool operator==(vec2i l, vec2i r) { return l.x == r.x && l.y == r.y; }
	constexpr bool operator!=(vec2i l, vec2i r) { return l.x != r.x || l.y != r.y; }

	std::ostream& operator<<(std::ostream& os, vec2i v);
} // namespace urd
