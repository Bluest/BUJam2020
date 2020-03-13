#include "PlayerState.h"

void PlayerState::updateSprite()
{
	// Update facing
	if (velocity.x > 0.0f)
	{
		// Facing right
		renderer->setFlip(SDL_FLIP_NONE);
	}
	else if (velocity.x < 0.0f)
	{
		// Facing left
		renderer->setFlip(SDL_FLIP_HORIZONTAL);
	}

	if (airborne)
	{
		// Jumping
		switch (level)
		{
		case 0:
		{
			renderer->setSprite(2);
			renderer->setAnimationSpeed(10.0f);
			break;
		}
		case 1:
		{
			renderer->setSprite(5);
			renderer->setAnimationSpeed(10.0f);
			break;
		}
		}
	}
	else
	{
		if (velocity.x == 0.0f)
		{
			// Idle
			switch (level)
			{
			case 0:
			{
				renderer->setSprite(0);
				renderer->setAnimationSpeed(5.0f);
				break;
			}
			case 1:
			{
				renderer->setSprite(3);
				renderer->setAnimationSpeed(5.0f);
			}
			}

		}
		else
		{
			// Walking
			switch (level)
			{
			case 0:
			{
				renderer->setSprite(1);
				renderer->setAnimationSpeed(10.0f);
				break;
			}
			case 1:
			{
				renderer->setSprite(4);
				renderer->setAnimationSpeed(10.0f);
			}
			}
		}
	}
}

void PlayerState::levelUp(const int& _level)
{
	switch (_level)
	{
	case 1:
	{
		level = 1;
		moveSpeed = 80.0f;
		jumpHeight = -200.0f;
	}
	}
}

void PlayerState::setRenderer(const std::shared_ptr<SpriteRenderer>& _renderer)
{
	renderer = _renderer;
	renderer->setRenderOffset({ 0.0f, -10.0f });
}

void PlayerState::onStart()
{
	level = 0;

	moveSpeed = 50.0f;
	jumpHeight = -120.0f;
	gravity = 200.0f;
	velocity = { 0.0f, 0.0f };
	airborne = true;

	updateSprite();
}
