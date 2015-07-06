#include "Cannon.h"

//Position
const int POS_X = 0;
const int POS_Y = 190;
//Rotation Speed
const int SPEED = 65;
//Rotation limits
const int LIMIT = 62;

//Shooting delay
const float DELAY = 0.2f;

//Used for the projectile's spawn
const float CANNON_LENGTH = 80;

//Number of balls you start with
const int NB_BALLS = 3;

Cannon::Cannon()
: Sprite(Texture::Cannon),
mProjectileVector(0, -CANNON_LENGTH),
mProjectileOrientation(0, 0),
mLaunchDelay(DELAY),
mRotation(0),
isFrozen(false)
{
	//Sprite setup
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, 0);
	this->SetPosition(POS_X, POS_Y);

	//Initialize the cannon's projectile
	mProjectile = new Projectile(POS_X, POS_Y - CANNON_LENGTH);
}


Cannon::~Cannon()
{
}

//Reset the cannon & its projectile (via its own reset) back to their default state 
void Cannon::Reset()
{
	mRotation = 0;
	isFrozen=false;
	mBalls = NB_BALLS;
	mLaunchDelay=DELAY;
	mProjectile->Reset();
}

//Set the cannon and its projectile's active states
void Cannon::SetActive(bool toggle)
{
	this->isActive = toggle;
	mProjectile->SetActive(toggle);
}

//Freeze the cannon for the fanfare
void Cannon::VictoryFreeze()
{
	isFrozen = true;
	mProjectile->Reset();
	RotateProjectile();
	//We'll give our lucky player another ball if he managed to finish a level (unless he currently has 3)
	if (mBalls < 3)
	{
		mBalls += 1;
	}
}

void Cannon::Update()
{
	float dt = gTimer->GetDeltaTime();
	if (!isFrozen)
	{
		//Turn the cannon (Left/Right) around based upon the player's input (Arrows & A/D)
		//If the rotation limit is breached, it'll be set to its rotation limit
		if (gDInput->keyDown(DIKEYBOARD_RIGHT) || gDInput->keyDown(DIKEYBOARD_D))
		{
			mRotation += SPEED * dt;
			if (mRotation > LIMIT)
			{
				mRotation = LIMIT;
			}
		}
		if (gDInput->keyDown(DIKEYBOARD_LEFT) || gDInput->keyDown(DIKEYBOARD_A))
		{
			mRotation -= SPEED * dt;
			if (mRotation < -LIMIT)
			{
				mRotation = -LIMIT;
			}
		}

		//There's a small delay before you can launch your first ball, preventing accidental shootings when you start the game.
		if (mLaunchDelay > 0)
		{
			mLaunchDelay -= dt;
		}
		else
		{
			//Otherwise launch projectile on Space/Return
			if (!mProjectile->GetHasBeenLaunched() && (gDInput->keyPressed(DIKEYBOARD_SPACE) || gDInput->keyPressed(DIKEYBOARD_RETURN)))
			{
				this->Shoot();
			}
		}

		//Update the Cannon's rotation based upon its current velocity & delta time
		this->SetRotationDeg(0, 0, mRotation);
		//And the projectile's, if it hasn't been launched
		if (!mProjectile->GetHasBeenLaunched())
		{
			mProjectile->SetRotationDeg(0, 0, mRotation);
			RotateProjectile();
		}
		else
		{
			//Otherwise, if the projectile has launched we check if the ball was lost or saved
			//Lost = Breached the lower limit (-1 ball)
			//Saved = Hit the rice bowl (0 ball lost)
			if (mProjectile->GetIsLost())
			{
					mProjectile->Reset();
					mBalls -= 1;
			}
			else if (mProjectile->GetIsSaved())
			{
				mProjectile->Reset();
			}
		}
	}
}

//Rotate our projectile based upon the cannon's rotation & length
void Cannon::RotateProjectile()
{
	//Degree to Radian
	float angle = mRotation / 180 * PI;

	//Rotate our vector
	float rotatedX = cosf(angle)*mProjectileVector.x - sinf(angle)*mProjectileVector.y;
	float rotatedY = sinf(angle)*mProjectileVector.x + cosf(angle)*mProjectileVector.y;

	mProjectileOrientation.x = rotatedX;
	mProjectileOrientation.y = rotatedY;

	//Set the result
	mProjectile->SetPosition(this->GetPosition().x + rotatedX, this->GetPosition().y +rotatedY);
}

//Shoot the projectile
void Cannon::Shoot()
{
	AudioSys->play2D(Sounds->Get(Sound::Launch));
	mProjectile->SetHasBeenLaunched(true);
	mProjectile->Launch(&mProjectileOrientation);
}