#include "Cannon.h"


Cannon::Cannon()
	: Sprite(Texture::Cannon)
{
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, 0);
}


Cannon::~Cannon()
{
}

void Cannon::Update()
{
}