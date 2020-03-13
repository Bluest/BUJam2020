#include "BlobCollector.h"
#include "PlayerState.h"

void BlobCollector::setPlayer(const std::shared_ptr<PlayerState>& _player)
{
	player = _player;
}

void BlobCollector::setCollectables(const std::list<std::shared_ptr<Entity>>& _blobs)
{
	blobs = _blobs;
	blobsCollected = 0;
}

void BlobCollector::onUpdate()
{
	box.x = int(getEntity()->transform.position.x - player->size.x / 2);
	box.y = int(getEntity()->transform.position.y - player->size.y);
	box.w = int(player->size.x);
	box.h = int(player->size.y);

	for (auto it = blobs.begin(); it != blobs.end(); ++it)
	{
		blobPosition.x = int((*it)->transform.position.x);
		blobPosition.y = int((*it)->transform.position.y);

		if (SDL_PointInRect(&blobPosition, &box))
		{
			(*it)->transform.position.y = -100.0f;
			if (++blobsCollected == 18)
			{
				player->levelUp(2);
			}
		}
	}
}
