#include "BackgroundRenderer.h"

void BackgroundRenderer::setImage(const std::shared_ptr<Sprite>& _image)
{
	image = _image;
}

void BackgroundRenderer::onDraw(SDL_Renderer* _renderer)
{
	SDL_RenderCopy(_renderer, image->texture, nullptr, nullptr);
}
