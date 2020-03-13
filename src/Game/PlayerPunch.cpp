#include "Map.h"
#include "PlayerPunch.h"
#include "PlayerState.h"

void PlayerPunch::setPlayerState(const std::shared_ptr<PlayerState>& _playerState)
{
	playerState = _playerState;
}

void PlayerPunch::setMap(const std::shared_ptr<Map>& _map)
{
	map = _map;
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
			if (playerState->facing == PlayerState::RIGHT)
			{
				SDL_Point target;
				target.x = int((getEntity()->transform.position.x + map->tileSize) / map->tileSize);
				target.y = int(getEntity()->transform.position.y / map->tileSize);

				// Level 3
				if (map->GetTile(target.x, target.y).type == Tile::blockType::BREAKABLE)
				{
					map->clearTile(target.x, target.y);
				}

				// Level 4
				if (playerState->doubleJumpEnabled)
				{
					if (map->GetTile(target.x, target.y - 1).type == Tile::blockType::BREAKABLE)
					{
						map->clearTile(target.x, target.y - 1);
					}
				}
			}
			else
			{
				SDL_Point target;
				target.x = int((getEntity()->transform.position.x - map->tileSize) / map->tileSize);
				target.y = int(getEntity()->transform.position.y / map->tileSize);

				// Level 3
				if (map->GetTile(target.x, target.y).type == Tile::blockType::BREAKABLE)
				{
					map->clearTile(target.x, target.y);
				}

				// Level 4
				if (playerState->doubleJumpEnabled)
				{
					if (map->GetTile(target.x, target.y - 1).type == Tile::blockType::BREAKABLE)
					{
						map->clearTile(target.x, target.y - 1);
					}
				}
			}

			playerState->punching = false;
			playerState->updateSprite();
		}
	}
}
