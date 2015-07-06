#ifndef COLORABLE_HPP
#define COLORABLE_HPP

enum Color
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
	Black
};

//Abstract class for objects with various colors
class Colorable
{

public:
	void RandomizeColor();
	Color GetColor() { return mColor; }

protected:
	virtual void UpdateColor() = 0;

	Color mColor;
};

#endif