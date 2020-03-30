#pragma once

#include "ofMain.h"
#include "musicNote.h"


class country 

{

public:

	country(string nameOfCountry);
	~country();

	void draw(float index, ofVec3f target);

	string countryName;

	float time;
	ofVec3f point;
	
	bool b_spawn;
	vector<ofVec3f> spawn;

	//--------------------------------------------audio
	vector<ofSoundPlayer> v_bass, v_drum, v_lead;

	//--------------------------------------------visuals
	//------flag
	ofImage flag;
	int radius, r, g, b;
	
	//------note trails
	musicNote note;



	//MAYBE ADD A DELAY TIMER FROM HERE
};