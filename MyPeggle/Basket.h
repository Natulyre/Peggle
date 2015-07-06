#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"
#include "Utils.h"
#include "CRectangle.h"

class Basket :
	public Sprite
{
public:
	Basket();
	~Basket();

	void Update();
	void SetActive(bool toggle);

private:
	D3DXVECTOR2 mVelocity;
	CRectangle* mCollider;
};

