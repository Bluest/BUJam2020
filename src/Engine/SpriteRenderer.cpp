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
	flip = SDL_FLIP_NONE;
	currentFrame = 0;
	frameInterval = 1.0f;
	timer = 0.0f;
}

void SpriteRenderer::setAnimationSpeed(const float& _framesPerSecond)
{
	frameInterval = 1.0f / _framesPerSecond;
}

void SpriteRenderer::setFlip(SDL_RendererFlip _flip)
{
	flip = _flip;
}

void SpriteRenderer::onDraw(SDL_Renderer* _renderer)
{
	if (sprite)
	{
		renderPosition.x = getEntity()->transform.position.x - getEntity()->transform.scale.x / 2;
		renderPosition.y = getEntity()->transform.position.y - getEntity()->transform.scale.y / 2;
		renderPosition.w = getEntity()->transform.scale.x;
		renderPosition.h = getEntity()->transform.scale.y;

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
