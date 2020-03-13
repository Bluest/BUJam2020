#include "BackgroundRenderer.h"
#include "BlobCollector.h"
#include "BlobParticle.h"
#include "BlobUI.h"
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

	// Blobs
	std::vector<SDL_Point> blobCoordinates;
	{
		blobCoordinates.push_back({ 3, 34 });
		blobCoordinates.push_back({ 4, 34 });
		blobCoordinates.push_back({ 5, 33 });
		blobCoordinates.push_back({ 6, 33 });
		blobCoordinates.push_back({ 8, 34 });
		blobCoordinates.push_back({ 9, 34 });
		blobCoordinates.push_back({ 2, 37 });
		blobCoordinates.push_back({ 3, 37 });
		blobCoordinates.push_back({ 1, 38 });
		blobCoordinates.push_back({ 2, 38 });
		blobCoordinates.push_back({ 3, 38 });
		blobCoordinates.push_back({ 4, 38 });
		blobCoordinates.push_back({ 8, 39 });
		blobCoordinates.push_back({ 11, 39 });
		blobCoordinates.push_back({ 11, 38 });
		blobCoordinates.push_back({ 11, 37 });
		blobCoordinates.push_back({ 11, 36 });
		blobCoordinates.push_back({ 15, 39 });
		blobCoordinates.push_back({ 21, 39 });
		blobCoordinates.push_back({ 22, 39 });
		blobCoordinates.push_back({ 23, 39 });
		blobCoordinates.push_back({ 24, 39 });
	}
	
	std::list<std::shared_ptr<Entity>> blobs;
	for (size_t i = 0; i < blobCoordinates.size(); ++i)
	{
		std::shared_ptr<Entity> blob = core->addEntity(3);
		SDL_FPoint blobPosition;
		blobPosition.x = float(blobCoordinates[i].x * map->tileSize + map->tileSize / 2);
		blobPosition.y = float(blobCoordinates[i].y * map->tileSize + map->tileSize / 2);
		blob->transform.position = blobPosition;

		std::shared_ptr<SpriteRenderer> blobSprite = blob->addComponent<SpriteRenderer>();
		blobSprite->addSprite(sprites->use("collectable_blob"));
		blobSprite->setSprite(0);
		blobSprite->setAnimationSpeed(5.0f);
		blob->addComponent<BlobParticle>();

		blobs.push_back(blob);
	}

	// Blob UI
	std::shared_ptr<Entity> ui = core->addEntity(5);
	std::shared_ptr<BlobUI> blobBar = ui->addComponent<BlobUI>();
	blobBar->setSprite(sprites->use("blob_ui"));

	// Player
	std::shared_ptr<Entity> player = core->addEntity(2);
	player->transform.position.x = 70.0f;
	player->transform.position.y = 1100.0f;

	std::shared_ptr<SpriteRenderer> spriteRenderer = player->addComponent<SpriteRenderer>();
	{
		spriteRenderer->addSprite(sprites->use("player_idle1"));
		spriteRenderer->addSprite(sprites->use("player_walk1"));
		spriteRenderer->addSprite(sprites->use("player_jump1"));
		spriteRenderer->addSprite(sprites->use("player_idle2"));
		spriteRenderer->addSprite(sprites->use("player_walk2"));
		spriteRenderer->addSprite(sprites->use("player_jump2"));
		spriteRenderer->addSprite(sprites->use("player_idle3"));
		spriteRenderer->addSprite(sprites->use("player_walk3"));
		spriteRenderer->addSprite(sprites->use("player_jump3"));
		spriteRenderer->addSprite(sprites->use("player_punch3"));
	}

	std::shared_ptr<PlayerMovement> playerMovement = player->addComponent<PlayerMovement>();

	std::shared_ptr<PlayerState> playerState = player->addComponent<PlayerState>();
	playerState->setRenderer(spriteRenderer);
	playerMovement->setPlayerState(playerState);

	std::shared_ptr<PlayerCollision> playerCollision = player->addComponent<PlayerCollision>();
	playerCollision->setMap(map);
	playerCollision->setPlayerState(playerState);
	playerMovement->setCollider(playerCollision);

	std::shared_ptr<BlobCollector> collector = player->addComponent<BlobCollector>();
	collector->setPlayer(playerState);
	collector->setCollectables(blobs);
	blobBar->setCollector(collector);

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
	sprites->load("player_idle3", "../sprites/player_idle3.png", 2);
	sprites->load("player_walk3", "../sprites/player_walk3.png", 10);
	sprites->load("player_jump3", "../sprites/player_jump3.png", 20);
	sprites->load("player_punch3", "../sprites/player_punch3.png", 10);
	sprites->load("tileset", "../sprites/tileset.png", 1);
	sprites->load("background", "../sprites/background_cropped.png", 1);
	sprites->load("blob_ui", "../sprites/growth_bar.png", 1);
	sprites->load("collectable_blob", "../sprites/collectable_blob.png", 8);
	sprites->load("enemy1", "../sprites/Kurbeh.png", 10);
}

void Game::Run()
{
	core->run();
}
