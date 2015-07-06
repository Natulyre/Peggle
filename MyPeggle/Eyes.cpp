#include "Eyes.h"

//Position
const int POS_X = 0;
const int POS_Y = 200;

const float BLINK_DELAY = 6.f;

Eyes::Eyes()
	: Sprite(Texture::Eyes),
	mTimer(BLINK_DELAY),
	isBlinking(false)
{

	//Sprite setup
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, -180);
	this->SetPosition(POS_X, POS_Y);
}


Eyes::~Eyes()
{
}

void Eyes::Update()
{
	float dt = gTimer->GetDeltaTime();

	//Once the timer runs out, we'll blink (or unblink) accordingly
	mTimer -= dt;
	if (mTimer <= 0)
	{
		//Once the moon blinks the delay before it unblinks is 1/6 of the usual delay before eye-action
		if (!isBlinking)
		{
			mTimer = BLINK_DELAY/6;
			Blink();
		}
		else
		{
			isBlinking = false;
			this->SetTexInfos(Texture::ID::Eyes);
			mTimer = BLINK_DELAY;
		}
	}
}

//Eyes will blink randomly left or right
void Eyes::Blink()
{
	AudioSys->play2D(Sounds->Get(Sound::Blink));
	int random = rand() % 2;
	isBlinking = true;
	if (random == 0)
	{
		this->SetTexInfos(Texture::ID::BlinkLeft);
	}
	else if (random == 1)
	{
		this->SetTexInfos(Texture::ID::BlinkRight);
	}
}