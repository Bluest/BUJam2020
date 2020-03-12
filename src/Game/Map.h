#include "Engine.h"

struct Tile
{
	enum blockType
	{
		EMPTY,
		BREAKABLE,
		REGULAR,
		DAMAGE
	};

	bool solid = false;
};

class Map : public Component
{
public:

	const int tileSize = 32;

	const int height = 10;
	const int width = 15;

	void LoadFromFile();
	void setTileset(const std::shared_ptr<Sprite>& _tileset);

	Tile GetTile(int x, int y);

private:

	void onDraw(SDL_Renderer* _renderer);

	std::vector<std::vector<Tile>> tiles;
	std::shared_ptr<Sprite> tileset;
	SDL_Rect frame;
};
