#include "musicNote.h"

musicNote::musicNote() 
{
	
}

void musicNote::setImage()
{
	int imageNumber;
	imageNumber = ofRandom(1, amountOfNoteImages);
	string convertedNumber = to_string(imageNumber);

	leadNoteImage.load("musicnotes/" + convertedNumber + ".png");
	leadNoteImage.resize(leadNoteImage.getWidth() / 25, leadNoteImage.getHeight() / 25);

	for (int i = 1; i < amountOfNoteImages + 1; i++)
	{
		noteTrail[i].load("musicnotes/" + to_string(i) + ".png");
	}
	
}
 


void musicNote::clearTrail()
{
	noteTrail.clear();
}