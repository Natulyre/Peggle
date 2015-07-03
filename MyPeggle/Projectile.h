#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"

class Projectile :
	public Sprite
{
public:
	Projectile();
	~Projectile();

	void Update();
};

