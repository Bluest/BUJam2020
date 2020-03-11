#include "Engine.h"

class Map;

class PlayerCollision : public Component
{
private:

	std::shared_ptr<Map> m_map;

	void onStart();
	void onUpdate();

	int m_mapWidth;
	int m_mapHeight;

	int m_tileWidth;
	int m_tileHeight;

	int m_playerWidth;
	int m_playerHeight;

public:
	void UpdateCollisionBox(int _w, int _h);

};
