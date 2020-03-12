#include "PlayerCollision.h"
#include "PlayerState.h"
#include "Map.h"

void PlayerCollision::updateCollisionBoxSize(const float& _w, const float& _h)
{
	playerBox.w = _w;
	playerBox.h = _h;
}

void PlayerCollision::setPlayerState(const std::shared_ptr<PlayerState>& _playerState)
{
	playerState = _playerState;
}

void PlayerCollision::setMap(const std::shared_ptr<Map>& _map)
{
	m_map = _map;
	tileSize = _map->tileSize;
}

void PlayerCollision::leftCollision()
{
	updatePlayerBox();

	if (m_map->GetTile(leftX, topY).solid || m_map->GetTile(leftX, bottomY).solid)
	{
		playerBox.x = float(leftX * tileSize + tileSize);
	}

	updateEntityPosition();
}

void PlayerCollision::rightCollision()
{
	updatePlayerBox();
	
	if (m_map->GetTile(rightX, topY).solid || m_map->GetTile(rightX, bottomY).solid)
	{
		playerBox.x = float(rightX * tileSize - playerBox.w);
	}

	updateEntityPosition();
}

void PlayerCollision::upCollision()
{
	updatePlayerBox();

	if (m_map->GetTile(leftX, topY).solid || m_map->GetTile(rightX, topY).solid)
	{
		playerBox.y = float(topY * tileSize + tileSize);
	}

	updateEntityPosition();
}

void PlayerCollision::downCollision()
{
	updatePlayerBox();

	if (m_map->GetTile(leftX, bottomY).solid || m_map->GetTile(rightX, bottomY).solid)
	{
		playerBox.y = float(bottomY * tileSize - playerBox.h);
		playerState->airborne = false;
	}

	updateEntityPosition();
}

void PlayerCollision::onStart()
{
	playerBox.w = 20.0f;
	playerBox.h = 20.0f;
}

void PlayerCollision::updatePlayerBox()
{
	playerBox.x = getEntity()->transform.position.x - playerBox.w / 2;
	playerBox.y = getEntity()->transform.position.y - playerBox.h / 2;

	leftX = int(playerBox.x / tileSize);
	rightX = int((playerBox.x + playerBox.w) / tileSize);
	topY = int(playerBox.y / tileSize);
	bottomY = int((playerBox.y + playerBox.h) / tileSize);
}

void PlayerCollision::updateEntityPosition()
{
	getEntity()->transform.position.x = playerBox.x + playerBox.w / 2;
	getEntity()->transform.position.y = playerBox.y + playerBox.h / 2;
}
