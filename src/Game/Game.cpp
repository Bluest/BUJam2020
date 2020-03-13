#include "BackgroundRenderer.h"
#include "Game.h"
#include "Map.h"
#include "Patrol.h"
#include "PlayerCollision.h"
#include "PlayerMovement.h"
#include "PlayerState.h"

Game::Game()
{
	core = Core::init(640, 480, 2, 60.0f);
	sprites = std::make_shared<SpriteManager>(core->getRenderer());
	loadSprites();
	Init();
}

void Game::Init()
{
	// Map
	std::shared_ptr<Entity> level = core->addEntity(1);
	std::shared_ptr<Map> map = level->addComponent<Map>();
	map->LoadFromFile();
	map->setTileset(sprites->use("tileset"));

	// Background
	std::shared_ptr<Entity> background = core->addEntity(0);
	std::shared_ptr<BackgroundRenderer> bgRenderer = background->addComponent<BackgroundRenderer>();
	bgRenderer->setImage(sprites->use("background"));

	// Player
	std::shared_ptr<Entity> player = core->addEntity(2);
	player->transform.position.x = 70.0f;
	player->transform.position.y = 1100.0f;
	player->transform.scale.x = 10.0f;
	player->transform.scale.y = 10.0f;

	std::shared_ptr<SpriteRenderer> spriteRenderer = player->addComponent<SpriteRenderer>();
	spriteRenderer->addSprite(sprites->use("player_idle1"));
	spriteRenderer->addSprite(sprites->use("player_walk1"));
	spriteRenderer->addSprite(sprites->use("player_jump1"));
	spriteRenderer->addSprite(sprites->use("player_idle2"));
	spriteRenderer->addSprite(sprites->use("player_walk2"));
	spriteRenderer->addSprite(sprites->use("player_jump2"));

	std::shared_ptr<PlayerMovement> playerMovement = player->addComponent<PlayerMovement>();

	std::shared_ptr<PlayerState> playerState = player->addComponent<PlayerState>();
	playerState->setRenderer(spriteRenderer);
	playerMovement->setPlayerState(playerState);

	std::shared_ptr<PlayerCollision> playerCollision = player->addComponent<PlayerCollision>();
	playerCollision->setMap(map);
	playerCollision->setPlayerState(playerState);
	playerMovement->setCollider(playerCollision);

	// Enemy
	//std::shared_ptr<Entity> enemy = core->addEntity(2);
	//enemy->transform.position.x = 250.0f;
	//enemy->transform.position.y = 50.0f;
	//enemy->transform.scale.x = 10.0f;
	//enemy->transform.scale.y = 10.0f;
	//
	//std::shared_ptr<SpriteRenderer> test = enemy->addComponent<SpriteRenderer>();
	//test->addSprite(sprites->use("enemy1"));
	//test->setSprite(0);
	//test->setAnimationSpeed(5.0f);
	//
	//std::shared_ptr<Patrol> patrol = enemy->addComponent<Patrol>();
	//patrol->setRenderer(test);
	//patrol->setMovementSpeed(20.0f);
	//patrol->setEnd(300.0f);
}

void Game::loadSprites()
{
	sprites->load("player_idle1", "../sprites/player_idle1.png", 4);
	sprites->load("player_walk1", "../sprites/player_walk1.png", 8);
	sprites->load("player_jump1", "../sprites/player_jump1.png", 20);
	sprites->load("player_idle2", "../sprites/player_idle2.png", 2);
	sprites->load("player_walk2", "../sprites/player_walk2.png", 10);
	sprites->load("player_jump2", "../sprites/player_jump2.png", 20);
	sprites->load("tileset", "../sprites/tileset.png", 1);
	sprites->load("background", "../sprites/background_cropped.png", 1);
	sprites->load("collectable_blob", "../sprites/collectable_blob.png", 8);
	sprites->load("enemy1", "../sprites/Kurbeh.png", 10);
}

void Game::Run()
{
	core->run();
}
