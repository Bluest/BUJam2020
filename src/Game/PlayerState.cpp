#include "PlayerState.h"

void PlayerState::onStart()
{
	velocity = { 0.0f, 0.0f };
	airborne = true;
}
