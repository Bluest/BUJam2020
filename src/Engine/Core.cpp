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
	core->layers.resize(1);

	return core;
}

Core::~Core()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

std::shared_ptr<Entity> Core::addEntity(const unsigned int& _layer)
{
	if (_layer > layers.size())
	{
		layers.resize(_layer + 1);
	}

	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	entity->self = entity;
	entity->core = self;
	layers[_layer].push_back(entity);

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
	start();
	time->start();

	while (input->processInput())
	{
		update();
		draw();
		time->tick();
	}
}

void Core::start()
{
	for (size_t currentLayer = 0; currentLayer < layers.size(); ++currentLayer)
	{
		for (auto it = layers[currentLayer].begin(); it != layers[currentLayer].end(); ++it)
		{
			(*it)->start();
		}
	}
}

void Core::update()
{
	for (size_t currentLayer = 0; currentLayer < layers.size(); ++currentLayer)
	{
		for (auto it = layers[currentLayer].begin(); it != layers[currentLayer].end(); ++it)
		{
			(*it)->update();
		}
	}
}

void Core::draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (size_t currentLayer = 0; currentLayer < layers.size(); ++currentLayer)
	{
		for (auto it = layers[currentLayer].begin(); it != layers[currentLayer].end(); ++it)
		{
			(*it)->draw(renderer);
		}
	}

	SDL_RenderPresent(renderer);
}
