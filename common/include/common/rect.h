#pragma once
#include "vec2.h"

namespace urd
{
	struct rect
	{
		static rect MaxMin(vec2 max, vec2 min);
		static rect Overlaps(rect l, rect r);

		vec2 center;
		vec2 size;

		constexpr vec2 haflSize() const;

		constexpr float top() const;
		constexpr float bottom() const;
		constexpr float right() const;
		constexpr float left() const;

		constexpr vec2 min() const;
		constexpr vec2 max() const;

		constexpr float x() const;
		constexpr float y() const;
		constexpr float width() const;
		constexpr float height() const;
	};
} // namespace urd