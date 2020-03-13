#include "PlayerPunch.h"
#include "PlayerState.h"

void PlayerPunch::setPlayerState(const std::shared_ptr<PlayerState>& _playerState)
{
	playerState = _playerState;
}

void PlayerPunch::onStart()
{
	input = getCore()->getInput();
}

void PlayerPunch::onUpdate()
{
	if (playerState->punchEnabled)
	{
		if (input->keyPress(SDLK_j))
		{
			if (!playerState->airborne && !playerState->punching)
			{
				playerState->velocity.x = 0.0f;
				playerState->punching = true;
				playerState->updateSprite();

				timer = duration;
			}
		}
	}

	if (playerState->punching)
	{
		timer -= getCore()->getDeltaTime();

		if (timer < 0.0f)
		{
			playerState->punching = false;
			playerState->updateSprite();
		}
	}
}
