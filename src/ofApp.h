#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "country.h"


class nowPlaying {
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
    void loadInfo(int startX, int startY);

        
    vector<country> countries;
    ofVec3f centre;
    float dist;
    int countrySize;
    vector<string> countryNames;
    string countryName;
    ofSoundPlayer baseMusicB,baseMusicL,baseMusicD;
    vector<ofSoundPlayer> soundVectorBass,soundVectorDrum,SoundVectorLead;
    vector<bool> play;
    ofImage britFlag;
    int randspawn;
    ofImage mapOutline;
	int countryIndex;

    int qSize;
	ofEasyCam camera;

    nowPlaying nowPlayer;
	
	ofxSVG worldMapSVG;

    int cardIndex, cardSize;
    bool b_toggleQ;

	int boxStartY;
	int boxStartX;

	vector<ofImage> infoCards;
	

};
