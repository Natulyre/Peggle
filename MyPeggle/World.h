#pragma once

#include "ResourceIDs.h"
#include "Component.h"
#include "Colorable.h"
#include "Cannon.h"
#include "Peg.h"
#include "Note.h"
#include "Eyes.h"
#include "Basket.h"
#include "Utils.h"
#include "Star.h"

const int NB_STUFF = 15;

class World:
	public Component
{
public:
	World();
	~World();

	void Update();
	void ResetLevel();
	void ResetWorld();
	void SetActive(bool toggle);
	bool GetIsGameOver()	{ return isGameOver; }
	static Note* mNotes[NB_STUFF];

private:
	Basket* mBasket;
	Eyes* mEyes;
	Cannon* mCannon;
	Peg* mPegs[NB_STUFF];
	std::vector<Star*> mStars;
	Sprite* mBackground;
	Sprite* mBallIndicator;
	bool isGameOver;
	bool fanfareOver;
	float mTimer;
	int currentNote;
};

