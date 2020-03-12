#include "Engine.h"

class Map;

class PlayerCollision : public Component
{
public:
	void leftCollision();
	void rightCollision();
	void upCollision();
	void downCollision();

	void updateCollisionBoxSize(const float& _w, const float& _h);
	void setMap(const std::shared_ptr<Map>& _map);

private:
	void onStart();

	void updatePlayerBox();
	void updateEntityPosition();

	std::shared_ptr<Map> m_map;
	int tileSize;

	SDL_FRect playerBox;
	int leftX;
	int rightX;
	int topY;
	int bottomY;
};
