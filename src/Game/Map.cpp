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
			if (line[x] == '-')
			{
				tiles[y][x].type = Tile::blockType::EMPTY;
				tiles[y][x].solid = false;
			}
			else if (line[x] == '#')
			{
				tiles[y][x].type = Tile::blockType::BLOCK;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'U')
			{
				tiles[y][x].type = Tile::blockType::PLATFORM;
				tiles[y][x].solid = true;
			}
			else if (line[x] == '[')
			{
				tiles[y][x].type = Tile::blockType::PLATFORM_LEFT;
				tiles[y][x].solid = true;
			}
			else if (line[x] == ']')
			{
				tiles[y][x].type = Tile::blockType::PLATFORM_RIGHT;
				tiles[y][x].solid = true;
			}
			else if (line[x] == '_')
			{
				tiles[y][x].type = Tile::blockType::PLATFORM_TOP;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'u')
			{
				tiles[y][x].type = Tile::blockType::PLATFORM_BOTTOM;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'f')
			{
				tiles[y][x].type = Tile::blockType::FLOOR;
				tiles[y][x].solid = true;
			}
			else if (line[x] == '<')
			{
				tiles[y][x].type = Tile::blockType::FLOOR_LEFT_EDGE;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'L')
			{
				tiles[y][x].type = Tile::blockType::FLOOR_LEFT_WALL;
				tiles[y][x].solid = true;
			}
			else if (line[x] == '>')
			{
				tiles[y][x].type = Tile::blockType::FLOOR_RIGHT_EDGE;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'R')
			{
				tiles[y][x].type = Tile::blockType::FLOOR_RIGHT_WALL;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'l')
			{
				tiles[y][x].type = Tile::blockType::WALL_LEFT;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'r')
			{
				tiles[y][x].type = Tile::blockType::WALL_RIGHT;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'c')
			{
				tiles[y][x].type = Tile::blockType::CEILING;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'j')
			{
				tiles[y][x].type = Tile::blockType::CEILING_LEFT_EDGE;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'J')
			{
				tiles[y][x].type = Tile::blockType::CEILING_LEFT_WALL;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 't')
			{
				tiles[y][x].type = Tile::blockType::CEILING_RIGHT_EDGE;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'T')
			{
				tiles[y][x].type = Tile::blockType::CEILING_RIGHT_WALL;
				tiles[y][x].solid = true;
			}
			else if (line[x] == '=')
			{
				tiles[y][x].type = Tile::blockType::FLOOR_CEILING;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'I')
			{
				tiles[y][x].type = Tile::blockType::WALL_BOTH;
				tiles[y][x].solid = true;
			}
			else if (line[x] == 'x')
			{
			tiles[y][x].type = Tile::blockType::LAVA;
			tiles[y][x].solid = false;
			}
			else if (line[x] == '~')
			{
			tiles[y][x].type = Tile::blockType::LAVA_SURFACE;
			tiles[y][x].solid = false;
			}
			else if (line[x] == '+')
			{
			tiles[y][x].type = Tile::blockType::BREAKABLE;
			tiles[y][x].solid = true;
			}
		}
	}
}

void Map::setTileset(const std::shared_ptr<Sprite>& _tileset)
{
	tileset = _tileset;
	frame = { 0, 0, tileSize, tileSize };
	renderPosition = { 0, 0, tileSize, tileSize };
}

Tile Map::GetTile(int x, int y)
{
	return tiles[y][x];
}

void Map::clearTile(const int& _x, const int& _y)
{
	tiles[_y][_x].type = Tile::blockType::EMPTY;
	tiles[_y][_x].solid = false;
}

void Map::onDraw(SDL_Renderer* _renderer)
{
	for (size_t y = 0; y < tiles.size(); ++y)
	{
		renderPosition.y = y * tileSize;
		renderPosition.y -= int(getCore()->getCamera()->getView().y);

		for (size_t x = 0; x < tiles[y].size(); ++x)
		{
			renderPosition.x = x * tileSize;
			renderPosition.x -= int(getCore()->getCamera()->getView().x);

			switch (tiles[y][x].type)
			{
			case Tile::blockType::EMPTY:
			{
				break;
			}
			case Tile::blockType::BLOCK:
			{
				frame.x = 2 * tileSize;
				frame.y = 1 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::PLATFORM:
			{
				frame.x = 0;
				frame.y = 3 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::PLATFORM_LEFT:
			{
				frame.x = 1 * tileSize;
				frame.y = 3 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::PLATFORM_RIGHT:
			{
				frame.x = 3 * tileSize;
				frame.y = 3 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::PLATFORM_TOP:
			{
				frame.x = 0;
				frame.y = 0;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::PLATFORM_BOTTOM:
			{
				frame.x = 0;
				frame.y = 2 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::FLOOR:
			{
				frame.x = 2 * tileSize;
				frame.y = 0;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::FLOOR_LEFT_EDGE:
			{
				frame.x = 1 * tileSize;
				frame.y = 0;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::FLOOR_LEFT_WALL:
			{
				frame.x = 4 * tileSize;
				frame.y = 1 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::FLOOR_RIGHT_EDGE:
			{
				frame.x = 3 * tileSize;
				frame.y = 0;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::FLOOR_RIGHT_WALL:
			{
				frame.x = 5 * tileSize;
				frame.y = 1 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::WALL_LEFT:
			{
				frame.x = 3 * tileSize;
				frame.y = 1 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::WALL_RIGHT:
			{
				frame.x = 1 * tileSize;
				frame.y = 1 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::CEILING:
			{
				frame.x = 2 * tileSize;
				frame.y = 2 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::CEILING_LEFT_EDGE:
			{
				frame.x = 3 * tileSize;
				frame.y = 2 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::CEILING_LEFT_WALL :
			{
				frame.x = 4 * tileSize;
				frame.y = 0;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::CEILING_RIGHT_EDGE:
			{
				frame.x = 1 * tileSize;
				frame.y = 2 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::CEILING_RIGHT_WALL:
			{
				frame.x = 5 * tileSize;
				frame.y = 0;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::FLOOR_CEILING:
			{
				frame.x = 2 * tileSize;
				frame.y = 3 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::WALL_BOTH:
			{
				frame.x = 0;
				frame.y = 1 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::LAVA:
			{
				frame.x = 4 * tileSize;
				frame.y = 3 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::LAVA_SURFACE:
			{
				frame.x = 4 * tileSize;
				frame.y = 2 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			case Tile::blockType::BREAKABLE:
			{
				frame.x = 5 * tileSize;
				frame.y = 2 * tileSize;
				SDL_RenderCopy(_renderer, tileset->texture, &frame, &renderPosition);
				break;
			}
			}
		}
	}
}
