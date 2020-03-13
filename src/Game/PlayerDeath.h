#include "Engine.h"

class PlayerState;

class PlayerDeath : public Component
{
public:
	void setPlayer(const std::shared_ptr<PlayerState>& _player);
	void setHazards(const std::list<SDL_Point>& _hazards);

private:
	void onUpdate();

	std::shared_ptr<PlayerState> player;

	SDL_FPoint respawnPosition;
	SDL_Rect collider;
	std::list<SDL_Point> hazards;
};
