#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"
#include "CCircle.h"
#include "Colorable.h"

class Peg :
	public Sprite, public Colorable
{
public:
	Peg();
	~Peg();

	void Update();
	void OnHit();
	void ResetToLocation(float x, float y);
	void SetActive(bool toggle);

	static int PegsAlive;
	static bool hasWon;

private:
	void UpdateColor();
	CCircle* mCollider;
};

