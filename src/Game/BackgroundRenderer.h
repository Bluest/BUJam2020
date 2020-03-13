#include "Engine.h"

class BackgroundRenderer : public Component
{
public:
	void setImage(const std::shared_ptr<Sprite>& _image);

private:
	void onDraw(SDL_Renderer* _renderer);

	std::shared_ptr<Sprite> image;
};
