#include "World.h"

Note* World::mNotes[NB_STUFF];

const float SING_DELAY = 0.3f;

World::World():
mTimer(SING_DELAY)
,currentNote(0)
{
	//Just plain sprites, no need for classes
	mBackground = new Sprite(Texture::Background);
	D3DXVECTOR3 center(mBackground->GetTextureInfos()->infos.Width / 2, mBackground->GetTextureInfos()->infos.Height / 2, 0.0f);
	mBackground->SetPivot(center);
	mBackground->SetPosition(0, 0);
	mBackground->SetRotationDeg(0, 180, 0);

	//Plain sprite #2
	mBallIndicator = new Sprite(Texture::BallIndicator3);
	D3DXVECTOR3 center2(mBallIndicator->GetTextureInfos()->infos.Width / 2, mBallIndicator->GetTextureInfos()->infos.Height / 2, 0.0f);
	mBallIndicator->SetPivot(center2);
	mBallIndicator->SetPosition(340, 200);
	mBallIndicator->SetRotationDeg(0, 180, 0);

	//Manually setting a bunch of stars decorations
	mStars.push_back(new Star(-220, -200));
	mStars.push_back(new Star(-80, -210));
	mStars.push_back(new Star(80, -230));
	mStars.push_back(new Star(320, -220));
	mStars.push_back(new Star(320, -20));
	mStars.push_back(new Star(360, 80));
	mStars.push_back(new Star(-300, -20));
	mStars.push_back(new Star(-325, -220));
	mStars.push_back(new Star(-340, 90));
	mStars.push_back(new Star(-360, 180));

	//Our world's components
	mBasket = new Basket();
	mEyes = new Eyes();
	mCannon = new Cannon();
	for (int i = 0; i < NB_STUFF; i++)
	{
		mNotes[i] = new Note();
		//Set the notes initial positions, they'll be revealed in order when captured
		mNotes[i]->SetPosition(-160-i*16, 260);
		mPegs[i] = new Peg();
	}

}

World::~World()
{
}

//Reset the whole world
void World::ResetWorld()
{
	mTimer = SING_DELAY;
	isGameOver = false;
	mCannon->Reset();
	ResetLevel();
}

//Set every components of the world active or not
void World::SetActive(bool toggle)
{
	this->isActive = toggle;
	mBasket->SetActive(toggle);
	mCannon->SetActive(toggle);
	mEyes->SetActive(toggle);
	mBackground->SetActive(toggle);
	mBallIndicator->SetActive(toggle);
	for (int i = 0; i < NB_STUFF; i++)
	{
		mNotes[i]->SetActive(toggle);
		mPegs[i]->SetActive(toggle);
	}
	for each (Star* s in mStars)
	{
		s->SetActive(toggle);
	}

}

//Reset specifically the level, which is called when you don't lose and when you do
void World::ResetLevel()
{
	//Also result in an ugly but quick level layout
	fanfareOver = false;
	Peg::hasWon = false;
	mTimer = SING_DELAY;
	currentNote = 0;
	mCannon->SetFrozen(false);
	for (int i = 0; i < NB_STUFF; i++)
	{
		mNotes[i]->Reset();
		int x = i % 5;
		int y = i / 5;
		mPegs[i]->ResetToLocation(-250+(x * 120), -120+(y*80));
	}
}

//Handle the world's various updates
void World::Update()
{	
	float dt = gTimer->GetDeltaTime();

	//The singing fanfare is dealt with using a timer
	if (Peg::hasWon == true && fanfareOver == false)
	{
		if (!(mCannon->GetFrozen()))
		{
			mCannon->VictoryFreeze();
			AudioSys->stopAllSounds();
			AudioSys->setSoundVolume(1.0f);
		}
		mTimer -= dt;
		if (mTimer <= 0)
		{
			mNotes[currentNote]->Sing();
			std::cout << currentNote << std::endl;
			mTimer = SING_DELAY;
			currentNote++;
			if (currentNote == NB_STUFF)
			{
				fanfareOver = true;
				AudioSys->setSoundVolume(0.5f);
				AudioSys->play2D(Sounds->Get(Sound::Music));
			}
		}
		//Once the fanfare is over we'll reset the level

	}
	else if (fanfareOver == true)
	{
		ResetLevel();
	}
	else
	{
		//Update the ball indicator's display based upon the current amount of balls left
		switch (mCannon->GetBalls())
		{
		case 1:
			mBallIndicator->SetTexInfos(Texture::BallIndicator1);
			break;
		case 2:
			mBallIndicator->SetTexInfos(Texture::BallIndicator2);
			break;
		case 3:
			mBallIndicator->SetTexInfos(Texture::BallIndicator3);
			break;
		case 0:
			isGameOver = true;
			break;
		}
	}
}