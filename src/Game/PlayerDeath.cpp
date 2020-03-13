#include "PlayerDeath.h"
#include "PlayerState.h"

void PlayerDeath::setPlayer(const std::shared_ptr<PlayerState>& _player)
{
	player = _player;
	respawnPosition = { 70.0f, 1200.0f };
}

void PlayerDeath::setHazards(const std::list<SDL_Point>& _hazards)
{
	hazards = _hazards;
}

void PlayerDeath::onUpdate()
{
	collider.x = int(getEntity()->transform.position.x - player->size.x / 2);
	collider.y = int(getEntity()->transform.position.y - player->size.y);
	collider.w = int(player->size.x);
	collider.h = int(player->size.y);

	for (auto it = hazards.begin(); it != hazards.end(); ++it)
	{
		if (SDL_PointInRect(&(*it), &collider))
		{
			getEntity()->transform.position = respawnPosition;
			player->airborne = true;
			getCore()->getCamera()->setPosition(getEntity()->transform.position);
		}
	}
}
