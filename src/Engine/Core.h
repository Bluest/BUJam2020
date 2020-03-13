#include <list>
#include <memory>
#include <vector>

#include "SDL.h"

class Camera;
class Entity;
class Input;
class Time;

class Core
{
public:
	static std::shared_ptr<Core> init(const int& _winW, const int& _winH, const int& _scale, const float& _fpsCap);
	~Core();

	std::shared_ptr<Entity> addEntity(const unsigned int& _layer);
	void run();

	std::shared_ptr<Camera> getCamera();
	float getDeltaTime();
	std::shared_ptr<Input> getInput();
	SDL_Renderer* getRenderer();

private:
	void start();
	void update();
	void draw();

	SDL_Window* window;
	SDL_Renderer* renderer;

	std::weak_ptr<Core> self;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Input> input;
	std::unique_ptr<Time> time;

	std::vector<std::list<std::shared_ptr<Entity>>> layers;
};
