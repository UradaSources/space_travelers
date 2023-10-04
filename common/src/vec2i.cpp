#include "common/vec2i.h"
#include "common/vec2.h"

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>

namespace urd
{
	const vec2i vec2i::up{0, 1};
	const vec2i vec2i::down{0, -1};
	const vec2i vec2i::left{-1, 0};
	const vec2i vec2i::right{1, 0};
	const vec2i vec2i::zero{0, 0};
	const vec2i vec2i::one{1, 1};

	vec2i vec2i::Min(vec2i lhs, vec2i rhs)
	{
		return vec2i{std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y)};
	}
	vec2i vec2i::Max(vec2i lhs, vec2i rhs)
	{
		return vec2i{std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y)};
	}

	vec2i& vec2i::operator+=(vec2i r)
	{
		this->set(this->x + r.x, this->y + r.y);
		return *this;
	}
	vec2i& vec2i::operator-=(vec2i r)
	{
		this->set(this->x - r.x, this->y - r.y);
		return *this;
	}
	vec2i& vec2i::operator*=(int r)
	{
		this->set(this->x * r, this->y * r);
		return *this;
	}
	vec2i& vec2i::operator/=(int r)
	{
		this->set(this->x / r, this->y / r);
		return *this;
	}
	vec2i& vec2i::operator*=(vec2i r)
	{
		this->set(this->x * r.x, this->y * r.y);
		return *this;
	}
	vec2i& vec2i::operator/=(vec2i r)
	{
		this->set(this->x / r.x, this->y / r.y);
		return *this;
	}

	vec2i::operator vec2() const { return vec2{(float)(this->x), (float)(this->y)}; }

	std::ostream& operator<<(std::ostream& os, const vec2i& v)
	{
		return os << "{" << v.x << ", " << v.y << "}";
	}

	void vec2i::set(std::int32_t x, std::int32_t y)
	{
		this->x = x;
		this->y = y;
	}
	float vec2i::magnitude() const { return std::sqrt((float)(x * x + y * y)); }
} // namespace urd
