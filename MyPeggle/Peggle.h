#pragma once

#include "Engine.h"
#include "Component.h"
#include "World.h"

enum States
{
	Starting,
	Playing,
	GameOver
};

class Peggle :
	public Component
{
public:
	Peggle();
	~Peggle();

	void Update();

private:
	void ChangeState(States state);

	States mCurrentState;
	World* mWorld;
	Sprite* mStartingScreen;
	Sprite* mGameOverScreen;
};

