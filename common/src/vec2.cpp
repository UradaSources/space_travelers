#include "common/vec2.h"
#include "common/vec2i.h"

#include <algorithm>
#include <cmath>

constexpr float Epsilon = 0.00001f;
constexpr float EpsilonNormalSqrt = 1e-15f;
constexpr float Rad2Deg = 360.0f / (3.1415926f * 2.0f);

namespace urd
{
	const vec2 vec2::up{0, 1};
	const vec2 vec2::down{0, -1};
	const vec2 vec2::left{-1, 0};
	const vec2 vec2::right{1, 0};
	const vec2 vec2::zero{0, 0};
	const vec2 vec2::one{1, 1};

	float vec2::Angle(vec2 from, vec2 to)
	{
		float denominator = std::sqrt(from.sqrMagnitude() * to.sqrMagnitude());
		if (denominator < EpsilonNormalSqrt)
			return 0;

		float dot = std::min(std::max(Dot(from, to) / denominator, -1.0f), 1.0f);
		return std::acos(dot) * Rad2Deg;
	}

	float vec2::SignedAngle(vec2 from, vec2 to)
	{
		float unsignedAngle = Angle(from, to);
		float sign = (float)(from.x * to.y - from.y * to.x) > 0 ? 1 : -1;
		return unsignedAngle * sign;
	}

	float vec2::Distance(vec2 a, vec2 b)
	{
		float diff_x = a.x - b.x;
		float diff_y = a.y - b.y;
		return std::sqrt(diff_x * diff_x + diff_y * diff_y);
	}

	vec2 vec2::Rotate(vec2 v, float angle, vec2 pivot)
	{
		float radians = angle * 3.1415926f / 180.0f;
		float c = std::cos(radians);
		float s = std::sin(radians);

		float x = c * (v.x - pivot.x) - s * (v.y - pivot.y) + pivot.x;
		float y = s * (v.x - pivot.x) + c * (v.y - pivot.y) + pivot.y;

		return vec2{x, y};
	}

	vec2 vec2::Min(vec2 lhs, vec2 rhs)
	{
		return vec2{std::fmin(lhs.x, rhs.x), std::fmin(lhs.y, rhs.y)};
	}
	vec2 vec2::Max(vec2 lhs, vec2 rhs)
	{
		return vec2{std::fmax(lhs.x, rhs.x), std::fmax(lhs.y, rhs.y)};
	}

	vec2 vec2::MoveTowards(vec2 current, vec2 target, float maxDistanceDelta)
	{
		float toX = target.x - current.x;
		float toY = target.y - current.y;

		float sqDist = toX * toX + toY * toY;

		if (sqDist == 0 || (maxDistanceDelta >= 0 && sqDist <= maxDistanceDelta * maxDistanceDelta))
			return target;

		float dist = std::sqrt(sqDist);
		return vec2{
			current.x + toX / dist * maxDistanceDelta, current.y + toY / dist * maxDistanceDelta};
	}
	vec2 vec2::Lerp(vec2 a, vec2 b, float t) { return (b - a) * t + a; }

	vec2& vec2::operator+=(vec2 r)
	{
		this->set(this->x + r.x, this->y + r.y);
		return *this;
	}
	vec2& vec2::operator-=(vec2 r)
	{
		this->set(this->x - r.x, this->y - r.y);
		return *this;
	}
	vec2& vec2::operator*=(float r)
	{
		this->set(this->x * r, this->y * r);
		return *this;
	}
	vec2& vec2::operator/=(float r)
	{
		this->set(this->x / r, this->y / r);
		return *this;
	}
	vec2& vec2::operator*=(vec2 r)
	{
		this->set(this->x * r.x, this->y * r.y);
		return *this;
	}
	vec2& vec2::operator/=(vec2 r)
	{
		this->set(this->x / r.x, this->y / r.y);
		return *this;
	}

	vec2::operator vec2i() const { return vec2i{(int)(this->x), (int)(this->y)}; }

	std::ostream& operator<<(std::ostream& os, const vec2& v)
	{
		return os << "{" << v.x << ", " << v.y << "}";
	}

	void vec2::set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void vec2::normalize()
	{
		float len = magnitude();
		if (len != 0.0f)
			*this /= len;
	}

	float vec2::magnitude() const { return std::sqrt(x * x + y * y); }

	vec2 vec2::normalized() const
	{
		float len = magnitude();
		if (len != 0.0f)
			return *this / len;
		else
			return *this;
	}
} // namespace urd
