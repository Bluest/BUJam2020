#include "Engine.h"

class Spin : public Component
{
private:
    void onUpdate()
    {
        getEntity()->transform.rotation += 360.0f * getCore()->getDeltaTime();
    }
};

int main(int argc, char* argv[])
{
    std::shared_ptr<Core> core = Core::init(500, 500, 60.0f);
    SpriteManager sprites(core->getRenderer());
    sprites.load("test", "../assets/squib.png", 1);

    std::shared_ptr<Entity> testEntity = core->addEntity();
    testEntity->transform.position.x = 250.0f;
    testEntity->transform.position.y = 250.0f;
    testEntity->transform.scale.x = 100.0f;
    testEntity->transform.scale.y = 100.0f;

    std::shared_ptr<Spin> spinner = testEntity->addComponent<Spin>();
    std::shared_ptr<SpriteRenderer> spriteRenderer = testEntity->addComponent<SpriteRenderer>();
    spriteRenderer->setSprite(sprites.use("test"));

    core->run();
    
    return 0;
}
