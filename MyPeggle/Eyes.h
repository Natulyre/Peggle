#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"

class Eyes :
	public Sprite
{
public:
	Eyes();
	~Eyes();

	void Update();
	void Blink();
	float mTimer;
	bool isBlinking;
};

