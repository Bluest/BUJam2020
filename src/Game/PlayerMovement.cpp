#include "PlayerCollision.h"
#include "PlayerMovement.h"
#include "PlayerState.h"

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
}

void PlayerMovement::onUpdate()
{
	// Input
	if (input->keyPress(SDLK_a))
	{
		// Walk left
		playerState->velocity.x -= playerState->moveSpeed;
		playerState->updateSprite();
	}

	if (input->keyRelease(SDLK_a))
	{
		// Stop walking left
		playerState->velocity.x += playerState->moveSpeed;
		playerState->updateSprite();
	}

	if (input->keyPress(SDLK_d))
	{
		// Walk right
		playerState->velocity.x += playerState->moveSpeed;
		playerState->updateSprite();
	}

	if (input->keyRelease(SDLK_d))
	{
		// Stop walking right
		playerState->velocity.x -= playerState->moveSpeed;
		playerState->updateSprite();
	}

	if (!input->keyHold(SDLK_a) && !input->keyHold(SDLK_d))
	{
		playerState->velocity.x = 0.0f;
	}

	if (input->keyPress(SDLK_k))
	{
		jump();
	}

	// Gravity
	if (playerState->airborne)
	{
		playerState->velocity.y += playerState->gravity * getCore()->getDeltaTime();
	}

	// Update position
	getEntity()->transform.position.x += playerState->velocity.x * getCore()->getDeltaTime();
	getEntity()->transform.position.y += playerState->velocity.y * getCore()->getDeltaTime();

	getCore()->getCamera()->setPosition(getEntity()->transform.position);
}

void PlayerMovement::jump()
{
	if (!playerState->airborne)
	{
		playerState->velocity.y = playerState->jumpHeight;
		playerState->airborne = true;
		playerState->updateSprite();
	}
}
