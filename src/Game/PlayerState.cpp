#include "PlayerState.h"

void PlayerState::updateSprite()
{
	// Update facing
	if (velocity.x > 0.0f)
	{
		// Facing right
		facing = RIGHT;
		renderer->setFlip(SDL_FLIP_NONE);
	}
	else if (velocity.x < 0.0f)
	{
		// Facing left
		facing = LEFT;
		renderer->setFlip(SDL_FLIP_HORIZONTAL);
	}

	if (punching)
	{
		switch (level)
		{
		case 3:
		{
			renderer->setSprite(9);
			renderer->setAnimationSpeed(10.0f);
			break;
		}
		case 4:
		{
			renderer->setSprite(13);
			renderer->setAnimationSpeed(10.0f);
			break;
		}
		}
	}
	else if (airborne)
	{
		// Jumping
		switch (level)
		{
		case 1:
		{
			renderer->setSprite(2);
			renderer->setAnimationSpeed(10.0f);
			break;
		}
		case 2:
		{
			renderer->setSprite(5);
			renderer->setAnimationSpeed(10.0f);
			break;
		}
		case 3:
		{
			renderer->setSprite(8);
			renderer->setAnimationSpeed(10.0f);
			break;
		}
		case 4:
		{
			renderer->setSprite(12);
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
			case 1:
			{
				renderer->setSprite(0);
				renderer->setAnimationSpeed(5.0f);
				break;
			}
			case 2:
			{
				renderer->setSprite(3);
				renderer->setAnimationSpeed(2.0f);
				break;
			}
			case 3:
			{
				renderer->setSprite(6);
				renderer->setAnimationSpeed(2.0f);
				break;
			}
			case 4:
			{
				renderer->setSprite(10);
				renderer->setAnimationSpeed(2.0f);
				break;
			}
			}
		}
		else
		{
			// Walking
			switch (level)
			{
			case 1:
			{
				renderer->setSprite(1);
				renderer->setAnimationSpeed(10.0f);
				break;
			}
			case 2:
			{
				renderer->setSprite(4);
				renderer->setAnimationSpeed(10.0f);
				break;
			}
			case 3:
			{
				renderer->setSprite(7);
				renderer->setAnimationSpeed(10.0f);
				break;
			}
			case 4:
			{
				renderer->setSprite(11);
				renderer->setAnimationSpeed(10.0f);
				break;
			}
			}
		}
	}
}

void PlayerState::levelUp(const int& _level)
{
	switch (_level)
	{
	case 2:
	{
		level = 2;
		size = { 20.0f, 20.0f };
		moveSpeed = 80.0f;
		jumpHeight = -200.0f;
		break;
	}
	case 3:
	{
		level = 3;
		size = { 36.0f, 20.0f };
		punchEnabled = true;
		break;
	}
	case 4:
	{
		level = 4;
		size = { 36.0f, 40.0f };
		renderer->setRenderOffset({ 0.0f, -26.0f });
		moveSpeed = 120.0f;
		doubleJumpEnabled = true;
		break;
	}
	}

	updateSprite();
}

void PlayerState::setRenderer(const std::shared_ptr<SpriteRenderer>& _renderer)
{
	renderer = _renderer;
	renderer->setRenderOffset({ 0.0f, -10.0f });
}

void PlayerState::onStart()
{
	level = 1;

	size = { 16.0f, 16.0f };
	moveSpeed = 50.0f;
	jumpHeight = -120.0f;
	gravity = 200.0f;
	velocity = { 0.0f, 0.0f };
	facing = RIGHT;
	airborne = true;
	punchEnabled = false;
	punching = false;
	doubleJumpEnabled = false;
	doubleJumpUsed = false;

	updateSprite();
}
