#include "PlayerMovement.h"

void PlayerMovement::setRenderer(std::shared_ptr<SpriteRenderer> _renderer)
{
	renderer = _renderer;
}

void PlayerMovement::onStart()
{
	input = getCore()->getInput();

	yVelocity = 0.0f;
	airborne = false;
}

void PlayerMovement::onUpdate()
{
	getEntity()->transform.position.y += yVelocity;
	yVelocity += 5.0f * getCore()->getDeltaTime();

	if (getEntity()->transform.position.y > 250.0f)
	{
		getEntity()->transform.position.y = 250.0f;
		airborne = false;
	}

	if (input->keyPress(SDLK_a))
	{
		renderer->setSprite(1);
		renderer->setAnimationSpeed(10.0f);
		renderer->setFlip(SDL_FLIP_HORIZONTAL);
	}

	if (input->keyRelease(SDLK_a))
	{
		renderer->setSprite(0);
		renderer->setAnimationSpeed(5.0f);
		renderer->setFlip(SDL_FLIP_HORIZONTAL);
	}

	if (input->keyHold(SDLK_a))
	{
		getEntity()->transform.position.x -= 100.0f * getCore()->getDeltaTime();
	}

	if (input->keyPress(SDLK_d))
	{
		renderer->setSprite(1);
		renderer->setAnimationSpeed(10.0f);
		renderer->setFlip(SDL_FLIP_NONE);
	}

	if (input->keyRelease(SDLK_d))
	{
		renderer->setSprite(0);
		renderer->setAnimationSpeed(5.0f);
		renderer->setFlip(SDL_FLIP_NONE);
	}

	if (input->keyHold(SDLK_d))
	{
		getEntity()->transform.position.x += 100.0f * getCore()->getDeltaTime();
	}

	if (input->keyPress(SDLK_k))
	{
		if (!airborne) jump();
	}
}

void PlayerMovement::jump()
{
	yVelocity = -2.0f;
	airborne = true;
}
