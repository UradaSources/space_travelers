#include "common/mathf.h"

#include <cassert>
#include <limits>
#include <random>

namespace urd
{
	namespace mathf
	{
		std::random_device _randomDevice;
		std::mt19937 _randomGen(_randomDevice());

		float moveTowards(float from, float target, float maxDelta)
		{
			if (std::abs(target - from) > maxDelta)
			{
				return target > from ? from + maxDelta : from - maxDelta;
			}
			return target;
		}

		float random(float min, float max)
		{
			assert(max > min);
			std::uniform_real_distribution<float> dist(min, max);
			return dist(_randomGen);
		}
		float random(float max) { return random(0.0f, max); }
		float random01() { return random(0.0f, 1.0f); }

		int random(int min, int max)
		{
			assert(max > min);
			std::uniform_int_distribution<int> dist(min, max);
			return dist(_randomGen);
		}
		int random(int max) { return random(0, max); }

		void seed() { _randomGen.seed(_randomDevice()); }
		void seed(int seed) { _randomGen.seed(seed); }
	} // namespace mathf
} // namespace urd
