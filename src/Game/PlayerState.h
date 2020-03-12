#include "Engine.h"

class PlayerState : public Component
{
public:
	void updateSprite();
	void setRenderer(const std::shared_ptr<SpriteRenderer>& _renderer);

	std::shared_ptr<SpriteRenderer> renderer;

	SDL_FPoint velocity;
	bool airborne;
	// dead
	// punching

private:
	void onStart();
};
