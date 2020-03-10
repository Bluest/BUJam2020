#include "SDL_image.h"
#include "SDL_render.h"

#include "Sprite.h"
#include "SpriteManager.h"

SpriteManager::SpriteManager(SDL_Renderer* _renderer)
{
	renderer = _renderer;
}

SpriteManager::~SpriteManager()
{
	for (auto it = sprites.begin(); it != sprites.end(); ++it)
	{
		SDL_DestroyTexture((*it)->texture);
		(*it)->texture = nullptr;
	}
}

void SpriteManager::load(const std::string& _name, const std::string& _file, const int& _frames)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

	sprite->name = _name;
	sprite->texture = IMG_LoadTexture(renderer, _file.c_str());
	SDL_QueryTexture(sprite->texture, nullptr, nullptr, &sprite->width, &sprite->height);
	sprite->frames = _frames;

	sprites.push_back(sprite);
}

std::shared_ptr<Sprite> SpriteManager::use(const std::string& _name)
{
	for (auto it = sprites.begin(); it != sprites.end(); ++it)
	{
		if ((*it)->name == _name)
		{
			return *it;
		}
	}

	return nullptr;
}
