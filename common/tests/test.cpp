#include <catch2/catch_test_macros.hpp>
#include "common/vec2.h"

using namespace urd;

TEST_CASE("vec2 test", "[vec2]") {
	SECTION("operator overload test") {
		REQUIRE((vec2{ 1,2 } == vec2{ 1,2 }));
		REQUIRE((vec2{ 1,2 } + vec2{ 1,2 } == vec2{ 2,4 }));
		REQUIRE((vec2{ 1,2 } - vec2{ 1,2 } == vec2::zero));
		REQUIRE((vec2{ 1,2 } *2 == vec2{ 2,4 }));
		REQUIRE((vec2{ 1,2 } / 2 == vec2{ 0.5f, 1.0f }));
	}
}