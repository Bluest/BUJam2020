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

	const int height = 4;
	const int width = 4;

	void LoadFromFile();

	Tile GetTile(int x, int y);

private:

	void onDraw(SDL_Renderer* _renderer);



	std::vector<std::vector<Tile>> tiles;

};
