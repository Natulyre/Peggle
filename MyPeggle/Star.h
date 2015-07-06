#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"

class Star :
	public Sprite
{
public:
	Star(float x, float y);
	~Star();

	void Update();
	void Shine();
	float mTimer;
	bool isShining;
};

