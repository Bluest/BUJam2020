#include "Engine.h"

class Map;

class PlayerCollision : public Component
{
private:

	std::shared_ptr<Map> m_map;

	void onStart();
	void onUpdate();

public:

};
