#include <memory>
#include <list>

class Entity;
struct SDL_FPoint;

class Camera
{
public:
	void move(const SDL_FPoint& _direction);

	void setPosition(const SDL_FPoint& _position);

private:
	void updateTilesOnScreen(const SDL_Point& _direction);

	const float mapWidth = 960.0f;
	const float mapHeight = 640.0f;

	const float width = 640.0f;
	const float height = 480.0f;
	SDL_FPoint previousPosition;
	SDL_FPoint position;

	std::list<std::list<std::shared_ptr<Entity>>> tilesOnScreen;

	// Map
	//std::list<std::list<int>> tilesOnScreen;
};
