#include "Projectile.h"


Projectile::Projectile()
	: Sprite(Texture::Projectile)
{
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, 0);
}


Projectile::~Projectile()
{
}

void Projectile::Update()
{
}