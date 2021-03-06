#include <list>
#include <memory>

#include "SDL_rect.h"

class Component;
class Core;
struct SDL_Renderer;

struct Transform
{
	SDL_FPoint position = { 0.0f, 0.0f };
	float rotation = 0.0f;
	SDL_FPoint scale = { 1.0f, 1.0f };
};

class Entity
{
	friend class Core;

public:
	Transform transform;

	template <typename T>
	std::shared_ptr<T> addComponent()
	{
		std::shared_ptr<T> component = std::make_shared<T>();
		component->entity = self;
		components.push_back(component);

		return component;
	}

	template <class T>
	std::shared_ptr<T> getComponent()
	{
		std::shared_ptr<T> component;

		for (auto it = components.begin(); it != components.end(); ++it)
		{
			component = std::dynamic_pointer_cast<T>(*it);
			if (component)
			{
				return component;
			}
		}

		return nullptr;
	}

	std::shared_ptr<Core> getCore();

private:
	void start();
	void update();
	void draw(SDL_Renderer* _renderer);

	std::weak_ptr<Entity> self;
	std::weak_ptr<Core> core;
	std::list<std::shared_ptr<Component>> components;
};
