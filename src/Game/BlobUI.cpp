#include "BlobCollector.h"
#include "BlobUI.h"

void BlobUI::setCollector(const std::shared_ptr<BlobCollector>& _collector)
{
	collector = _collector;
}

void BlobUI::setSprite(const std::shared_ptr<Sprite>& _sprite)
{
	sprite = _sprite;
	renderPosition = { 2, 2, sprite->width, sprite->height };
	bar = { 40.0f, 11.0f, 0.0f, 22.0f };
	barLength = 0.0f;
}

void BlobUI::onDraw(SDL_Renderer* _renderer)
{
	SDL_RenderCopy(_renderer, sprite->texture, nullptr, &renderPosition);

	barLength = 114.0f * float(collector->blobsCollected) / 18.0f;
	bar.w = barLength;

	SDL_SetRenderDrawColor(_renderer, 160, 64, 255, 255);
	SDL_RenderFillRectF(_renderer, &bar);
}
