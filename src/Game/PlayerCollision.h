#include "Engine.h"

class Map;
class PlayerState;

class PlayerCollision : public Component
{
public:
	void updateCollisionBox();

	void setPlayerState(const std::shared_ptr<PlayerState>& _playerState);
	void setMap(const std::shared_ptr<Map>& _map);

private:
	void onStart();
	void onUpdate();

	void leftCollision();
	void rightCollision();
	void upCollision();
	void downCollision();
	void checkWalkoff();

	void updateBoxEdges();
	void updateEntityPosition();

	std::shared_ptr<PlayerState> playerState;
	std::shared_ptr<Map> m_map;
	int tileSize;

	float previousPosition;
	SDL_FRect playerBox;

	int leftX;
	int middleX;
	int rightX;

	int topY;
	int middleY;
	int bottomY;
};
