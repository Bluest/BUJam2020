#include "Engine.h"

class PlayerState;

class BlobCollector : public Component
{
public:
	void setPlayer(const std::shared_ptr<PlayerState>& _player);
	void setCollectables(const std::list<std::shared_ptr<Entity>>& _blobs);

	int blobsCollected;

private:
	void onUpdate();

	const int blobsTo2 = 18;
	const int blobsTo3 = 28;
	const int blobsTo4 = 40;

	std::shared_ptr<PlayerState> player;

	SDL_Rect box;
	SDL_Point blobPosition;
	std::list<std::shared_ptr<Entity>> blobs;
};