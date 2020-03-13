#include "Engine.h"

class PlayerState;

class PlayerMovement : public Component
{
public:
	void setPlayerState(const std::shared_ptr<PlayerState>& _playerState);

private:
	void onStart();
	void onUpdate();

	void jump();

	std::shared_ptr<Input> input;
	std::shared_ptr<PlayerState> playerState;
};
