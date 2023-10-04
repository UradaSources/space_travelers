#pragma once
#include "common/color.h"
#include "common/vec2.h"

#include <string_view>

namespace urd
{
	namespace visual
	{
		void init();

		void line(vec2 p1, vec2 p2, color c = color::white);
		void ray(vec2 p1, vec2 dir, color c = color::white);
		void box(vec2 pos, vec2 size, color c = color::white);
		void mark(vec2 center, color c = color::white, float len = 10);
		void print(vec2 pos, const std::string_view text, int size, color c = color::white);
	} // namespace visual
} // namespace urd
