#include "Game.h"
#include "Map.h"
#include "PlayerMovement.h"
#include "Patrol.h"
#include "PlayerCollision.h"

Game::Game()
{
	core = Core::init(960, 440, 2, 60.0f);
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
	sprites->load("yellow_block", "../sprites/yellow_block.png", 1);

	std::shared_ptr<Entity> player = core->addEntity(0);
	player->transform.position.x = 25.0f;
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


	/* init enemy */
	std::shared_ptr<Entity> enemy = core->addEntity(0);
	enemy->transform.position.x = 225.0f;
	enemy->transform.position.y = 50.0f;
	enemy->transform.scale.x = 10.0f;
	enemy->transform.scale.y = 10.0f;

	std::shared_ptr<SpriteRenderer> test = enemy->addComponent<SpriteRenderer>();
	test->addSprite(sprites->use("player_walk"));
	test->setSprite(0);
	test->setAnimationSpeed(5.0f);

	std::shared_ptr<Patrol> patrol = enemy->addComponent<Patrol>();
	patrol->setRenderer(spriteRenderer);
	patrol->setMovementSpeed(10.0f);
	patrol->setEnd(300.0f);

	std::shared_ptr<PlayerCollision> collision = player->addComponent<PlayerCollision>();
	collision->SetMap(map);
}

void Game::Run()
{
	core->run();
}
