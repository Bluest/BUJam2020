#include "BlobParticle.h"

void BlobParticle::onUpdate()
{
	getEntity()->transform.rotation += 180.0f * getCore()->getDeltaTime();
}
