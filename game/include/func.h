#pragma once
#include "common/vec2.h"
#include "common/vec2i.h"

#include <entt/entt.hpp>

namespace urd
{
	enum class CharacterMotionDirect
	{
		None,
		Up,
		Down,
		Left,
		Right
	};

	// 是否从键盘获取输入
	struct CacheKeyboardInput
	{
		CharacterMotionDirect caceh_target_dir; // 缓存的输入
	};

	// 当前的坐标位置
	struct Coord
	{
		int x, y;
	};

	// 正在移动过程中
	struct InMoveProcess
	{
		vec2 target_pos;
		vec2 cur_pos;
	};

	// 移动速度
	struct MoveSpeed
	{
		float speed;
	};

	// 当前的运动方向
	struct MotionDirect
	{
		CharacterMotionDirect dir;
	};

	void init(entt::registry& registry);
	void update(entt::registry& registry, float dt);

	void draw(const entt::registry& registry);
} // namespace urd
