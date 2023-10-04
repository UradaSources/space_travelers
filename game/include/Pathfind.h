#pragma once
#include "WorldGrid.h"
#include "common/vec2i.h"

#include <cstdio>
#include <list>
#include <raylib.h>
#include <set>

namespace urd
{
	struct Node
	{
		const Tile* tile;

		const Node* last;

		float g;
		float h;

		inline float f() const { return g + h; }
		inline bool fBetter(float gNew) const { return gNew + h < this->f(); }
		inline bool vaild() const { return tile != nullptr; }
	};

	struct _nodeSort
	{
		using is_transparent = void;

		bool operator()(const Node& a, const Node& b) const;

		bool operator()(vec2i coord, const Node& n) const;
		bool operator()(const Node& n, vec2i coord) const;
	};

	class Pathfind
	{
	  public:
		using NodeRef = std::reference_wrapper<Node>;

	  private:
		const WorldGrid& m_grid;

		std::set<Node, _nodeSort> m_nodeSet;

		std::set<NodeRef, _nodeSort> m_open;
		std::set<NodeRef, _nodeSort> m_close;

		bool getOrBuildNode(int x, int y, Node& node);

	  public:
		Pathfind(const WorldGrid& world);
		Pathfind(const Pathfind&) = delete;
		Pathfind(Pathfind&&) = default;

		void test()
		{
			Node raw[]{
				Node{m_grid.tryGetCell(0, 0), nullptr, 0.0f, 0},
				Node{m_grid.tryGetCell(1, 0), nullptr, 2.0f, 0},
				Node{m_grid.tryGetCell(0, 1), nullptr, 3.0f, 0},
				Node{m_grid.tryGetCell(2, 2), nullptr, 1.0f, 0},
				Node{m_grid.tryGetCell(2, 3), nullptr, 1.0f, 0},
				Node{m_grid.tryGetCell(0, 2), nullptr, 0.5f, 0},
			};

			m_nodeSet.insert(raw, raw + 6);

			for (const Node& n : m_nodeSet)
				std::printf("%f->{%d, %d}\n", n.f(), n.tile->x, n.tile->y);

			auto it = m_nodeSet.find(Node{m_grid.tryGetCell(10, 10), nullptr, 0,0});
			if (it != m_nodeSet.end())
			{
				const Node& n = (*it);
				std::printf("good, %f:{%d,%d}\n", n.f(), n.tile->x, n.tile->y);
			}
			else
			{
				std::printf("bad\n");
			}
		}
		void astar(const Tile* start, const Tile* target);
	};
} // namespace urd