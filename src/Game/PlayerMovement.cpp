#include "PlayerCollision.h"
#include "PlayerMovement.h"
#include "PlayerState.h"

void PlayerMovement::setRenderer(const std::shared_ptr<SpriteRenderer>& _renderer)
{
	renderer = _renderer;
}

void PlayerMovement::setPlayerState(const std::shared_ptr<PlayerState>& _playerState)
{
	playerState = _playerState;
}

void PlayerMovement::setCollider(const std::shared_ptr<PlayerCollision>& _collider)
{
	collider = _collider;
}

void PlayerMovement::onStart()
{
	input = getCore()->getInput();

	updateSprite();
}

void PlayerMovement::onUpdate()
{
	// Input
	if (input->keyPress(SDLK_a))
	{
		// Walk left
		playerState->velocity.x -= 50.0f;
		updateSprite();
	}

	if (input->keyRelease(SDLK_a))
	{
		// Stop walking left
		playerState->velocity.x += 50.0f;
		updateSprite();
	}

	if (input->keyPress(SDLK_d))
	{
		// Walk right
		playerState->velocity.x += 50.0f;
		updateSprite();
	}

	if (input->keyRelease(SDLK_d))
	{
		// Stop walking right
		playerState->velocity.x -= 50.0f;
		updateSprite();
	}

	if (input->keyPress(SDLK_k))
	{
		jump();
	}

	// Gravity
	playerState->velocity.y += 200.0f * getCore()->getDeltaTime();

	getEntity()->transform.position.x += playerState->velocity.x * getCore()->getDeltaTime();
	getEntity()->transform.position.y += playerState->velocity.y * getCore()->getDeltaTime();

	// Collisions

	// Hardcoded floor
	if (getEntity()->transform.position.y > 200.0f)
	{
		// Landing
		if (playerState->airborne)
		{
			playerState->airborne = false;
			updateSprite();
		}
	
		getEntity()->transform.position.y = 200.0f;
		playerState->velocity.y = 0.0f;
	}

	// (Dropping off a ledge)
	if (!playerState->airborne && playerState->velocity.y > 5.0f)
	{
		playerState->airborne = true;
		updateSprite();
	}
}

void PlayerMovement::jump()
{
	if (!playerState->airborne)
	{
		playerState->velocity.y = -100.0f;
		playerState->airborne = true;
		updateSprite();
	}
}

void PlayerMovement::updateSprite()
{
	// Update facing
	if (playerState->velocity.x > 0.0f)
	{
		// Facing right
		renderer->setFlip(SDL_FLIP_NONE);
	}
	else if (playerState->velocity.x < 0.0f)
	{
		// Facing left
		renderer->setFlip(SDL_FLIP_HORIZONTAL);
	}

	if (playerState->airborne)
	{
		// Jumping
		renderer->setSprite(2);
		renderer->setAnimationSpeed(10.0f);
	}
	else
	{
		if (playerState->velocity.x == 0.0f)
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
