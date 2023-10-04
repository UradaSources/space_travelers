#include "common/color.h"

namespace urd
{
	const color color::clear{0, 0, 0, 0};
	const color color::white{255, 255, 255, 255};
	const color color::black{0, 0, 0, 255};
	const color color::red{255, 0, 0, 255};
	const color color::green{0, 255, 0, 255};
	const color color::blue{0, 0, 255, 255};
	const color color::cyan{0, 255, 255, 255};
	const color color::gray{125, 125, 125, 255};
	const color color::magenta{255, 0, 255, 255};
	const color color::yellow{255, 234, 4, 255};

	bool operator==(const color& l, const color& r)
	{
		return l.r == r.r && l.g == r.g && l.b == r.b && l.a == r.a;
	}
} // namespace urd
