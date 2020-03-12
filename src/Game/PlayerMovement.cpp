#include "PlayerMovement.h"

void PlayerMovement::setRenderer(std::shared_ptr<SpriteRenderer> _renderer)
{
	renderer = _renderer;
}

void PlayerMovement::onStart()
{
	input = getCore()->getInput();

	velocity.x = 0.0f;
	velocity.y = 0.0f;
	airborne = true;
	updateSprite();
}

void PlayerMovement::onUpdate()
{
	// Input
	if (input->keyPress(SDLK_a))
	{
		// Walk left
		velocity.x -= 50.0f;
		updateSprite();
	}

	if (input->keyRelease(SDLK_a))
	{
		// Stop walking left
		velocity.x += 50.0f;
		updateSprite();
	}

	if (input->keyPress(SDLK_d))
	{
		// Walk right
		velocity.x += 50.0f;
		updateSprite();
	}

	if (input->keyRelease(SDLK_d))
	{
		// Stop walking right
		velocity.x -= 50.0f;
		updateSprite();
	}

	if (input->keyPress(SDLK_k))
	{
		// Jump
		if (!airborne) jump();
	}

	// Update position
	getEntity()->transform.position.x += velocity.x * getCore()->getDeltaTime();
	getEntity()->transform.position.y += velocity.y * getCore()->getDeltaTime();

	// Gravity
	velocity.y += 200.0f * getCore()->getDeltaTime();

	// Hardcoded floor
	if (getEntity()->transform.position.y > 200.0f)
	{
		// Landing
		if (airborne)
		{
			airborne = false;
			updateSprite();
		}

		getEntity()->transform.position.y = 200.0f;
		velocity.y = 0.0f;
	}

	// (Dropping off a ledge)
	if (!airborne && velocity.y > 5.0f)
	{
		airborne = true;
		updateSprite();
	}
}

void PlayerMovement::jump()
{
	velocity.y = -100.0f;
	airborne = true;
	updateSprite();
}

void PlayerMovement::updateSprite()
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
