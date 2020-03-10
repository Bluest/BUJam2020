#include "SDL_render.h"

#include "Core.h"
#include "Entity.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

void SpriteRenderer::setSprite(const std::shared_ptr<Sprite>& _sprite)
{
	sprite = _sprite;
	frame = { 0, 0, sprite->width, sprite->height };
	currentFrame = 0;
	frameInterval = 1.0f;
	timer = 0.0f;
}

void SpriteRenderer::setAnimationSpeed(const float& _framesPerSecond)
{
	frameInterval = 1.0f / _framesPerSecond;
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
				SDL_FLIP_NONE);

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
				SDL_FLIP_NONE);
		}
	}
}
