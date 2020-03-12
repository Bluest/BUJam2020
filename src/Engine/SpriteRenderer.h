#include <memory>
#include <vector>

#include "SDL_render.h"

#include "Component.h"

struct Sprite;

class SpriteRenderer : public Component
{
public:
	void addSprite(const std::shared_ptr<Sprite>& _sprite);

	void setSprite(const int& _index);
	void setAnimationSpeed(const float& _framesPerSecond);
	void setFlip(const SDL_RendererFlip& _flipState);
	void setRenderOffset(const SDL_FPoint& _offset);

private:
	void onDraw(SDL_Renderer* _renderer);
	
	std::vector<std::shared_ptr<Sprite>> sprites;
	std::shared_ptr<Sprite> sprite;
	SDL_Rect frame;
	SDL_RendererFlip flip;
	int currentFrame;
	float frameInterval;
	float timer;

	SDL_FPoint renderOffset;
	SDL_FRect renderPosition;
	SDL_FPoint renderCentre;
};
