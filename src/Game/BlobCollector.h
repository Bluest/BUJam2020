#include "Engine.h"

class PlayerState;

class BlobCollector : public Component
{
public:
	void setPlayer(const std::shared_ptr<PlayerState>& _player);

private:
	void onUpdate();

	std::shared_ptr<PlayerState> player;

	//std::list blobs
};
