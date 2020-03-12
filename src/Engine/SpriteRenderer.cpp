#include "Core.h"
#include "Entity.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

void SpriteRenderer::addSprite(const std::shared_ptr<Sprite>& _sprite)
{
	sprites.push_back(_sprite);
}

void SpriteRenderer::setSprite(const int& _index)
{
	sprite = sprites[_index];
	frame = { 0, 0, sprite->width, sprite->height };
	currentFrame = 0;
	frameInterval = 1.0f;
	timer = 0.0f;
}

void SpriteRenderer::setAnimationSpeed(const float& _framesPerSecond)
{
	frameInterval = 1.0f / _framesPerSecond;
}

void SpriteRenderer::setFlip(const SDL_RendererFlip& _flip)
{
	flip = _flip;
}

void SpriteRenderer::setRenderOffset(const SDL_FPoint& _offset)
{
	renderOffset = _offset;
}

void SpriteRenderer::onDraw(SDL_Renderer* _renderer)
{
	if (sprite)
	{
		renderPosition.x = getEntity()->transform.position.x - float(sprite->width) / 2 + renderOffset.x;
		renderPosition.y = getEntity()->transform.position.y - float(sprite->height) / 2 + renderOffset.y;
		renderPosition.w = float(sprite->width);
		renderPosition.h = float(sprite->height);

		renderCentre.x = getEntity()->transform.scale.x / 2;
		renderCentre.y = getEntity()->transform.scale.y / 2;

		if (sprite->frames > 1)
		{
			frame.x = currentFrame * sprite->width;

			SDL_RenderCopyExF(_renderer,
				sprite->texture,
				&frame,
				&renderPosition,
				getEntity()->transform.rotation,
				&renderCentre,
				flip);

			timer += getCore()->getDeltaTime();
			if (timer > frameInterval)
			{
				timer -= frameInterval;
				if (++currentFrame == sprite->frames)
				{
					currentFrame = 0;
				}
			}
		}
		else
		{
			SDL_RenderCopyExF(_renderer,
				sprite->texture,
				nullptr,
				&renderPosition,
				getEntity()->transform.rotation,
				&renderCentre,
				flip);
		}
	}
}
