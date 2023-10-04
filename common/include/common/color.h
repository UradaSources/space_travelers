#pragma once
#include <cstdint>

namespace urd
{
	struct color
	{
		static const color clear;
		static const color white;
		static const color black;
		static const color red;
		static const color green;
		static const color blue;
		static const color cyan;
		static const color gray;
		static const color magenta;
		static const color yellow;

		std::uint8_t r, g, b, a;

		void set(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};

	bool operator==(const color& l, const color& r);
} // namespace urd