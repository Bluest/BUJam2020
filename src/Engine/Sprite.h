#include <string>

struct SDL_Texture;

struct Sprite
{
	std::string name;
	SDL_Texture* texture = nullptr;
	int width = NULL;
	int height = NULL;
	int frames = NULL;
};
