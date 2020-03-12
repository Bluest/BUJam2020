#include "Engine.h"

class PlayerState;
class PlayerCollision;

class PlayerMovement : public Component
{
public:
	void setPlayerState(const std::shared_ptr<PlayerState>& _playerState);
	void setCollider(const std::shared_ptr<PlayerCollision>& _collider);

private:
	void onStart();
	void onUpdate();

	void jump();

	std::shared_ptr<Input> input;
	std::shared_ptr<PlayerState> playerState;
	std::shared_ptr<PlayerCollision> collider;
};
