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
	Textures->LoadTexture(Texture::Projectile, "Projectile_Red.png");
	Textures->LoadTexture(Texture::Peg, "Projectile_Red.png");
	Textures->LoadTexture(Texture::Background, "Projectile_Red.png");
	Textures->LoadTexture(Texture::Eyes, "Eyes.png");
	Textures->LoadTexture(Texture::Cannon, "Cannon.png");
	Textures->LoadTexture(Texture::Basket, "Basket.png");

	//Sounds->LoadSound(Sound::TestMusicID, "testmusic.mp3");
	//Sounds->LoadSound(Sound::TestSoundFXID, "bell.wav");

	//AudioSys->play2D(Sounds->Get(Sound::TestMusicID));
	//AudioSys->play2D(Sounds->Get(Sound::TestSoundFXID));

	//Cannon* cannon = new Cannon();
	Basket* basket = new Basket();
}

Peggle::~Peggle()
{

}

void Peggle::Start()
{

}

void Peggle::Update()
{

}

void Peggle::Draw()
{

}

void Peggle::Stop()
{

}
