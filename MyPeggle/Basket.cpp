#include "Basket.h"


Basket::Basket()
	: Sprite(Texture::Basket)
{
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, -180, 0);
	this->SetPosition(0, 0);
	//this->Scale(0);
	//this->SetPosition(-250, 0);
}


Basket::~Basket()
{
}

void Basket::Update()
{
}