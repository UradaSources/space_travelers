#include <common/vec2i.h>
#include <cstdio>
#include <functional>
#include <set>

using namespace urd;

struct Node
{
	float f;
	vec2i coord;
};

struct _CoordSort
{
	using is_transparent = void;

	bool operator()(const Node& a, const Node& b) const
	{
		if (a.coord.y == b.coord.y)
			return a.coord.x < b.coord.x;
		else
			return a.coord.y < b.coord.y;
	}
	bool operator()(vec2i coord, const Node& a) const
	{
		if (a.coord.y == coord.y)
			return a.coord.x < coord.x;
		else
			return a.coord.y < coord.y;
	}
	bool operator()(const Node& a, vec2i coord) const
	{
		if (a.coord.y == coord.y)
			return a.coord.x < coord.x;
		else
			return a.coord.y < coord.y;
	}
};

struct _FSort
{
	bool operator()(const Node& a, const Node& b) const
	{
		if (a.f != b.f)
			return a.f < b.f;
		else
		{
			if (a.coord.y == b.coord.y)
				return a.coord.x < b.coord.x;
			else
				return a.coord.y < b.coord.y;
		}
	}
};

int main()
{
	Node raw[]{
		Node{12, vec2i{1, 2}},
		Node{1, vec2i{8, 0}},
		Node{90, vec2i{4, 2}},
		Node{2, vec2i{1, 3}},
		Node{78, vec2i{2, 2}},
	};

	std::set<std::reference_wrapper<Node>, _FSort> all;

	// auto i = std::ref(raw[0]);
	for (auto it = raw; it != raw + 5; it++)
	{
		all.insert(std::ref(*it));
	}

	// 修改第一个元素
	Node& first = *all.begin();

	first.f = 100;

	// std::printf("%f\n", (*all.begin()).get().f);

	for (const Node& n : all)
		std::printf("%f->{%d, %d}\n", n.f, n.coord.x, n.coord.y);

	// auto it = all.find(vec2i{1, 2});
	// if (it != all.end())
	// {
	// 	const Node& n = (*it).get();
	// 	std::printf("good, %f:{%d,%d}\n", n.f, n.coord.x, n.coord.y);
	// }
	// else
	// {
	// 	std::printf("bad\n");
	// }

	auto it = all.find(raw[1]);
	if (it != all.end())
	{
		const Node& n = (*it).get();
		std::printf("good, %f:{%d,%d}\n", n.f, n.coord.x, n.coord.y);
	}
	else
	{
		std::printf("bad\n");
	}

	return 0;
}