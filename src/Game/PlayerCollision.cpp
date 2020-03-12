#include "PlayerCollision.h"
#include "Map.h"

void PlayerCollision::onStart()
{
	m_tileHeight = m_map->tileSize;
	m_tileWidth = m_map->tileSize;

	m_playerWidth = 20;
	m_playerHeight = 20;

	m_mapWidth = m_map->width * m_tileWidth;
	m_mapHeight = m_map->height * m_tileHeight;
}

void PlayerCollision::onUpdate()
{

}

bool PlayerCollision::CheckTilemapCollision()
{
	int playerLeft = getEntity()->transform.position.x - (m_playerWidth / 2);
	int playerRight = getEntity()->transform.position.x + (m_playerWidth / 2);
	int playerTop = getEntity()->transform.position.y - (m_playerHeight / 2);
	int playerBottom = getEntity()->transform.position.y + (m_playerHeight / 2);

	int left_tile = playerLeft / m_tileWidth;
	int right_tile = playerRight / m_tileWidth;
	int top_tile = playerTop / m_tileHeight;
	int bottom_tile = playerBottom / m_tileHeight;

	if (left_tile < 0) left_tile = 0;
	if (right_tile >= m_map->width) right_tile = m_map->width - 1;
	if (top_tile < 0) top_tile = 0;
	if (bottom_tile >= m_map->height) bottom_tile = m_map->height - 1;

	bool any_collision = false;

	for (int i = left_tile; i <= right_tile; i++)
	{
		for (int j = top_tile; j <= bottom_tile; j++)
		{
			Tile t = m_map->GetTile(i, j);
			if (t.solid == true)
			{
				any_collision = true;
			}
		}
	}
	return any_collision;
}

void PlayerCollision::UpdateCollisionBox(int _w, int _h)
{
	m_playerWidth = _w;
	m_playerHeight = _h;
}