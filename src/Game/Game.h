#include "Engine.h"

class Game
{
public:
	
	Game();
	Game(int _winWidth, int _winHeight, int _scale, float _fpsCap);

	void Run();

private:
	std::shared_ptr<Core> core;
	std::shared_ptr<SpriteManager> sprites;

	void Init();

};
