#include "SDL_rect.h"

#include <memory>
#include <list>

class Entity;

class Camera
{
public:
	void move(const SDL_FPoint& _direction);

	void setPosition(const SDL_FPoint& _position);
	SDL_FRect getView();

private:
	void updateTilesOnScreen(const SDL_Point& _direction);

	const float mapWidth = 1376.0f;
	const float mapHeight = 1312.0f;
	const float width = 320.0f;
	const float height = 240.0f;

	SDL_FPoint previousPosition;
	SDL_FPoint position;

	std::list<std::list<std::shared_ptr<Entity>>> tilesOnScreen;

	// Map
	//std::list<std::list<int>> tilesOnScreen;
};
