#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{    
    loadCountries();
    loadGraphics();
    loadBaseMusic();
    loadCamera();
    
    
    qSize = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // get current time if time is a factor of 5 clear the spawn vector and set the spawn boolean to true if non of the tracks in it are playing
    /*
     TO-DO: DELAY THE SENDING OF NOTES TO NOT OVERPOPULATE QUEUE
     ADD TIMER SYSTEM HERE
     */
    
    randspawn = ofGetElapsedTimef();
    for(int i = 0; i < countries.size(); i++)
    {
        if((randspawn % 500 == 0)&&(countries[i].spawn.size() < 1)&&((!countries[i].v_drum[0].isPlaying())&&(!countries[i].v_bass[0].isPlaying())&&(!countries[i].v_lead[0].isPlaying()))){
            countries[i].spawn.clear();
            countries[i].b_spawn = true;
            qSize++;
        }
        
        
    }
    
    if (camera.getX() < ofGetWidth() / 2) camera.setPosition(ofGetWidth() / 2, camera.getY(), camera.getZ());
    if (camera.getX() > worldMapSVG.getWidth() - ofGetWidth()/2) camera.setPosition(worldMapSVG.getWidth() - (ofGetWidth()/2), camera.getY(), camera.getZ());
    
    if (camera.getY() < ofGetHeight() / 1.75) camera.setPosition(camera.getX(), ofGetHeight() / 1.75, camera.getZ());
    if (camera.getY() > worldMapSVG.getHeight() - ofGetHeight()/1.75) camera.setPosition(camera.getX(), worldMapSVG.getHeight() - ofGetHeight() / 1.75, camera.getZ());
    
    //dynCamera.camera.moveCamera();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    camera.begin();
    
    
    //sets the colour of the countries on the map to white
    ofSetColor(255);
    
    //--------------------------------START MATRIX PUSH
    ofPushMatrix();
    
    ofScale(1, -1, -1);
    ofTranslate(0, -worldMapSVG.getHeight(), 0);
    worldMapSVG.draw();
    
    ofPopMatrix();
    
    //--------------------------------STOP MATRIX PUSH
    
    
    
    //--------------------------------START MATRIX PUSH
    //push the matrix to set the 0,0 point to the centre
    ofPushMatrix();
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    
    //draw the britsh flag over the uk
    britFlag.draw(centre.x-britFlag.getWidth()/20,centre.y-britFlag.getHeight()/20,britFlag.getWidth()/10,britFlag.getHeight()/10);
    //for every country trigger the draw function, it takes the i value each time as an index to allow for more variation later - might not be needed, but it does need the ofVec3f centre as a point for the spawners to move too
    for(int i = 0; i < countries.size(); i++){
        countries[i].draw(i,centre);
        //if the country has more than 0 spawns check the distance between it and the centre point
        if(countries[i].spawn.size() > 0){
            
            dist = ofDist(centre.x, centre.y, countries[i].spawn[0].x, countries[i].spawn[0].y);
            //if the distance minus the size of the uk is less than 3 pick a number between from 0 to 2 inclusive to decide which type of track will play - if there is a track playing from that country already set the value to 4 preventing it from triggering a sample
            
            //------------------------------------------------PLAYBACK OF AUDIO BEGIN---------------------------------------------------------
            /*
             TO-DO: MAKE QUEUE SYSTEM FOR PLAYBACK
             CHECK IF LEAD BASS OR DRUMS IS NOT PLAYING
             IF CURRENTLY PLAYING: ADD TO QUEUE
             IF NOT CURRENTLY PLAYING: PLAY
             
             */
            if(dist - countrySize < 10){
                
                countries[i].spawn.pop_back();
                
                int trackBDL = countries[i].track[0].x;
                int trackBDLnum = countries[i].track[0].y;
                
                switch (trackBDL) {
                    case 0:
                        nowPlayer.bassnow_v.push_back(countries[i].v_bass[trackBDLnum]);
                        break;
                    case 1:
                        nowPlayer.leadnow_v.push_back(countries[i].v_lead[trackBDLnum]);
                        break;
                    case 2:
                        nowPlayer.drumnow_v.push_back(countries[i].v_drum[trackBDLnum]);
                        break;
                }
                
            }
            
        }
        
        //------------------------------------------------PLAYBACK OF AUDIO END---------------------------------------------------------
    }
    
    ofPopMatrix();
    
    //--------------------------------STOP MATRIX PUSH
    
    
    camera.end();
    ofSetColor(0, 0, 0, 120);
    ofDrawRectangle(ofGetWidth()-200, 0, 200, 200);
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(nowPlayer.bassnow_v.size()) + " in bass queue", ofGetWidth()-190, 10);
    ofDrawBitmapString(ofToString(nowPlayer.leadnow_v.size()) + " in lead queue", ofGetWidth()-190, 30);
    ofDrawBitmapString(ofToString(nowPlayer.drumnow_v.size()) + " in drum queue", ofGetWidth()-190, 50);
    
    ofDrawBitmapString(ofToString(qSize) + " queue", ofGetWidth()-190, 90);
    
    //queue
    if(nowPlayer.bassnow_v.size() > 0){
        if(!nowPlayer.bassnow_v[0].isPlaying()){
            nowPlayer.bassnow_v[0].play();
        }
        if((nowPlayer.bassnow_v[0].getPosition() > 0.9)&&(nowPlayer.bassnow_v[0].isPlaying())){
            nowPlayer.bassnow_v[0].stop();
            cout << "change" << endl;
            nowPlayer.bassnow_v.erase(nowPlayer.bassnow_v.begin());
            qSize--;
        }
    }
    if(nowPlayer.leadnow_v.size() > 0){
        
        if(!nowPlayer.leadnow_v[0].isPlaying()){
            nowPlayer.leadnow_v[0].play();
        }
        if(nowPlayer.leadnow_v[0].getPosition() > 0.9){
            nowPlayer.leadnow_v[0].stop();
            nowPlayer.leadnow_v.erase(nowPlayer.leadnow_v.begin());
            qSize--;
        }
    }
    if(nowPlayer.drumnow_v.size() > 0){
        if(!nowPlayer.drumnow_v[0].isPlaying()){
            nowPlayer.drumnow_v[0].play();
        }
        if(nowPlayer.drumnow_v[0].getPosition() > 0.9){
            nowPlayer.drumnow_v[0].stop();
            nowPlayer.drumnow_v.erase(nowPlayer.drumnow_v.begin());
            qSize--;
        }
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'w')
    {
        ofVec3f currentPos = camera.getPosition();
        currentPos.y += 30;
        camera.setPosition(currentPos);
    }
    
    if (key == 's')
    {
        ofVec3f currentPos = camera.getPosition();
        currentPos.y -= 30;
        camera.setPosition(currentPos);
    }
    if (key == 'a')
    {
        ofVec3f currentPos = camera.getPosition();
        currentPos.x -= 30;
        camera.setPosition(currentPos);
    }
    
    if (key == 'd')
    {
        ofVec3f currentPos = camera.getPosition();
        currentPos.x += 30;
        camera.setPosition(currentPos);
    }
    //testing queues thngs
    if (key == 'l') {
        for(int i = 0; i < countries.size(); i++)
        {
            countries[i].spawn.clear();
            countries[i].b_spawn = true;
            qSize++;
        }
    }
}

void ofApp::moveCamera()
{
    int timer = ofGetElapsedTimef();
    
    if (timer % 15 == 0)
    {
        if (countryIndex >= countries.size()) {
            countryIndex = 0;
        }
        camera.setPosition(countries[countryIndex].point);
        camera.setDistance(2000);
        countryIndex++;
        
    }
}

void ofApp::loadCountries()
{
    // collect country names from directory
    string path = "countries";
    ofDirectory dir(path);
    dir.listDir();
    
    for (int i = 0; i < dir.size(); i++) {
        countryName = dir.getPath(i);
        countryName.erase(0, countryName.find("/")+1);
        //		countryName.erase(0, countryName.find("\\") + 1);
        countryNames.push_back(countryName);
    }
    //create new country for each country name - temp changed to 1 for experiments
    int numCountries = dir.size();
    for (int i = 0; i < numCountries; i++) {
        country newCountry(countryNames[i]);
        countries.push_back(newCountry);
    }
    countryIndex = 0;
}

void ofApp::loadGraphics()
{
    // set the centre point for the uk and a size for it to be
    centre.x = 825;
    centre.y = 1300;
    countrySize = 20;
    
    // load british flag and world map outline
    britFlag.load("flag.png");
    
    //mapOutline.load("WorldMapOutline.png");
    worldMapSVG.load("WorldMapSVG.svg");
}

void ofApp::loadCamera()
{
    ofPoint middle;
    
    camera.setDistance(2000);
    camera.setDrag(200);
    
    middle.x = worldMapSVG.getWidth() / 2;
    middle.y = worldMapSVG.getHeight() / 2;
    middle.z = 1000;
    
    camera.setPosition(middle);
}

void ofApp::loadBaseMusic()
{
    // assign backing track that will always be playing on loop with a volume of 50%
    baseMusic.load("p1.mp3");
    baseMusic.setLoop(true);
    baseMusic.play();
    baseMusic.setVolume(0.5f);
}
