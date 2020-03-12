#include "Game.h"
#include "Map.h"
#include "PlayerMovement.h"

Game::Game()
{
	core = Core::init(960, 640, 2, 60.0f);
	sprites = std::make_shared<SpriteManager>(core->getRenderer());
	Init();
}

Game::Game(int _winWidth, int _winHeight, int _scale, float _fpsCap)
{
	core = Core::init(_winWidth, _winHeight, _scale, _fpsCap);
	sprites = std::make_shared<SpriteManager>(core->getRenderer());
	Init();
}

void Game::Init()
{
	/* init map */
	std::shared_ptr<Entity> level = core->addEntity(0);
	std::shared_ptr<Map> map = level->addComponent<Map>();
	map->LoadFromFile();

	/* init player */
	sprites->load("player_idle1", "../sprites/player_idle1.png", 4);
	sprites->load("player_walk1", "../sprites/player_walk1.png", 8);
	sprites->load("player_jump1", "../sprites/player_jump1.png", 20);

	std::shared_ptr<Entity> player = core->addEntity(0);
	player->transform.position.x = 125.0f;
	player->transform.position.y = 50.0f;
	player->transform.scale.x = 10.0f;
	player->transform.scale.y = 10.0f;

	std::shared_ptr<SpriteRenderer> spriteRenderer = player->addComponent<SpriteRenderer>();
	spriteRenderer->addSprite(sprites->use("player_idle1"));
	spriteRenderer->addSprite(sprites->use("player_walk1"));
	spriteRenderer->addSprite(sprites->use("player_jump1"));
	spriteRenderer->setSprite(0);
	spriteRenderer->setAnimationSpeed(5.0f);

	std::shared_ptr<PlayerMovement> playerMovement = player->addComponent<PlayerMovement>();
	playerMovement->setRenderer(spriteRenderer);
}

void Game::Run()
{
	core->run();
}
