#include "Engine.h"

class Map;
class PlayerState;

class PlayerCollision : public Component
{
public:
	void leftCollision();
	void rightCollision();
	void upCollision();
	void downCollision();

	void updateCollisionBoxSize(const float& _w, const float& _h);
	void setPlayerState(const std::shared_ptr<PlayerState>& _playerState);
	void setMap(const std::shared_ptr<Map>& _map);

private:
	void onStart();

	void updatePlayerBox();
	void updateEntityPosition();

	std::shared_ptr<PlayerState> playerState;
	std::shared_ptr<Map> m_map;
	int tileSize;

	SDL_FRect playerBox;
	int leftX;
	int rightX;
	int topY;
	int bottomY;
};
