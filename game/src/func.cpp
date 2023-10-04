#include "func.h"

#include "Pathfind.h"
#include "WorldGrid.h"
#include "basic/input.h"
#include "basic/visual.h"
#include "common/color.h"
#include "common/mathf.h"
#include "common/vec2.h"
#include "common/vec2i.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <entt/entt.hpp>
#include <fmt/core.h>
#include <list>
#include <set>
#include <vector>

namespace urd
{
	entt::entity player;
	WorldGrid world(20, 12);
	Pathfind pathfind(world);

	float TileSize = 10.0f;

	vec2 CoordToPos(int x, int y)
	{
		assert(x >= 0 && x < world.width() && y >= 0 && y < world.height());
		return vec2{x * TileSize, y * TileSize};
	}
	void PosToCoord(vec2 pos, int& x, int& y)
	{
		x = (int)(pos.x / TileSize);
		y = (int)(pos.y / TileSize);
	}

	vec2i MapMotionDirect(CharacterMotionDirect dir)
	{
		switch (dir)
		{
			case CharacterMotionDirect::None:
				return vec2i::zero;
			case CharacterMotionDirect::Up:
				return vec2i::up;
			case CharacterMotionDirect::Down:
				return vec2i::down;
			case CharacterMotionDirect::Left:
				return vec2i::left;
			default:
				return vec2i::right;
		}
	}

	// ----------------------------------------------------------------------------------------
	void init(entt::registry& registry)
	{
		player = registry.create();
		registry.emplace<Coord>(player);
		registry.emplace<CacheKeyboardInput>(player);
		registry.emplace<MoveSpeed>(player, 20);
		registry.emplace<MotionDirect>(player);

		std::printf("init player :%d\n", entt::to_integral(player));

		int tileNum = world.width() * world.height();
		for (int i = 0; i < tileNum; i++)
		{
			world.getCellByIndex(i).pass = true; //mathf::random01() > 0.1f;
		}

		world.getCell(0, 0).pass = true;
		world.getCell(world.width() - 1, world.height() - 1).pass = true;

		// pathfind.test();
		pathfind.astar(world.tryGetCell(1, 1), world.tryGetCell(5, 5));
	}

	// ----------------------------------------------------------------------------------------
	void update(entt::registry& registry, float dt)
	{
		// 更新键盘输入
		{
			using input::KeyCode;

			auto view = registry.view<CacheKeyboardInput>();
			for (auto en : view)
			{
				auto& inp = view.get<CacheKeyboardInput>(en);
				if (input::getKeyDown(KeyCode::Up))
					inp.caceh_target_dir = CharacterMotionDirect::Up;
				else if (input::getKeyDown(KeyCode::Down))
					inp.caceh_target_dir = CharacterMotionDirect::Down;
				else if (input::getKeyDown(KeyCode::Left))
					inp.caceh_target_dir = CharacterMotionDirect::Left;
				else if (input::getKeyDown(KeyCode::Right))
					inp.caceh_target_dir = CharacterMotionDirect::Right;
			}
		}

		// 更新移动过程中角色的位置
		{
			auto view = registry.view<InMoveProcess, Coord, MoveSpeed>();
			for (auto en : view)
			{
				auto [moveProcess, coord, moveSpeed] =
					view.get<InMoveProcess, Coord, MoveSpeed>(en);

				float posDelta = moveSpeed.speed * dt;
				vec2 pos = vec2::MoveTowards(moveProcess.cur_pos, moveProcess.target_pos, posDelta);

				// 到达目标位置
				if ((pos - moveProcess.target_pos).magnitude() < 0.1f)
					registry.erase<InMoveProcess>(en);
				else
					moveProcess.cur_pos = pos;
			}
		}

		// 是否根据输入位置更改移动方向
		{
			auto view = registry.view<CacheKeyboardInput, Coord, MotionDirect>(
				entt::exclude<InMoveProcess>);
			for (auto en : view)
			{
				const auto& inp = view.get<CacheKeyboardInput>(en);
				if (inp.caceh_target_dir != CharacterMotionDirect::None)
				{
					const auto& coord = view.get<Coord>(en);
					vec2i dir = MapMotionDirect(inp.caceh_target_dir);
					vec2i nextCoord = vec2i{coord.x, coord.y} + dir;

					Tile* peekTile = world.tryGetCell(nextCoord.x, nextCoord.y);
					if (peekTile && peekTile->pass)
					{
						auto& motion = view.get<MotionDirect>(en);
						motion.dir = inp.caceh_target_dir;
					}
				}
			}
		}

		// 在角色到达目标位置后立即开始下一步移动过程
		{
			auto view = registry.view<Coord, MotionDirect>(entt::exclude<InMoveProcess>);
			for (auto en : view)
			{
				auto [coord, motionDirect] = view.get<Coord, MotionDirect>(en);

				if (motionDirect.dir != CharacterMotionDirect::None)
				{
					vec2i dir = MapMotionDirect(motionDirect.dir);
					vec2i nextCoord = vec2i{coord.x, coord.y} + dir;

					Tile* peekTile = world.tryGetCell(nextCoord.x, nextCoord.y);
					if (peekTile && peekTile->pass)
					{
						vec2 curPos = CoordToPos(coord.x, coord.y);
						vec2 targetPos = CoordToPos(nextCoord.x, nextCoord.y);

						coord.x = nextCoord.x;
						coord.y = nextCoord.y;

						registry.emplace<InMoveProcess>(en, targetPos, curPos);
					}
				}
			}
		}
	}

	// ----------------------------------------------------------------------------------------
	void draw(const entt::registry& registry)
	{
		for (int i = 0; i < world.width() * world.height(); i++)
		{
			auto& tile = world.getCellByIndex(i);
			vec2 pos = CoordToPos(tile.x, tile.y);

			color c = color::white;
			if (!tile.pass)
			{
				c = color::red;
				visual::mark(pos, c);
			}
			visual::box(pos, vec2::one * TileSize, c);
		}

		// static color playerColor[]{color::red, color::yellow, color::blue};
		{
			const auto view = registry.view<Coord>();
			for (auto en : view)
			{
				vec2 realPos;

				auto moveProcess = registry.try_get<InMoveProcess>(en);
				if (moveProcess)
					realPos = moveProcess->cur_pos;
				else
				{
					auto& coord = view.get<Coord>(en);
					realPos = CoordToPos(coord.x, coord.y);
				}
				visual::box(realPos, vec2{10, 10}, color::green);
			}
		}

		visual::mark(vec2{}, color::red);
	}
} // namespace urd
