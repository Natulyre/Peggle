#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"
#include "CCircle.h"
#include "Colorable.h"

class Projectile :
	public Sprite, public Colorable
{
public:
	Projectile(float x, float y);
	~Projectile();

	void Update();
	void SetHasBeenLaunched(bool toggle) { hasBeenLaunched = toggle; }
	bool GetHasBeenLaunched()			{return hasBeenLaunched;}
	bool GetIsLost()					{ return isLost; }
	bool GetIsSaved()					{ return isSaved; }
	void Bounce(Collider* collider);
	void Adjust(Collider* collider);
	void Launch(D3DXVECTOR2* orientation);

	void Reset();

private:
	void UpdateColor();

	D3DXVECTOR2 mInitialLocation;
	D3DXVECTOR2 mVelocity;
	CCircle* mCollider;
	bool hasBeenLaunched;
	bool isLost;
	bool isSaved;
};

