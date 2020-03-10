#include "SDL_render.h"

#include "Entity.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

void SpriteRenderer::setSprite(const std::shared_ptr<Sprite>& _sprite)
{
	sprite = _sprite;
}

void SpriteRenderer::onDraw(SDL_Renderer* _renderer)
{
	spritePosition.x = getEntity()->transform.position.x - getEntity()->transform.scale.x / 2;
	spritePosition.y = getEntity()->transform.position.y - getEntity()->transform.scale.y / 2;
	spritePosition.w = getEntity()->transform.scale.x;
	spritePosition.h = getEntity()->transform.scale.y;

	spriteCentre.x = getEntity()->transform.scale.x / 2;
	spriteCentre.y = getEntity()->transform.scale.y / 2;

	SDL_RenderCopyExF(_renderer,
		sprite->texture,
		nullptr,
		&spritePosition,
		getEntity()->transform.rotation,
		&spriteCentre,
		SDL_FLIP_NONE);
}
