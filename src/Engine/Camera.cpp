#include "SDL_rect.h"

#include "Camera.h"

void Camera::move(const SDL_FPoint& _direction)
{
	position.x += _direction.x;
	position.y += _direction.y;

	if (int(position.x) != int(previousPosition.x) || int(position.y) != int(previousPosition.y))
	{
		SDL_Point direction;
		direction.x = int(_direction.x);
		direction.y = int(_direction.y);

		updateTilesOnScreen(direction);
	}

	previousPosition = position;
}

void Camera::updateTilesOnScreen(const SDL_Point& _direction)
{
	if (_direction.x == -1)
	{
		// left
		for (size_t row = 0; row < tilesOnScreen.size(); ++row)
		{
			tilesOnScreen.pop_front();
			//entitiesOnScreen.push_back(/**/);
		}
	}

	if (_direction.x == 1)
	{
		// right

	}
}
