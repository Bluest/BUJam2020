#include "PlayerCollision.h"
#include "Map.h"

void PlayerCollision::CheckTilemapCollision()
{
	playerBox.x = getEntity()->transform.position.x - playerBox.w / 2;
	playerBox.y = getEntity()->transform.position.y - playerBox.h / 2;

	upCollision();
	downCollision();
	leftCollision();
	rightCollision();

	getEntity()->transform.position.x = playerBox.x + playerBox.w / 2;
	getEntity()->transform.position.y = playerBox.y + playerBox.h / 2;
}

void PlayerCollision::UpdateCollisionBoxSize(int _w, int _h)
{
	playerBox.w = _w;
	playerBox.h = _h;
}

void PlayerCollision::onStart()
{
	playerBox.w = 0.6f;
	playerBox.h = 0.6f;
}

void PlayerCollision::leftCollision()
{
	//int left_tile = playerLeft / m_tileWidth;
	//int right_tile = playerRight / m_tileWidth;
	//int top_tile = playerTop / m_tileHeight;
	//int bottom_tile = playerBottom / m_tileHeight;
	//
	//if (left_tile < 0) left_tile = 0;
	//if (right_tile >= m_map->width) right_tile = m_map->width - 1;
	//if (top_tile < 0) top_tile = 0;
	//if (bottom_tile >= m_map->height) bottom_tile = m_map->height - 1;
	
	// Top left tile
	Tile topLeft = m_map->GetTile(int(playerBox.x), int(playerBox.y));

	if (topLeft.solid)
	{
		//getEntity()->transform.position.x = 
	}

	// Bottom left tile
	if (m_map->GetTile(playerBox.x, playerBox.y + playerBox.h).solid)
	{
		
	}

	//bool any_collision = false;
	//
	//for (int i = left_tile; i <= right_tile; i++)
	//{
	//	for (int j = top_tile; j <= bottom_tile; j++)
	//	{
	//		Tile t = m_map->GetTile(i, j);
	//		if (t.solid == true)
	//		{
	//			any_collision = true;
	//		}
	//	}
	//}
	//
	//return any_collision;
}

void PlayerCollision::rightCollision()
{

	if (m_map->GetTile(playerBox.x, playerBox.y).solid)
	{
		
	}

	if (m_map->GetTile(playerBox.x, playerBox.y + playerBox.h).solid)
	{
		
	}
}

void PlayerCollision::upCollision()
{

}

void PlayerCollision::downCollision()
{

}
