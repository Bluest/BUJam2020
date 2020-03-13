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
		renderer->setSprite(2);
		renderer->setAnimationSpeed(10.0f);
	}
	else
	{
		if (velocity.x == 0.0f)
		{
			// Idle
			renderer->setSprite(0);
			renderer->setAnimationSpeed(5.0f);
		}
		else
		{
			// Walking
			renderer->setSprite(1);
			renderer->setAnimationSpeed(10.0f);
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
	moveSpeed = 50.0f;
	jumpHeight = -120.0f;
	gravity = 200.0f;
	velocity = { 0.0f, 0.0f };
	airborne = true;
}
