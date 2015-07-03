#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"

class Cannon :
	public Sprite
{
public:
	Cannon();
	~Cannon();

	void Update();
};

