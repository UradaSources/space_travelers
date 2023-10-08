#pragma once
#include "WorldGrid.h"
#include "common/vec2i.h"

#include <cstdio>
#include <list>
#include <memory>
#include <raylib.h>
#include <set>
#include <vector>

namespace urd
{
	class Pathfind
	{
		struct Node
		{
			std::shared_ptr<Node> parent;

			int id;
			const Tile* tile;

			float g;
			float h;

			constexpr float f() const { return g + h; }
			constexpr Node(int id, const Tile* tile): id(id), tile(tile), g(0), h(0) {}
		};

		using NodePtr = std::shared_ptr<Node>;

		struct _nodeSort
		{
			using is_transparent = void;

			constexpr bool operator()(const NodePtr& a, const NodePtr& b) const
			{
				return a->id < b->id;
			}
			constexpr bool operator()(int id, const NodePtr& n) const { return id < n->id; }
			constexpr bool operator()(const NodePtr& n, int id) const { return id < n->id; }
		};

	  private:
		const WorldGrid& m_grid;

		std::set<NodePtr, _nodeSort> m_nodeSet;

		std::set<NodePtr, _nodeSort> m_open;
		std::set<NodePtr, _nodeSort> m_close;

		NodePtr getOrBuildNode(int x, int y);

	  public:
		Pathfind(const WorldGrid& world);
		Pathfind(const Pathfind&) = delete;
		Pathfind(Pathfind&&) = default;

		void astar(const Tile* start, const Tile* target);
	};
} // namespace urd