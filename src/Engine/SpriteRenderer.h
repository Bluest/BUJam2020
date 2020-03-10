#include "Component.h"

struct SDL_FRect;
struct SDL_Renderer;
struct Sprite;

class SpriteRenderer : public Component
{
public:
	void setSprite(const std::shared_ptr<Sprite>& _sprite);

private:
	void onDraw(SDL_Renderer* _renderer);

	std::shared_ptr<Sprite> sprite;
	SDL_FRect spritePosition;
	SDL_FPoint spriteCentre;
};
