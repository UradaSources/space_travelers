#include "common/rect.h"

namespace urd
{
	rect rect::MaxMin(vec2 max, vec2 min)
	{
		vec2 center = vec2::Lerp(min, max, 0.5f);
		return rect{center, max - min};
	}
	rect rect::Overlaps(rect l, rect r)
	{
		vec2 overlapsMin = vec2::Max(l.min(), r.min());
		vec2 overlapsMax = vec2::Min(l.max(), r.max());
		return rect::MaxMin(overlapsMax, overlapsMin);
	}

	constexpr vec2 rect::haflSize() const { return size * 0.5f; }

	constexpr float rect::top() const { return center.y + size.y * 0.5f; }
	constexpr float rect::bottom() const { return center.y - size.y * 0.5f; }
	constexpr float rect::right() const { return center.x + size.x * 0.5f; }
	constexpr float rect::left() const { return center.x - size.x * 0.5f; }

	constexpr vec2 rect::min() const { return center - size * 0.5f; }
	constexpr vec2 rect::max() const { return center + size * 0.5f; }

	constexpr float rect::x() const { return center.x; }
	constexpr float rect::y() const { return center.y; }
	constexpr float rect::width() const { return size.x; }
	constexpr float rect::height() const { return size.y; }
} // namespace urd
