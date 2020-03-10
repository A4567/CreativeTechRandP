#pragma once

#include "ofMain.h"
#include "ofxSvg.h"


class country {
    
public:
    
    
    void draw(float index, ofVec3f target);
    float time;
    int radius,r,g,b;
    ofVec3f point;
    country(string nameOfCountry);
    ~country();
    string name;
    vector<ofSoundPlayer> v_bass, v_drum, v_lead;
    ofImage flag,note;
    bool b_spawn;
    vector<ofVec3f> spawn;
};

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
		
        
    vector<country> countries;
    ofVec3f centre;
    float dist;
    int countrySize;
    vector<string> countryNames;
    string countryName;
    ofSoundPlayer noise;
    vector<ofSoundPlayer> soundVectorBass,soundVectorDrum,SoundVectorLead;
    vector<bool> play;
    ofImage britFlag;
    int randspawn;
    ofImage mapOutline;

	ofEasyCam camera;
	ofVec3f middle;

	ofxSVG worldMapSVG;


};
