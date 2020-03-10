#include "Component.h"

struct SDL_FRect;
struct SDL_Renderer;
struct Sprite;

class SpriteRenderer : public Component
{
public:
	void setSprite(const std::shared_ptr<Sprite>& _sprite);
	void setAnimationSpeed(const float& _framesPerSecond);

private:
	void onDraw(SDL_Renderer* _renderer);

	std::shared_ptr<Sprite> sprite;
	SDL_Rect frame;
	int currentFrame;
	float frameInterval;
	float timer;

	SDL_FRect renderPosition;
	SDL_FPoint renderCentre;
};
