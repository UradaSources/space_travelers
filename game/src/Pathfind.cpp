#include "Pathfind.h"

#include "WorldGrid.h"
#include "common/mathf.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <functional>

namespace urd
{
	vec2i nearDirect[] = {vec2i::left, vec2i::up, vec2i::down, vec2i::right};

	float MDist(const Tile* a, const Tile* b)
	{
		return mathf::abs(b->x - a->x) + mathf::abs(b->y - a->y);
	}

	std::shared_ptr<Pathfind::Node> Pathfind::getOrBuildNode(int x, int y)
	{
		if (m_grid.vaildCoord(x, y))
		{
			int id = m_grid.toIndex(x, y);

			auto it = m_nodeSet.find(id);
			if (it == m_nodeSet.end())
			{
				const Tile& tile = m_grid.getCell(x, y);
				auto pair = m_nodeSet.insert(std::make_shared<Node>(id, &tile));
				assert(pair.second);
				return *pair.first;
			}
			else
				return *it;
		}
		return nullptr;
	}

	Pathfind::Pathfind(const WorldGrid& world): m_grid(world) {}

	void Pathfind::astar(const Tile* start, const Tile* target)
	{
		m_open.clear();
		m_close.clear();

		Node firstNode;
		assert(this->getOrBuildNode(start->x, start->y, firstNode));

		m_open.insert(std::ref(firstNode));

		while (!m_open.empty())
		{
			float fMin = 10000;
			std::reference_wrapper<Node> fMinNode;

			for (Node& node : m_open)
			{
				if (node.f() <= fMin)
				{
					fMin = node.f();
					fMinNode = node;
				}
			}

			// 查找open列表中f值最小的节点
			// 将其从open列表中移除并加入close列表
			Node& curNode = m_open.back();

			m_open.pop_back();
			m_close.push_back(std::ref(curNode));

			if (curNode.tile != target)
			{
				auto curTile = curNode.tile;

				std::vector<std::reference_wrapper<Node>> vaildNrarNodes;
				vaildNrarNodes.reserve(4);

				for (auto dir : nearDirect)
				{
					int x = curTile->x + dir.x;
					int y = curTile->y + dir.y;

					// 获取对应方向上的临近节点, 该节点需要存在且可用
					// 且不在close列表中
					// 若满足全部条件则将其暂存到列表中
					Node nearNode;
					if (this->getOrBuildNode(x, y, nearNode)) // && nearNode.tile->pass)
					{
						if (!std::binary_search(m_close.begin(), m_close.end(), nearNode))
							vaildNrarNodes.push_back(std::ref(nearNode));
					}
				}

				// 处理全部的临近节点
				for (Node& nearNode : vaildNrarNodes)
				{
					// 检查当前临近节点是否在开放列表中
					auto openNodeIt = m_open.find(nearNode);
					if (openNodeIt != m_open.end())
					{
						// 直接修改所引用对象的值并不会使set自动排序
						// 所以统一将其从open中移除
						// 稍后将整个vaildNrarNodes重新插入open
						Node& node = *openNodeIt;
						m_open.erase(openNodeIt);

						// 测试新提供的g值是否令f值更小
						float gNew = curNode.g + 10;
						if (node.fBetter(gNew))
						{
							// 更新父节点和g值
							node.parent = &curNode;
							node.g = gNew;
						}
					}
					else
					{
						nearNode.parent = &curNode;
						nearNode.g = curNode.g + 10;

						// 计算当前节点到目标的距离h值,
						// 在整个算法过程中, h总是不变
						nearNode.h = MDist(target, nearNode.tile);
					}
				}

				// 将所有节点加入open中
				// 这也将触发排序函数根据f值对所有节点进行排序
				m_open.insert(vaildNrarNodes.begin(), vaildNrarNodes.end());
			}
			else
			{
				std::printf("pathfind done.\n");
				for (auto i = m_open.rbegin(); i != m_open.rend(); i++)
				{
					Node& n = *i;
					std::printf("{%d, %d}\n", n.tile->x, n.tile->y);
				}
				return;
			}
		}
		std::printf("pathfind faild.\n");

		std::printf("open:\n");
		for (auto i = m_open.rbegin(); i != m_open.rend(); i++)
		{
			Node& n = *i;
			std::printf("%p{%d, %d}<=%p\n", &n, n.tile->x, n.tile->y, n.parent);
		}

		std::printf("close:\n");
		for (auto i = m_close.rbegin(); i != m_close.rend(); i++)
		{
			Node& n = *i;
			std::printf("%p{%d, %d}<=%p\n", &n, n.tile->x, n.tile->y, n.parent);
		}
	}
} // namespace urd
