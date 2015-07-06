#pragma once

#include "ResourceIDs.h"
#include "Sprite.h"
#include "Projectile.h"

class Cannon :
	public Sprite
{
public:
	Cannon();
	~Cannon();
	int GetBalls()	{ return mBalls; }
	void Reset();
	void SetActive(bool toggle);
	bool GetFrozen() { return isFrozen; }
	void SetFrozen(bool toggle) { isFrozen = toggle; }
	void VictoryFreeze();


private:
	void RotateProjectile();
	void Shoot();
	void Update();

	float mRotation;
	int mBalls;
	Projectile* mProjectile;
	D3DXVECTOR2 mProjectileVector;
	D3DXVECTOR2 mProjectileOrientation;
	bool isFrozen;

	float mLaunchDelay;
};

