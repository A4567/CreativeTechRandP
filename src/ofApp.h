#pragma once

#include "ofMain.h"


class country {
    
public:
    
    
    void draw(float index);
    float time;
    int radius,r,g,b;
    ofVec3f point;
    country(string nameOfCountry);
    ~country();
    string name;
    //audioManager countryAudioManager;
    vector<ofSoundPlayer> v_bass, v_drum, v_lead;
    ofImage flag;
    
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
};
