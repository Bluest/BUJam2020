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

void Camera::setPosition(const SDL_FPoint& _position)
{
	position = _position;

	if (position.x - width / 2 < 0.0f)
	{
		position.x = width / 2;
	}

	if (position.x + width / 2 > mapWidth)
	{
		position.x = mapWidth - width / 2;
	}

	if (position.y - height / 2 < 0.0f)
	{
		position.y = height / 2;
	}

	if (position.y + height / 2 > mapHeight)
	{
		position.y = height / 2;
	}
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
