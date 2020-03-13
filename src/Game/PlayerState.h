#include "Engine.h"

class PlayerState : public Component
{
public:
	void updateSprite();
	void levelUp(const int& _level);
	//void die();

	void setRenderer(const std::shared_ptr<SpriteRenderer>& _renderer);

	std::shared_ptr<SpriteRenderer> renderer;

	SDL_FPoint size;
	float moveSpeed;
	float jumpHeight;
	float gravity;
	SDL_FPoint velocity;
	bool airborne;

	// Abilities
	bool punchEnabled;
	bool punching;
	bool doubleJumpEnabled;
	bool doubleJumpUsed;

private:
	void onStart();

	int level;
};
