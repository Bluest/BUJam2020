#include "PlayerCollision.h"
#include "PlayerState.h"
#include "Map.h"

void PlayerCollision::updateCollisionBox()
{
	playerBox.w = playerState->size.x;
	playerBox.h = playerState->size.y;
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
	updateBoxEdges();

	if (m_map->GetTile(leftX, topY).solid ||
		m_map->GetTile(leftX, bottomY).solid ||
		m_map->GetTile(leftX, middleY).solid)
	{
		playerBox.x = previousPosition;
	}
}

void PlayerCollision::rightCollision()
{
	updateBoxEdges();
	
	if (m_map->GetTile(rightX, topY).solid ||
		m_map->GetTile(rightX, bottomY).solid ||
		m_map->GetTile(rightX, middleY).solid)
	{
		playerBox.x = previousPosition;
	}
}

void PlayerCollision::upCollision()
{
	updateBoxEdges();

	if (m_map->GetTile(leftX, topY).solid ||
		m_map->GetTile(rightX, topY).solid ||
		m_map->GetTile(middleX, topY).solid)
	{
		playerBox.y = float(topY * tileSize + tileSize);
		playerState->velocity.y = 0.0f;
	}
}

void PlayerCollision::downCollision()
{
	updateBoxEdges();

	if (m_map->GetTile(leftX, bottomY).solid ||
		m_map->GetTile(rightX, bottomY).solid ||
		m_map->GetTile(middleX, bottomY).solid)
	{
		playerBox.y = float(bottomY * tileSize - (playerBox.h + 1));
		playerState->airborne = false;
		playerState->doubleJumpUsed = false;
		playerState->velocity.y = 0.0f;
		playerState->updateSprite();
	}
}

void PlayerCollision::checkWalkoff()
{
	updateBoxEdges();

	if (!m_map->GetTile(leftX, bottomY + 1).solid &&
		!m_map->GetTile(rightX, bottomY + 1).solid &&
		!m_map->GetTile(middleX, bottomY + 1).solid)
	{
		playerState->airborne = true;
		playerState->updateSprite();
	}
}

void PlayerCollision::onStart()
{
	updateCollisionBox();

	previousPosition = getEntity()->transform.position.x - playerBox.w / 2;
}

void PlayerCollision::onUpdate()
{
	updateCollisionBox();

	playerBox.x = getEntity()->transform.position.x - playerBox.w / 2;
	playerBox.y = getEntity()->transform.position.y - playerBox.h;

	leftCollision();
	rightCollision();
	upCollision();

	if (!playerState->airborne)
	{
		checkWalkoff();
	}

	if (playerState->airborne)
	{
		downCollision();
	}

	updateEntityPosition();
}

void PlayerCollision::updateBoxEdges()
{
	leftX = int(playerBox.x / tileSize);
	rightX = int((playerBox.x + playerBox.w) / tileSize);
	middleX = int(float(leftX + rightX) / 2);

	topY = int(playerBox.y / tileSize);
	bottomY = int((playerBox.y + playerBox.h) / tileSize);
	middleY = int(float(topY + bottomY) / 2);
}

void PlayerCollision::updateEntityPosition()
{
	getEntity()->transform.position.x = playerBox.x + playerBox.w / 2;
	getEntity()->transform.position.y = playerBox.y + playerBox.h;

	previousPosition = playerBox.x;
}
