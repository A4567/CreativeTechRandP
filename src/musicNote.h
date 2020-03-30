#pragma once
#include "ofMain.h"
#include "ofxSvg.h"
#include <string>

class musicNote
{
public:
	musicNote();
	void setImage();
	void drawNewTrail();
	void clearTrail();



	string countryName;

	ofImage leadNoteImage;
	vector<ofImage> noteTrail;

	int amountOfNoteImages = 54;

	
};

