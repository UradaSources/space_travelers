#include "WorldGrid.h"

#include <cassert>

WorldGrid::WorldGrid(int w, int h): m_width(w), m_height(h), m_tileArray(w * h)
{
	int i = 0;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			auto& tile = m_tileArray[i++];
			tile.x = x;
			tile.y = y;
		}
	}
}

int WorldGrid::width() const { return m_width; }
int WorldGrid::height() const { return m_height; }

bool WorldGrid::vaildCoord(int x, int y) const
{
	return x >= 0 && x < m_width && y >= 0 && y < m_height;
}
int WorldGrid::toIndex(int x, int y) const { return y * m_width + x; }

Tile& WorldGrid::getCell(int x, int y)
{
	assert(vaildCoord(x, y));
	return m_tileArray[toIndex(x, y)];
}
Tile& WorldGrid::getCellByIndex(int index)
{
	return m_tileArray.at(index);
}
Tile* WorldGrid::tryGetCell(int x, int y)
{
	if (vaildCoord(x, y))
		return &m_tileArray[toIndex(x, y)];
	return nullptr;
}

const Tile& WorldGrid::getCell(int x, int y)const
{
	assert(vaildCoord(x, y));
	return m_tileArray[toIndex(x, y)];
}
const Tile& WorldGrid::getCellByIndex(int index)const
{
	return m_tileArray.at(index);
}
const Tile* WorldGrid::tryGetCell(int x, int y)const
{
	if (vaildCoord(x, y))
		return &m_tileArray[toIndex(x, y)];
	return nullptr;
}
