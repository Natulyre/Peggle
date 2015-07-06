#include "Peg.h"
#include "World.h"

//Static int that represents how many pegs are on the "board"
int Peg::PegsAlive = 0;

//Whether the pegs have been all destroyed or not
bool Peg::hasWon = false;


Peg::Peg()
	: Sprite(Texture::Peg_Red)
{
	//Sprite setup
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, -180);

	//Collider setup
	mCollider = new CCircle(this, 0.f, 0.f, 16.f);
	this->SetID(Components::Peg);
}


Peg::~Peg()
{
}

//Basically Init/Reinit a peg toward a specific location
void Peg::ResetToLocation(float x, float y)
{
	this->SetActive(true);
	mCollider->SetEnabled(true);
	RandomizeColor();
	this->SetPosition(x, y);
	this->mCollider->SetPosition(x, y);
	if (PegsAlive < 15)
	{
		PegsAlive += 1;
	}
}

//Set the peg's and its collider's active state
void Peg::SetActive(bool toggle)
{
	this->isActive = toggle;
	this->mCollider->SetEnabled(toggle);
}


//Update the sprite's texture based upon the currentColor
void Peg::UpdateColor()
{
	switch (mColor)
	{
	case Red:
		this->SetTexInfos(Texture::Peg_Red);
		break;
	case Orange:
		this->SetTexInfos(Texture::Peg_Orange);
		break;
	case Yellow:
		this->SetTexInfos(Texture::Peg_Yellow);
		break;
	case Green:
		this->SetTexInfos(Texture::Peg_Green);
		break;
	case Cyan:
		this->SetTexInfos(Texture::Peg_Cyan);
		break;
	case Blue:
		this->SetTexInfos(Texture::Peg_Blue);
		break;
	case Purple:
		this->SetTexInfos(Texture::Peg_Purple);
		break;
	case Pink:
		this->SetTexInfos(Texture::Peg_Pink);
		break;
	case Grey:
		this->SetTexInfos(Texture::Peg_Grey);
		break;
	case Black:
		this->SetTexInfos(Texture::Peg_Black);
		break;
	default:
		break;
	}
}

//Upon being hit, the peg will *turn* into a note, which represents the final victory song, if achieved
void Peg::OnHit()
{
	this->SetActive(false);
	PegsAlive -= 1;
	World::mNotes[PegsAlive]->Capture(mColor);

	//If the new number of pegs alive is equal to 0, we win.
	if (Peg::PegsAlive == 0)
	{
		Peg::hasWon = true;
	}
}

void Peg::Update()
{
}