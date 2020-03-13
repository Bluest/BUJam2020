#include "Engine.h"

class BlobCollector;

class BlobUI : public Component
{
public:
	void setCollector(const std::shared_ptr<BlobCollector>& _collector);
	void setSprite(const std::shared_ptr<Sprite>& _sprite);

private:
	void onDraw(SDL_Renderer* _renderer);

	std::shared_ptr<BlobCollector> collector;

	std::shared_ptr<Sprite> sprite;
	SDL_Rect renderPosition;
	SDL_FRect bar;
	SDL_FRect barShadow;
	float barLength;
};
