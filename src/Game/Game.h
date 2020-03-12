#include "Engine.h"

class Game
{
public:
	
	Game();

	void Run();

private:
	std::shared_ptr<Core> core;
	std::shared_ptr<SpriteManager> sprites;

	void Init();
	void loadSprites();
};
