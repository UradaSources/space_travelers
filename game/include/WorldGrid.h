#pragma once
#include <vector>

struct Tile
{
	int x, y;
	bool pass;
};

class WorldGrid
{
  private:
	int m_width;
	int m_height;

	std::vector<Tile> m_tileArray;

  public:
	WorldGrid(int w, int h);

	WorldGrid(const WorldGrid&) = default;
	WorldGrid(WorldGrid&&) = default;

	WorldGrid& operator=(const WorldGrid&) = default;
	WorldGrid& operator=(WorldGrid&&) = default;

	int width() const;
	int height() const;

	bool vaildCoord(int x, int y) const;
	int toIndex(int x, int y) const;

	Tile& getCell(int x, int y);
	Tile& getCellByIndex(int index);
	Tile* tryGetCell(int x, int y);

	const Tile& getCell(int x, int y) const;
	const Tile& getCellByIndex(int index) const;
	const Tile* tryGetCell(int x, int y) const;
};