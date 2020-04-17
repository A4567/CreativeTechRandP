#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "country.h"


class nowPlaying 
{
public:
    vector<ofSoundPlayer> bassnow_v;
    vector<ofSoundPlayer> leadnow_v;
    vector<ofSoundPlayer> drumnow_v;

};

class ofApp : public ofBaseApp
{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
		void moveCamera();

		void loadCountries();
		void loadGraphics();
		void loadCamera();
		void loadBaseMusic();



        
    string countryName;

    ofSoundPlayer baseMusic;

    vector<ofSoundPlayer> soundVectorBass,soundVectorDrum,SoundVectorLead;
    vector<bool> play;
	vector<string> countryNames;
	vector<country> countries;
	ofSoundPlayer c_bass, c_drum, c_lead;

	string playing;

	ofVec3f centre;

    ofImage britFlag;
	ofImage mapOutline;

	ofxSVG worldMapSVG;


    int randspawn;
	int countryIndex;
	int countrySize;
    int qSize;

	ofEasyCam camera;
    nowPlaying nowPlayer;

	
	float dist;
	float mouseX;
	float mouseY;


};