#include "BackgroundRenderer.h"
#include "BlobCollector.h"
#include "BlobParticle.h"
#include "BlobUI.h"
#include "Game.h"
#include "Map.h"
#include "Patrol.h"
#include "PlayerCollision.h"
#include "PlayerDeath.h"
#include "PlayerMovement.h"
#include "PlayerPunch.h"
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
		blobCoordinates.push_back({ 28, 37 });
		blobCoordinates.push_back({ 29, 37 });
		blobCoordinates.push_back({ 35, 35 });
		blobCoordinates.push_back({ 36, 35 });
		blobCoordinates.push_back({ 40, 32 });
		blobCoordinates.push_back({ 41, 32 });
		blobCoordinates.push_back({ 40, 33 });
		blobCoordinates.push_back({ 41, 33 });
		blobCoordinates.push_back({ 26, 32 });
		blobCoordinates.push_back({ 26, 33 });
		blobCoordinates.push_back({ 15, 34 });
		blobCoordinates.push_back({ 16, 34 });
		blobCoordinates.push_back({ 10, 30 });
		blobCoordinates.push_back({ 8, 28 });
		blobCoordinates.push_back({ 11, 26 });
		blobCoordinates.push_back({ 12, 26 });
		blobCoordinates.push_back({ 8, 23 });
		blobCoordinates.push_back({ 1, 29 });
		blobCoordinates.push_back({ 2, 29 });
		blobCoordinates.push_back({ 3, 29 });
		blobCoordinates.push_back({ 17, 27 });
		blobCoordinates.push_back({ 20, 27 });
		blobCoordinates.push_back({ 24, 25 });
		blobCoordinates.push_back({ 29, 27 });
		blobCoordinates.push_back({ 30, 27 });
		blobCoordinates.push_back({ 31, 27 });
		blobCoordinates.push_back({ 32, 27 });
		blobCoordinates.push_back({ 35, 29 });
		blobCoordinates.push_back({ 36, 29 });
		blobCoordinates.push_back({ 39, 24 });
		blobCoordinates.push_back({ 40, 24 });
		blobCoordinates.push_back({ 31, 23 });
		blobCoordinates.push_back({ 40, 18 });
		blobCoordinates.push_back({ 40, 19 });
		blobCoordinates.push_back({ 41, 15 });
		blobCoordinates.push_back({ 37, 13 });
		blobCoordinates.push_back({ 34, 12 });
		blobCoordinates.push_back({ 41, 10 });
		blobCoordinates.push_back({ 28, 11 });
		blobCoordinates.push_back({ 28, 12 });
		blobCoordinates.push_back({ 28, 16 });
		blobCoordinates.push_back({ 21, 18 });
		blobCoordinates.push_back({ 16, 16 });
		blobCoordinates.push_back({ 15, 16 });
		blobCoordinates.push_back({ 11, 18 });
		blobCoordinates.push_back({ 12, 18 });
		blobCoordinates.push_back({ 13, 18 });
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

	// UI
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
		spriteRenderer->addSprite(sprites->use("player_idle4"));
		spriteRenderer->addSprite(sprites->use("player_walk4"));
		spriteRenderer->addSprite(sprites->use("player_jump4"));
		spriteRenderer->addSprite(sprites->use("player_punch4"));
	}

	std::shared_ptr<PlayerMovement> playerMovement = player->addComponent<PlayerMovement>();
	std::shared_ptr<PlayerPunch> playerPunch = player->addComponent<PlayerPunch>();
	playerPunch->setMap(map);

	std::shared_ptr<PlayerState> playerState = player->addComponent<PlayerState>();
	playerState->setRenderer(spriteRenderer);
	playerMovement->setPlayerState(playerState);
	playerPunch->setPlayerState(playerState);

	std::shared_ptr<PlayerCollision> playerCollision = player->addComponent<PlayerCollision>();
	playerCollision->setMap(map);
	playerCollision->setPlayerState(playerState);

	std::shared_ptr<BlobCollector> collector = player->addComponent<BlobCollector>();
	collector->setPlayer(playerState);
	collector->setCollectables(blobs);
	blobBar->setCollector(collector);

	std::shared_ptr<PlayerDeath> playerDeath = player->addComponent<PlayerDeath>();
	playerDeath->setPlayer(playerState);

	// Hazards
	std::list<SDL_Point> lavaPits;
	{
		lavaPits.push_back({ 1072, 1200 });
		lavaPits.push_back({ 1088, 1200 });
		lavaPits.push_back({ 1104, 1200 });
		lavaPits.push_back({ 1200, 1200 });
		lavaPits.push_back({ 1216, 1200 });
		lavaPits.push_back({ 1232, 1200 });
		lavaPits.push_back({ 496, 944 });
		lavaPits.push_back({ 512, 944 });
		lavaPits.push_back({ 528, 944 });
		lavaPits.push_back({ 592, 944 });
		lavaPits.push_back({ 608, 944 });
		lavaPits.push_back({ 624, 944 });
		lavaPits.push_back({ 688, 944 });
		lavaPits.push_back({ 704, 944 });
		lavaPits.push_back({ 720, 944 });
		lavaPits.push_back({ 624, 656 });
		lavaPits.push_back({ 640, 656 });
		lavaPits.push_back({ 656, 656 });
		lavaPits.push_back({ 720, 656 });
		lavaPits.push_back({ 736, 656 });
		lavaPits.push_back({ 752, 656 });
		lavaPits.push_back({ 768, 656 });
		lavaPits.push_back({ 784, 656 });
		lavaPits.push_back({ 800, 656 });
		lavaPits.push_back({ 816, 656 });
		lavaPits.push_back({ 832, 656 });
		lavaPits.push_back({ 848, 656 });
		lavaPits.push_back({ 80, 464 });
		lavaPits.push_back({ 96, 464 });
		lavaPits.push_back({ 112, 464 });
		lavaPits.push_back({ 128, 464 });
		lavaPits.push_back({ 144, 464 });
		lavaPits.push_back({ 160, 464 });
		lavaPits.push_back({ 176, 464 });
		lavaPits.push_back({ 192, 464 });
		lavaPits.push_back({ 208, 464 });
		lavaPits.push_back({ 592, 368 });
		lavaPits.push_back({ 608, 368 });
		lavaPits.push_back({ 624, 368 });
		lavaPits.push_back({ 640, 368 });
		lavaPits.push_back({ 656, 368 });
		lavaPits.push_back({ 672, 368 });
		lavaPits.push_back({ 688, 368 });
		lavaPits.push_back({ 752, 368 });
		lavaPits.push_back({ 768, 368 });
		lavaPits.push_back({ 784, 368 });
		lavaPits.push_back({ 800, 368 });
		lavaPits.push_back({ 816, 368 });
		lavaPits.push_back({ 832, 368 });
		lavaPits.push_back({ 848, 368 });
	}

	playerDeath->setHazards(lavaPits);
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
	sprites->load("player_punch3", "../sprites/player_punch3.png", 20);
	sprites->load("player_idle4", "../sprites/player_idle4.png", 2);
	sprites->load("player_walk4", "../sprites/player_walk4.png", 10);
	sprites->load("player_jump4", "../sprites/player_jump4.png", 20);
	sprites->load("player_punch4", "../sprites/player_punch4.png", 20);
	sprites->load("tileset", "../sprites/tileset.png", 1);
	sprites->load("background", "../sprites/background_cropped.png", 1);
	sprites->load("blob_ui", "../sprites/growth_bar.png", 1);
	sprites->load("collectable_blob", "../sprites/collectable_blob.png", 8);
}

void Game::Run()
{
	core->run();
}
