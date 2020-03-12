#include <fstream>
#include <string>
#include <iostream>

#include "Map.h"

void Map::LoadFromFile()
{
	std::ifstream file("map.txt");
	std::string line;

	tiles.resize(height);
	for (int y = 0; y < height; ++y)
	{
		tiles[y].resize(width);
	}

	for (int y = 0; y < height; ++y)
	{
		std::getline(file, line);
		for (size_t x = 0; x < line.size(); ++x)
		{
			if (line[x] == '#')
			{
				printf("#");
				tiles[y][x].solid = true;
			}
			else
			{
				tiles[y][x].solid = false;
				printf("-");
			}
		}
		printf("\n");
	}
}

void Map::setTileset(const std::shared_ptr<Sprite>& _tileset)
{
	tileset = _tileset;
}

Tile Map::GetTile(int x, int y)
{
	return tiles[y][x];
}

void Map::onDraw(SDL_Renderer* _renderer)
{

}
