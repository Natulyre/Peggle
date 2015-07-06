#ifndef ResourcesID
#define ResourcesID


namespace Components
{
	enum ID
	{
		UNDEFINED,
		Projectile,
		Peg,
		Basket,
	};
}

//There are a lot of repetitions for the differents colors
//but since I couldn't access/modify anything from the engine (No internet)
//I couldn't use a texture atlas.
namespace Texture
{
	enum ID
	{
		StartingScreen,
		GameOverScreen,
		Background,
		Basket,
		Cannon,
		Eyes,
		BlinkRight,
		BlinkLeft,
		BallIndicator3,
		BallIndicator2,
		BallIndicator1,
		Projectile_Red,
		Projectile_Orange,
		Projectile_Yellow,
		Projectile_Green,
		Projectile_Cyan,
		Projectile_Blue,
		Projectile_Purple,
		Projectile_Pink,
		Projectile_Grey,
		Projectile_Black,
		Peg_Red,
		Peg_Orange,
		Peg_Yellow,
		Peg_Green,
		Peg_Cyan,
		Peg_Blue,
		Peg_Purple,
		Peg_Pink,
		Peg_Grey,
		Peg_Black,
		Note_Red,
		Note_Orange,
		Note_Yellow,
		Note_Green,
		Note_Cyan,
		Note_Blue,
		Note_Purple,
		Note_Pink,
		Note_Grey,
		Note_Black,
		Star1,
		Star2,
		Star3
	};
}

namespace Sound
{
	enum ID
	{
		Red,
		Orange,
		Yellow,
		Green,
		Cyan,
		Blue,
		Purple,
		Pink,
		Grey,
		Black,
		Confirm,
		Launch,
		Music,
		Basket,
		Blink,
		Doom,
	};
}

//namespace Font
//{
//	enum ID
//	{
//		Dialog
//	};
//}

#endif 
