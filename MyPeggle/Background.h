#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"

class Background :
	public Sprite
{
public:
	Background();
	~Background();

	void Update();
};

