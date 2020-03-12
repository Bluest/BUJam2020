#include <stdlib.h>
#include <time.h>

#include "Patrol.h"

void Patrol::onStart()
{
	startX = getEntity()->transform.position.x;
	startY = getEntity()->transform.position.y;

	yVelocity = 0.0f;
	airborne = false;
}

void Patrol::onUpdate()
{
	getEntity()->transform.position.y += yVelocity;
	yVelocity += 5.0f * getCore()->getDeltaTime();

	if (getEntity()->transform.position.y > startY)
	{
		getEntity()->transform.position.y = startY;
		airborne = false;
	}

	Move();
	Jump();
}

void Patrol::Move()
{
	if (movingRight)
	{
		getEntity()->transform.position.x += movementSpeed * getCore()->getDeltaTime();
		renderer->setSprite(1);
		renderer->setAnimationSpeed(10.0f);
		renderer->setFlip(SDL_FLIP_HORIZONTAL);
		if (getEntity()->transform.position.x > waypoint)
		{
			movingRight = false;
		}
	}
	else
	{
		getEntity()->transform.position.x -= movementSpeed * getCore()->getDeltaTime();
		renderer->setSprite(1);
		renderer->setAnimationSpeed(10.0f);
		renderer->setFlip(SDL_FLIP_NONE);
		if (getEntity()->transform.position.x < startX)
		{
			movingRight = true;
		}
	}
}

void Patrol::Jump()
{
	if (jumpEnabled)
	{
		if (canJump)
		{
			yVelocity = -2.0f;
			airborne = true;
		}
	}
}

void Patrol::RandNum()
{
	std::srand(time_t(NULL));

	int x = std::rand() % 20 + 1;

	printf("%i", x);

	if (x == 1)
		canJump = true;
}

void Patrol::setRenderer(std::shared_ptr<SpriteRenderer> _renderer)
{
	renderer = _renderer;
}

void Patrol::setMovementSpeed(float _movementSpeed)
{
	movementSpeed = _movementSpeed;
}

void Patrol::enableJump(bool _jumpEnabled)
{
	jumpEnabled = _jumpEnabled;
}

void Patrol::setEnd(float _b)
{
	waypoint = _b;
}
