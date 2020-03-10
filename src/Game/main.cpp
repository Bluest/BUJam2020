#include "Engine.h"

#include "PlayerMovement.h"

int main(int argc, char* argv[])
{
    std::shared_ptr<Core> core = Core::init(500, 500, 60.0f);
    SpriteManager sprites(core->getRenderer());
    sprites.load("player_idle", "../sprites/player_idle.png", 4);
	sprites.load("player_walk", "../sprites/player_walk.png", 4);

	std::shared_ptr<Entity> player = core->addEntity();
	player->transform.position.x = 250.0f;
	player->transform.position.y = 250.0f;
	player->transform.scale.x = 100.0f;
	player->transform.scale.y = 100.0f;

    std::shared_ptr<SpriteRenderer> spriteRenderer = player->addComponent<SpriteRenderer>();
	spriteRenderer->addSprite(sprites.use("player_idle"));
	spriteRenderer->addSprite(sprites.use("player_walk"));
	spriteRenderer->setSprite(0);
	spriteRenderer->setAnimationSpeed(5.0f);

	std::shared_ptr<PlayerMovement> playerMovement = player->addComponent<PlayerMovement>();
	playerMovement->setRenderer(spriteRenderer);

    core->run();
    
    return 0;
}
