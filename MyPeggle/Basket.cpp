#include "Basket.h"

//Position
const int POS_X = 0;
const int POS_Y = -220;
//Movement Speed
const int SPEED_X = 100;
const int SPEED_Y = 0;
//Collider related
const int COL_WIDTH = 70; //88 actual width
const int COL_HEIGHT = 20; //32 actual height
//Movement limits
const int LIMIT_X = 325;


Basket::Basket()
	: Sprite(Texture::Basket),
	mVelocity(SPEED_X, SPEED_Y)
{
	//Sprite setup
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, -180);
	this->SetPosition(POS_X, POS_Y);

	//Collider setup
	mCollider = new CRectangle(this, POS_X - COL_WIDTH / 2, POS_Y - COL_HEIGHT / 2, COL_WIDTH, COL_HEIGHT);
	this->SetID(Components::Basket);
	
}


Basket::~Basket()
{
}

//Set the basket and its collider's active states
void Basket::SetActive(bool toggle)
{
	this->isActive = toggle;
	mCollider->SetEnabled(toggle);
}

void Basket::Update()
{
	float dt = gTimer->GetDeltaTime();

	//Move the basket based upon its current velocity & delta time
	this->SetPosition(this->GetPosition().x + mVelocity.x * dt, this->GetPosition().y + mVelocity.y * dt);

	//Set its collider position
	mCollider->SetPosition(this->GetPosition().x - COL_WIDTH / 2, this->GetPosition().y - COL_HEIGHT / 2);

	//If the basket reach the horizontal limit, it'll turn around.
	if (this->GetPosition().x <= -LIMIT_X || this->GetPosition().x >= LIMIT_X)
	{
		mVelocity.x = -mVelocity.x;
	}
}