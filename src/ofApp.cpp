#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    centre.x = 0;
    centre.y = 0;
    countrySize = 125;
    noise.load("p1.mp3");
    noise.setLoop(true);
   // noise.setMultiPlay(true);
  //  noise.play();
    noise.setVolume(0.5f);
    
    britFlag.load("flag.png");
    
    string path = "countries";
    ofDirectory dir(path);
    dir.listDir();
    for(int i = 0; i < dir.size(); i++){
        countryName = dir.getPath(i);
        countryName.erase(0, countryName.find("/")+1);
        countryNames.push_back(countryName);
    }
    int numCountries = dir.size();
    for(int i = 0; i < numCountries; i++){
        country newCountry(countryNames[i]);
        countries.push_back(newCountry);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if(noise.getPosition() > 0.7){
        noise.setPosition(0);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

    ofDrawCircle(centre, countrySize);
    britFlag.draw(centre.x-britFlag.getWidth()/4,centre.y-britFlag.getHeight()/4,britFlag.getWidth()/2,britFlag.getHeight()/2);
    for(int i = 0; i < countries.size(); i++){
        countries[i].draw(i);
        dist = ofDist(centre.x, centre.y, countries[i].point.x, countries[i].point.y);
        if(dist - countrySize < countries[i].radius){
            
            int rand;
            if((!countries[i].v_bass[0].isPlaying())&&(!countries[i].v_drum[0].isPlaying())&&(!countries[i].v_lead[0].isPlaying())){
                rand = ofRandom(3);
                cout << rand << endl;
            }else{
                rand = 4;
            }
            
            switch (rand) {
                case 0:
                    if(!countries[i].v_bass[0].isPlaying()){
                        countries[i].v_bass[0].play();
                        cout << "bass" << countries[i].name << endl;
                    }
                    break;
                case 1:
                    if(!countries[i].v_drum[0].isPlaying()){
                        countries[i].v_drum[0].play();
                        cout << "drum" << countries[i].name << endl;
                    }
                    break;
                case 2:
                    if(!countries[i].v_lead[0].isPlaying()){
                        countries[i].v_lead[0].play();
                        cout << "lead" << countries[i].name << endl;
                    }
                    break;
            }
        }else{
            countries[i].v_bass[0].stop();
            countries[i].v_drum[0].stop();
            countries[i].v_lead[0].stop();
        }
    }
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
//--------------------------------------------------------------
country::country(string nameOfCountry){
    name = nameOfCountry;
    radius = 25;
    r = ofRandom(30,220);
    g = ofRandom(30,220);
    b = ofRandom(30,220);
    
    string path_b = "countries/" + name + "/bass/bass";
    string path_d = "countries/" + name + "/drums/drums";
    string path_l = "countries/" + name + "/lead/lead";
    flag.load("countries/"+name+"/flag.png");
    

    for(int i = 0; i < 1; i++){
        ofSoundPlayer bass,lead,drums;
        bass.load(path_b + ofToString(i) +".mp3");
        //bass.setMultiPlay(true);
        bass.setLoop(true);
        lead.load(path_b + ofToString(i) +".mp3");
        //lead.setMultiPlay(true);
        lead.setLoop(true);
        drums.load(path_d + ofToString(i) +".mp3");
        //drums.setMultiPlay(true);
        drums.setLoop(true);
        v_bass.push_back(bass);
        v_drum.push_back(drums);
        v_lead.push_back(lead);
    }
}

country::~country(){
    
}

void country::draw(float index){
    time = ofGetElapsedTimef();
    float speed = 0.01;
    float posX = (index*1.1) + 39.54;
    float posY = (index*1.1) + 42.69;
    
    point.x = (ofGetWidth()*2.0) * ofNoise(time * (speed*(index+1)) + posX) - ofGetWidth();
    point.y = (ofGetHeight()*2.0) * ofNoise(time * (speed*(index+1)) + posY) - ofGetHeight();
    ofSetColor(r, g, b, 110);
    ofDrawCircle(point, radius);
    ofSetColor(255);
    flag.draw(point.x-flag.getWidth()/20,point.y-flag.getHeight()/20,flag.getWidth()/10,flag.getHeight()/10);
    // make it more controlled and less flowy looking, give the countries a sense of intention
    ofDrawBitmapString(name, point.x+25,point.y);
}
