#include "Note.h"


Note::Note()
: Sprite(Texture::Note_Red)
{
	//Sprite setup
	D3DXVECTOR3 center(this->GetTextureInfos()->infos.Width / 2, this->GetTextureInfos()->infos.Height / 2, 0.0f);
	this->SetPivot(center);
	this->SetRotationDeg(0, 0, -180);
}


Note::~Note()
{
}

//Plays a note based on its color
//Notes will sing when hit and when victory is reached, creating a wonderful* song
void Note::Sing()
{
	switch (mColor)
	{
	case Red:
		AudioSys->play2D(Sounds->Get(Sound::Red));
		break;
	case Orange:
		AudioSys->play2D(Sounds->Get(Sound::Orange));
		break;
	case Yellow:
		AudioSys->play2D(Sounds->Get(Sound::Yellow));
		break;
	case Green:
		AudioSys->play2D(Sounds->Get(Sound::Green));
		break;
	case Cyan:
		AudioSys->play2D(Sounds->Get(Sound::Cyan));
		break;
	case Blue:
		AudioSys->play2D(Sounds->Get(Sound::Blue));
		break;
	case Purple:
		AudioSys->play2D(Sounds->Get(Sound::Purple));
		break;
	case Pink:
		AudioSys->play2D(Sounds->Get(Sound::Pink));
		break;
	case Grey:
		AudioSys->play2D(Sounds->Get(Sound::Grey));
		break;
	case Black:
		AudioSys->play2D(Sounds->Get(Sound::Black));
		break;
	default:
		break;
	}
}

//Set a note as captured (captured notes are displayed in the upper left corner), make it sing and update its sprite
void Note::Capture(Color color)
{
	isActive = true;
	isCaptured = true;
	mColor = color;
	UpdateColor();
	Sing();
}

//Reset Note
void Note::Reset()
{
	isCaptured = false;
	isActive = false;
}

//Update the sprite's texture based upon the currentColor
void Note::UpdateColor()
{
	switch (mColor)
	{
	case Red:
		this->SetTexInfos(Texture::Note_Red);
		break;
	case Orange:
		this->SetTexInfos(Texture::Note_Orange);
		break;
	case Yellow:
		this->SetTexInfos(Texture::Note_Yellow);
		break;
	case Green:
		this->SetTexInfos(Texture::Note_Green);
		break;
	case Cyan:
		this->SetTexInfos(Texture::Note_Cyan);
		break;
	case Blue:
		this->SetTexInfos(Texture::Note_Blue);
		break;
	case Purple:
		this->SetTexInfos(Texture::Note_Purple);
		break;
	case Pink:
		this->SetTexInfos(Texture::Note_Pink);
		break;
	case Grey:
		this->SetTexInfos(Texture::Note_Grey);
		break;
	case Black:
		this->SetTexInfos(Texture::Note_Black);
		break;
	default:
		break;
	}
}
