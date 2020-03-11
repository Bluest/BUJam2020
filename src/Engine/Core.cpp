#include "Core.h"
#include "Entity.h"
#include "Input.h"
#include "Time.h"

std::shared_ptr<Core> Core::init(const int& _winW, const int& _winH, const int& _scale, const float& _fpsCap)
{
	std::shared_ptr<Core> core = std::make_shared<Core>();

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(_winW, _winH, 0, &core->window, &core->renderer);
	SDL_RenderSetLogicalSize(core->renderer, _winW / _scale, _winH / _scale);

	core->self = core;
	core->input = std::make_shared<Input>();
	core->time = std::make_unique<Time>(_fpsCap);

	return core;
}

Core::~Core()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

std::shared_ptr<Entity> Core::addEntity(const int& _layer)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	entity->self = entity;
	entity->core = self;
	entities.push_back(entity);

	return entity;
}

float Core::getDeltaTime()
{
	return time->getDelta();
}

std::shared_ptr<Input> Core::getInput()
{
	return input;
}

SDL_Renderer* Core::getRenderer()
{
	return renderer;
}

void Core::run()
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		(*it)->start();
	}

	time->start();

	while (input->processInput())
	{
		for (auto it = entities.begin(); it != entities.end(); ++it)
		{
			(*it)->update();
		}

		draw();

		time->tick();
	}
}

void Core::draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		(*it)->draw(renderer);
	}

	SDL_RenderPresent(renderer);
}
