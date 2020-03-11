#include <memory>
#include <list>

class Entity;
struct SDL_FPoint;

class Camera
{
public:
	void move(const SDL_FPoint& _direction);

private:
	void updateTilesOnScreen(const SDL_Point& _direction);

	float width;
	float height;
	SDL_FPoint previousPosition;
	SDL_FPoint position;

	std::list<std::list<std::shared_ptr<Entity>>> tilesOnScreen;

	// Map
	//std::list<std::list<int>> tilesOnScreen;
};
