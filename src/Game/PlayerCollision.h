#include "Engine.h"

class Map;

class PlayerCollision : public Component
{
public:
	void CheckTilemapCollision();

	void UpdateCollisionBoxSize(int _w, int _h);
	void SetMap(std::shared_ptr<Map> _map) { m_map = _map; }

private:
	void onStart();

	void leftCollision();
	void rightCollision();
	void upCollision();
	void downCollision();

	std::shared_ptr<Map> m_map;

	SDL_FRect playerBox;
};
