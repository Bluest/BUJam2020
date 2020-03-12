#include "Engine.h"

class PlayerState : public Component
{
public:
	SDL_FPoint velocity;
	bool airborne;
	// dead
	// punching

private:
	void onStart();
};
