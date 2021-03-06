#include "SDL_timer.h"

class Time
{
public:
	Time(const float& _fpsCap);

	void start();
	void tick();
	float getDelta();

private:
	float prev;
	float curr;
	float delta;
	float target;
};
