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
				tiles[y][x].type = Tile::blockType::WALL;
				tiles[y][x].solid = true;
			}
			else
			{
				tiles[y][x].solid = false;
				tiles[y][x].type = Tile::blockType::EMPTY;
				printf("-");
			}
		}
		printf("\n");
	}
}

void Map::setTileset(const std::shared_ptr<Sprite>& _tileset)
{
	tileset = _tileset;
	frame = { 0, 0, tileSize, tileSize };
	renderPosition = { 0.0f, 0.0f, float(tileSize), float(tileSize) };
}

Tile Map::GetTile(int x, int y)
{
	return tiles[x][y];
}

void Map::onDraw(SDL_Renderer* _renderer)
{
	for (size_t y = 0; y < tiles.size(); ++y)
	{
		renderPosition.y = y * tileSize;

		for (size_t x = 0; x < tiles[y].size(); ++x)
		{
			renderPosition.x = x * tileSize;

			switch (tiles[y][x].type)
			{
			case Tile::blockType::EMPTY:
			{
				break;
			}
			case Tile::blockType::WALL:
			{
				//frame.x = tileSize;
				SDL_RenderCopyF(_renderer, tileset->texture, &frame, &renderPosition);
			}
			}
		}
	}
}
