#include "basic/visual.h"

#include <raylib.h>
#include "common/vec2.h"

namespace urd
{
	namespace visual
	{
		Color _toRaylibColor(color c) { return Color{c.r, c.g, c.b, c.a}; }
		Vector2 _toRaylibVec(vec2 vec) { return Vector2{vec.x, vec.y}; }

		Font _defaultFont;

		void init() { _defaultFont = LoadFont("../../resources/sarasa-fixed-sc-regular.ttf"); }

		vec2 offset{300, -200};
		vec2 scale{2.0f, 2.0f};

		void line(vec2 p1, vec2 p2, color c)
		{
			p1 *= scale;
			p2 *= scale;

			p1 += offset;
			p2 += offset;

			p2.y *= -1;
			p1.y *= -1;

			DrawLine(p1.x, p1.y, p2.x, p2.y, _toRaylibColor(c));
		}
		void ray(vec2 p1, vec2 dir, color c) { line(p1, p1 + dir, c); }
		void box(vec2 pos, vec2 size, color c)
		{
			float w = size.x * 0.5f;
			float h = size.y * 0.5f;

			vec2 p1 = pos + vec2{-w, h};
			vec2 p2 = pos + vec2{w, h};
			vec2 p3 = pos + vec2{w, -h};
			vec2 p4 = pos + vec2{-w, -h};

			line(p1, p2, c);
			line(p2, p3, c);
			line(p3, p4, c);
			line(p4, p1, c);
		}
		void mark(vec2 center, color c, float len)
		{
			vec2 xOffset = len * 0.5f * vec2::right;
			vec2 yOffset = len * 0.5f * vec2::up;

			line(center - xOffset, center + xOffset, c);
			line(center - yOffset, center + yOffset, c);
		}
		void print(vec2 pos, const std::string_view text, int size, color c)
		{
			DrawTextEx(_defaultFont, text.data(), _toRaylibVec(pos), size, 0, _toRaylibColor(c));
		}
	} // namespace visual
} // namespace urd