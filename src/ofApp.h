#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "country.h"
#include "dynamicCamera.h"




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

		
        
    vector<country> countries;
    ofVec3f centre;
    float dist;
    int countrySize;
    vector<string> countryNames;
    string countryName;
    ofSoundPlayer baseMusic;
    vector<ofSoundPlayer> soundVectorBass,soundVectorDrum,SoundVectorLead;
    vector<bool> play;
    ofImage britFlag;
    int randspawn;
    ofImage mapOutline;
	int countryIndex;


	ofEasyCam camera;


	
	ofxSVG worldMapSVG;


};
