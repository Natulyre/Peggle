#include "Colorable.h"
#include "Utils.h"

//Assign a random color to the colorable
void Colorable::RandomizeColor()
{
	int random = rand() % 10;
	this->mColor = static_cast<Color>(random);

	UpdateColor();
}