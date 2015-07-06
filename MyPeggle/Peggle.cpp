#include "Background.h"
#include "Basket.h"
#include "Cannon.h"
#include "Eyes.h"
#include "Peg.h"
#include "Peggle.h"
#include "Projectile.h"
#include "ResourceIDs.h"

Peggle::Peggle()
{
	//Bunch of resources being loaded
#pragma region Projectiles
	Textures->LoadTexture(Texture::Projectile_Red,		"Eye_Red.png");
	Textures->LoadTexture(Texture::Projectile_Orange,   "Eye_Orange.png");
	Textures->LoadTexture(Texture::Projectile_Yellow,   "Eye_Yellow.png");
	Textures->LoadTexture(Texture::Projectile_Green,	"Eye_Green.png");
	Textures->LoadTexture(Texture::Projectile_Cyan,		"Eye_Cyan.png");
	Textures->LoadTexture(Texture::Projectile_Blue,		"Eye_Blue.png");
	Textures->LoadTexture(Texture::Projectile_Purple,	"Eye_Purple.png");
	Textures->LoadTexture(Texture::Projectile_Pink,		"Eye_Pink.png");
	Textures->LoadTexture(Texture::Projectile_Grey,		"Eye_Grey.png");
	Textures->LoadTexture(Texture::Projectile_Black,	"Eye_Black.png");
#pragma endregion
#pragma region Pegs
	Textures->LoadTexture(Texture::Peg_Red,				"Projectile_Red.png");
	Textures->LoadTexture(Texture::Peg_Orange,			"Projectile_Orange.png");
	Textures->LoadTexture(Texture::Peg_Yellow,			"Projectile_Yellow.png");
	Textures->LoadTexture(Texture::Peg_Green,			"Projectile_Green.png");
	Textures->LoadTexture(Texture::Peg_Cyan,			"Projectile_Cyan.png");
	Textures->LoadTexture(Texture::Peg_Blue,			"Projectile_Blue.png");
	Textures->LoadTexture(Texture::Peg_Purple,			"Projectile_Purple.png");
	Textures->LoadTexture(Texture::Peg_Pink,			"Projectile_Pink.png");
	Textures->LoadTexture(Texture::Peg_Grey,			"Projectile_Grey.png");
	Textures->LoadTexture(Texture::Peg_Black,			"Projectile_Black.png");
#pragma endregion
#pragma region Notes
	Textures->LoadTexture(Texture::Note_Red,			"Note_Red.png");
	Textures->LoadTexture(Texture::Note_Orange,			"Note_Orange.png");
	Textures->LoadTexture(Texture::Note_Yellow,			"Note_Yellow.png");
	Textures->LoadTexture(Texture::Note_Green,			"Note_Green.png");
	Textures->LoadTexture(Texture::Note_Cyan,			"Note_Cyan.png");
	Textures->LoadTexture(Texture::Note_Blue,			"Note_Blue.png");
	Textures->LoadTexture(Texture::Note_Purple,			"Note_Purple.png");
	Textures->LoadTexture(Texture::Note_Pink,			"Note_Pink.png");
	Textures->LoadTexture(Texture::Note_Grey,			"Note_Grey.png");
	Textures->LoadTexture(Texture::Note_Black,			"Note_Black.png");
#pragma endregion
	Textures->LoadTexture(Texture::StartingScreen, "StartingScreen.png");
	Textures->LoadTexture(Texture::GameOverScreen, "GameOverScreen.png");
	Textures->LoadTexture(Texture::Background,"Background.png");
	Textures->LoadTexture(Texture::Eyes, "Eyes.png");
	Textures->LoadTexture(Texture::BlinkLeft, "BlinkLeft.png");
	Textures->LoadTexture(Texture::BlinkRight, "BlinkRight.png");
	Textures->LoadTexture(Texture::Cannon, "Cannon.png");
	Textures->LoadTexture(Texture::Basket, "Basket.png");

	Textures->LoadTexture(Texture::BallIndicator1, "BallIndicator1.png");
	Textures->LoadTexture(Texture::BallIndicator2, "BallIndicator2.png");
	Textures->LoadTexture(Texture::BallIndicator3, "BallIndicator3.png");

	Textures->LoadTexture(Texture::Star1, "Star1.png");
	Textures->LoadTexture(Texture::Star2, "Star2.png");
	Textures->LoadTexture(Texture::Star3, "Star3.png");

	Sounds->LoadSound(Sound::Music, "Music.mp3");
	Sounds->LoadSound(Sound::Red, "Red.wav");
	Sounds->LoadSound(Sound::Orange, "Orange.wav");
	Sounds->LoadSound(Sound::Yellow, "Yellow.wav");
	Sounds->LoadSound(Sound::Green, "Green.wav");
	Sounds->LoadSound(Sound::Cyan, "Cyan.wav");
	Sounds->LoadSound(Sound::Blue, "Blue.wav");
	Sounds->LoadSound(Sound::Purple, "Purple.wav");
	Sounds->LoadSound(Sound::Pink, "Pink.wav");
	Sounds->LoadSound(Sound::Grey, "Grey.wav");
	Sounds->LoadSound(Sound::Black, "Black.wav");
	Sounds->LoadSound(Sound::Confirm, "Confirm.wav");
	Sounds->LoadSound(Sound::Launch, "Launch.wav");
	Sounds->LoadSound(Sound::Blink, "Blink.wav");
	Sounds->LoadSound(Sound::Basket, "Basket.wav");
	Sounds->LoadSound(Sound::Doom, "Doom.wav");
	AudioSys->setSoundVolume(0.5f);

	//No point in making a class for the start/gameover screens
	mStartingScreen = new Sprite(Texture::StartingScreen);
	mGameOverScreen = new Sprite(Texture::GameOverScreen);
	D3DXVECTOR3 center(mStartingScreen->GetTextureInfos()->infos.Width / 2, mStartingScreen->GetTextureInfos()->infos.Height / 2, 0.0f);
	mStartingScreen->SetPivot(center);
	mStartingScreen->SetPosition(0, 0);
	mStartingScreen->SetRotationDeg(0, 180, 0);
	mGameOverScreen->SetPivot(center);
	mGameOverScreen->SetPosition(0, 0);
	mGameOverScreen->SetRotationDeg(0, 180,0);

	//The most important initialization, our game field
	mWorld = new World();

	//We start with the start menu
	ChangeState(Starting);
}

Peggle::~Peggle()
{

}

//Will update the current game state
void Peggle::Update()
{
	switch (mCurrentState)
	{
	case Starting:
		if ((gDInput->keyPressed(DIKEYBOARD_SPACE) || gDInput->keyPressed(DIKEYBOARD_RETURN)))
		{
			ChangeState(Playing);
			AudioSys->play2D(Sounds->Get(Sound::ID::Confirm));
		}
		break;
	case Playing:
		if (mWorld->GetIsGameOver())
		{
			ChangeState(GameOver);
		}
		break;
	case GameOver:
		if (gDInput->keyPressed(DIKEYBOARD_R))
		{
			ChangeState(Playing);
			AudioSys->play2D(Sounds->Get(Sound::ID::Confirm));
		}
		if ((gDInput->keyPressed(DIKEYBOARD_SPACE) || gDInput->keyPressed(DIKEYBOARD_RETURN)))
		{
			ChangeState(Starting);
			AudioSys->play2D(Sounds->Get(Sound::ID::Confirm));
		}
		break;
	}
}

//Change game state, will activate/deactive appropriate thingies accordingly
void Peggle::ChangeState(States state)
{
	switch (state)
	{
	case Starting:
		AudioSys->stopAllSounds();
		mStartingScreen->SetActive(true);
		mGameOverScreen->SetActive(false);
		mWorld->SetActive(false);
		break;
	case Playing:
		AudioSys->play2D(Sounds->Get(Sound::Music));
		mStartingScreen->SetActive(false);
		mGameOverScreen->SetActive(false);
		mWorld->SetActive(true);
		mWorld->ResetWorld();
		break;
	case GameOver:
		AudioSys->stopAllSounds();
		mStartingScreen->SetActive(false);
		mGameOverScreen->SetActive(true);
		mWorld->SetActive(false);
		break;
	}
	mCurrentState = state;
}
