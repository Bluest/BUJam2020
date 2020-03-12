#include "Engine.h"

class PlayerMovement : public Component
{
public:
	void setRenderer(std::shared_ptr<SpriteRenderer> _renderer);

private:
	void onStart();
	void onUpdate();

	void jump();
	void updateSprite();

	std::shared_ptr<Input> input;
	std::shared_ptr<SpriteRenderer> renderer;

	SDL_FPoint velocity;
	bool airborne;
};
