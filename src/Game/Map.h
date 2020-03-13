#include "Engine.h"

struct Tile
{
	enum blockType
	{
		EMPTY,
		BLOCK,
		PLATFORM,
		PLATFORM_LEFT,
		PLATFORM_RIGHT,
		PLATFORM_TOP,
		PLATFORM_BOTTOM,
		FLOOR,
		FLOOR_LEFT_EDGE,
		FLOOR_LEFT_WALL,
		FLOOR_RIGHT_EDGE,
		FLOOR_RIGHT_WALL,
		WALL_LEFT,
		WALL_RIGHT,
		CEILING,
		CEILING_LEFT_EDGE,
		CEILING_LEFT_WALL,
		CEILING_RIGHT_EDGE,
		CEILING_RIGHT_WALL,
		FLOOR_CEILING,
		WALL_BOTH,
		LAVA,
		LAVA_SURFACE
	};

	blockType type;
	bool solid = false;
};

class Map : public Component
{
public:
	const int tileSize = 32;

	const int height = 41;
	const int width = 43;

	void LoadFromFile();
	void setTileset(const std::shared_ptr<Sprite>& _tileset);

	Tile GetTile(int x, int y);

private:
	void onDraw(SDL_Renderer* _renderer);

	std::vector<std::vector<Tile>> tiles;
	std::shared_ptr<Sprite> tileset;
	SDL_Rect frame;
	SDL_Rect renderPosition;
};
