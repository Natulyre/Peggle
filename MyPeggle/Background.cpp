#include "Background.h"


Background::Background()
	: Sprite(Texture::Background)
{
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, 0);
}


Background::~Background()
{
}

void Background::Update()
{
}