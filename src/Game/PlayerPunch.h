#include "Engine.h"

class Map;
class PlayerState;

class PlayerPunch : public Component
{
public:
	void setPlayerState(const std::shared_ptr<PlayerState>& _playerState);
	void setMap(const std::shared_ptr<Map>& _map);

private:
	void onStart();
	void onUpdate();

	std::shared_ptr<Input> input;
	std::shared_ptr<PlayerState> playerState;
	std::shared_ptr<Map> map;

	const float duration = 0.9f;
	float timer;
};
