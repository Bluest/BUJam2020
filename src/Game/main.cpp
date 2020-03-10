#include "Engine.h"

class Spin : public Component
{
private:
    void onUpdate()
    {
        getEntity()->transform.rotation += 0.0f * getCore()->getDeltaTime();
    }
};

class Rockets : public Component
{
private:
	void onUpdate()
	{
		getEntity()->transform.position.y += 10.0f * getCore()->getDeltaTime();
		getEntity()->transform.scale.x *= 1.005f;
		getEntity()->transform.scale.y *= 1.005f;
	}
};

int main(int argc, char* argv[])
{
    std::shared_ptr<Core> core = Core::init(500, 500, 60.0f);
    SpriteManager sprites(core->getRenderer());
    sprites.load("test", "../assets/lonk.png", 10);

    std::shared_ptr<Entity> testEntity = core->addEntity();
    testEntity->transform.position.x = 250.0f;
    testEntity->transform.position.y = 250.0f;
    testEntity->transform.scale.x = 100.0f;
    testEntity->transform.scale.y = 100.0f;

    std::shared_ptr<Spin> spinner = testEntity->addComponent<Spin>();
    std::shared_ptr<SpriteRenderer> spriteRenderer = testEntity->addComponent<SpriteRenderer>();
    spriteRenderer->setSprite(sprites.use("test"));
	spriteRenderer->setAnimationSpeed(15.0f);

	testEntity->addComponent<Rockets>();

    core->run();
    
    return 0;
}
