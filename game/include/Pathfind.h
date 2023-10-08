#pragma once
#include "WorldGrid.h"
#include "common/vec2i.h"

#include <cstdio>
#include <list>
#include <raylib.h>
#include <set>
#include <vector>

namespace urd
{
	class Pathfind
	{
		struct Node
		{
			const Node* parent;

			int id;
			const Tile* tile;

			float g;
			float h;

			constexpr float f() const { return g + h; }
		};

		struct _nodeSort
		{
			using is_transparent = void;

			constexpr bool operator()(const Node& a, const Node& b) const { return a.id < b.id; }
			constexpr bool operator()(int id, const Node& n) const { return id < n.id; }
			constexpr bool operator()(const Node& n, int id) const { return id < n.id; }
		};

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

		void astar(const Tile* start, const Tile* target);
	};
} // namespace urd