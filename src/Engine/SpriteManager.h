#include <list>
#include <memory>
#include <string>

struct SDL_Renderer;
struct Sprite;

class SpriteManager
{
public:
	SpriteManager(SDL_Renderer* _renderer);
	~SpriteManager();

	void load(const std::string& _name, const std::string& _file, const int& _frames);
	std::shared_ptr<Sprite> use(const std::string& _name);

private:
	SDL_Renderer* renderer;
	std::list<std::shared_ptr<Sprite>> sprites;
};
