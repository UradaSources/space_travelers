#include "basic/input.h"
#include "basic/visual.h"
#include "common/vec2.h"
#include "func.h"

#include <cstdio>
#include <entt/entt.hpp>
#include <functional>
#include <iostream>
#include <raylib.h>

using namespace urd;

int main(int argc, char* argv[])
{
	const int ScreenWidth = 600;
	const int ScreenHeight = 400;

	InitWindow(ScreenWidth, ScreenHeight, "main");

	SetTargetFPS(60);

	Font font = LoadFont("../../resources/sarasa-fixed-sc-regular.ttf");

	entt::registry registry;

	urd::init(registry);

	float s = 12;

	while (!WindowShouldClose())
	{
		urd::update(registry, GetFrameTime());

		BeginDrawing();
		{
			ClearBackground(GRAY);

			constexpr int StrBufferSize = 50;
			char _strBuffer[StrBufferSize]{};

			std::snprintf(_strBuffer, StrBufferSize, "fps %.1f", 1.0f / GetFrameTime());
			DrawTextEx(font, _strBuffer, Vector2{0, 0}, 24, 0, RAYWHITE);

			urd::draw(registry);
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
