#include "Engine.h"

class Patrol : public Component
{
private:

	float movementSpeed;
	float startX, startY;
	float distance;

	float waypoint;
	bool movingRight;

	float yVelocity;
	bool airborne;
	bool jumpEnabled;
	bool canJump;
	
	std::shared_ptr<SpriteRenderer> renderer;

	void onStart();
	void onUpdate();

	void Move();
	void Jump();
	void RandNum();

public:

	void setRenderer(std::shared_ptr<SpriteRenderer> _renderer);
	void setMovementSpeed(float _movementSpeed);
	void enableJump(bool _jumpEnabled);

	void setEnd(float _b);

};