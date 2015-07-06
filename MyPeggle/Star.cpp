#include "Star.h"

const float BLINK_DELAY = 0.7f;

Star::Star(float x, float y)
: Sprite(Texture::Star1),
mTimer(BLINK_DELAY),
isShining(false)
{
	//Sprite setup
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, -180);
	this->SetPosition(x, y);
}


Star::~Star()
{
}

void Star::Update()
{
	float dt = gTimer->GetDeltaTime();

	//Once the timer runs out, we'll Shine
	mTimer -= dt;
	if (mTimer <= 0)
	{
		Shine();
	}
}

//Star will Shine randomly and will have their delay randomly set (might be the same multiple time)
void Star::Shine()
{
	int random = rand() % 3;
	int random2 = rand() % 5;
	mTimer = BLINK_DELAY * random2;
	isShining = true;
	if (random == 0)
	{
		this->SetTexInfos(Texture::Star1);
	}
	else if (random == 1)
	{
		this->SetTexInfos(Texture::Star2);
	}
	else
	{
		this->SetTexInfos(Texture::Star3);
	}
}