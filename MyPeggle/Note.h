#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"
#include "Colorable.h"

//Represents popped up peggles and play a song after winning
class Note :
	public Sprite, public Colorable
{
public:
	Note();
	~Note();

	void Capture(Color color);
	bool GetCaptured() { return isCaptured; }
	void Reset();
	void Sing();

private:
	void UpdateColor();
	bool isCaptured;
};

