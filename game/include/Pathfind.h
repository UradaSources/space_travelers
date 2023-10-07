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

		std::list<NodeRef> m_open;
		std::list<NodeRef> m_close;

		bool getOrBuildNode(int x, int y, Node& node);

	  public:
		Pathfind(const WorldGrid& world);
		Pathfind(const Pathfind&) = delete;
		Pathfind(Pathfind&&) = default;

		void astar(const Tile* start, const Tile* target);
	};
} // namespace urd