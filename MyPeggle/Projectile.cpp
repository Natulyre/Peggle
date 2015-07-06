#include "Projectile.h"
#include "Peg.h"

//Game limits
const int HEIGHT_LIMIT = 500;
const int WIDTH_LIMIT = 340;

const float GRAVITY = -1;


Projectile::Projectile(float x, float y)
: Sprite(Texture::Projectile_Red),
	hasBeenLaunched(false),
	mInitialLocation(x, y),
	mVelocity(0, 0)
{
	//Sprite setup
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, 180);
	this->SetPosition(mInitialLocation.x, mInitialLocation.y);

	//Collider setup
	this->mCollider = new CCircle(this, mInitialLocation.x, mInitialLocation.y, 16);
	this->SetID(Components::Projectile);
}


Projectile::~Projectile()
{
}

//Update the sprite's texture based upon the currentColor
void Projectile::UpdateColor()
{
	switch (mColor)
	{
	case Red:
		this->SetTexInfos(Texture::Projectile_Red);
		break;
	case Orange:
		this->SetTexInfos(Texture::Projectile_Orange);
		break;
	case Yellow:
		this->SetTexInfos(Texture::Projectile_Yellow);
		break;
	case Green:
		this->SetTexInfos(Texture::Projectile_Green);
		break;
	case Cyan:
		this->SetTexInfos(Texture::Projectile_Cyan);
		break;
	case Blue:
		this->SetTexInfos(Texture::Projectile_Blue);
		break;
	case Purple:
		this->SetTexInfos(Texture::Projectile_Purple);
		break;
	case Pink:
		this->SetTexInfos(Texture::Projectile_Pink);
		break;
	case Grey:
		this->SetTexInfos(Texture::Projectile_Grey);
		break;
	case Black:
		this->SetTexInfos(Texture::Projectile_Black);
		break;
	default:
		break;
	}
}

//Reset the projectile & randomize its color, everyone likes colored balls
void Projectile::Reset()
{
	mVelocity.x = 0;
	mVelocity.y = 0;
	hasBeenLaunched = false;
	isLost = false;
	isSaved = false;
	this->SetPosition(mInitialLocation.x, mInitialLocation.y);
	mCollider->SetPosition(mInitialLocation.x, mInitialLocation.y);
	RandomizeColor();
}


//Move the projectile and handle collisions
void Projectile::Update()
{
	float dt = gTimer->GetDeltaTime();
	//We'll only update its velocity if the ball has been launched
	if (hasBeenLaunched)
	{
		mVelocity.y += GRAVITY *dt;
		this->SetPosition(this->GetPosition().x + this->mVelocity.x, this->GetPosition().y + this->mVelocity.y);
		mCollider->SetPosition(this->GetPosition().x, this->GetPosition().y);
	}	

	//Go through each collider collided with though the LookForCollision Function
	for each (Collider* col in mCollider->LookForCollisions())
	{
		//If one of the component hit a Peg
		if (col->GetGameObject()->GetID() == Components::Peg)
		{
			Bounce(col);
			//Consider that collider's component a peg directly and activate its onHit function
			static_cast<Peg*>(col->GetGameObject())->OnHit();
		}
		//If one of the component hit is the basket
		if (col->GetGameObject()->GetID() == Components::Basket)
		{
			AudioSys->play2D(Sounds->Get(Sound::Basket));
			//Set isSaved to true, which will "save" the ball
			isSaved = true;
		}
	}

	//If the ball goes too low, we lose it
	if (this->GetPosition().y < -HEIGHT_LIMIT)
	{
		AudioSys->play2D(Sounds->Get(Sound::Doom));
		isLost = true;
	}
	//Otherwise the ball will bounce off the screen's upper limit
	else if (this->GetPosition().y > HEIGHT_LIMIT)
	{
		mVelocity.y = -mVelocity.y;
	}
	//And the screen's Left/Right limits
	else if (this->GetPosition().x > WIDTH_LIMIT || this->GetPosition().x < -WIDTH_LIMIT)
	{
		mVelocity.x = -mVelocity.x;
	}

}

//Launch the projectile based on the cannon's orientation
void Projectile::Launch(D3DXVECTOR2* orientation)
{
	mVelocity.x = orientation->x / 200.f;
	mVelocity.y = orientation->y / 200.f;
}

//A broken unbalanced version of the actual math for collisions. We're looking for a low-gravity bouncy ball recoil.
//The game's charm come from its difficulty and sillyness.
void Projectile::Bounce(Collider* collider)
{
	D3DXVECTOR3 vectDir(mVelocity.x, mVelocity.y, 0);
	//Formation de la norme de la tangeante et normalisation
	D3DXVECTOR3 ballObstacle((collider->GetPosition().x + 16.f) - (this->GetPosition().x + 16.f),
		(collider->GetPosition().y + 16.f) - (this->GetPosition().y + 16.f), 0);
	D3DXVECTOR3 collisionNorm(0,0,0);
	D3DXVec3Normalize(&collisionNorm, &ballObstacle);
	//Réflexion du vecteur sur la tangeante
	D3DXVECTOR3 outVect(0,0,0);
	float dotProduct = D3DXVec3Dot(&vectDir, &collisionNorm);
	collisionNorm.x = (collisionNorm.x * dotProduct*2.f);
	collisionNorm.y = (collisionNorm.y * dotProduct*2.f);

	outVect = outVect - collisionNorm;
	outVect.x *= 0.45f;
	outVect.y *= 0.45f;
	
	//Ajustement de la direction selon le rebond calculé
	mVelocity.x = outVect.x;
	mVelocity.y = outVect.y;
}
