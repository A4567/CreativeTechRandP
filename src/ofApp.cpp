#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // set the centre point for the uk and a size for it to be
    centre.x = 825;
    centre.y = 1300;
    countrySize = 20;
//    assign backing track that will always be playing on loop with a volume of 50%
    noise.load("p1.mp3");
    noise.setLoop(true);
    noise.play();
    noise.setVolume(0.5f);
    // load british flag and world map outline
    britFlag.load("flag.png");
    //mapOutline.load("WorldMapOutline.png");
	worldMapSVG.load("WorldMapSVG.svg");
    // collect country names from directory
    string path = "countries";
    ofDirectory dir(path);
    dir.listDir();
    for(int i = 0; i < dir.size(); i++){
        countryName = dir.getPath(i);
        //countryName.erase(0, countryName.find("/")+1);
        countryName.erase(0, countryName.find("\\")+1);
        countryNames.push_back(countryName);
    }
    //create new country for each country name
    int numCountries = dir.size();
    for(int i = 0; i < numCountries; i++){
        country newCountry(countryNames[i]);
        countries.push_back(newCountry);
    }

	camera.setDistance(2000);
	camera.setDrag(200);
	middle.x = worldMapSVG.getWidth() / 2;
	middle.y = worldMapSVG.getHeight() / 2;
	middle.z = 1000;

	camera.setPosition(middle);
	
}

//--------------------------------------------------------------
void ofApp::update(){

    // get current time if time is a factor of 5 clear the spawn vector and set the spawn boolean to true if non of the tracks in it are playing
    randspawn = ofGetElapsedTimef();
    for(int i = 0; i < countries.size(); i ++){
        if((randspawn % 5 == 0)&&(countries[i].spawn.size() < 1)&&((!countries[i].v_drum[0].isPlaying())&&(!countries[i].v_bass[0].isPlaying())&&(!countries[i].v_lead[0].isPlaying()))){
            countries[i].spawn.clear();
            countries[i].b_spawn = true;
        }
    }

	if (camera.getX() < ofGetWidth() / 2) camera.setPosition(ofGetWidth() / 2, camera.getY(), camera.getZ());
	if (camera.getX() > worldMapSVG.getWidth() - ofGetWidth()/2) camera.setPosition(worldMapSVG.getWidth() - (ofGetWidth()/2), camera.getY(), camera.getZ());

	if (camera.getY() < ofGetHeight() / 1.75) camera.setPosition(camera.getX(), ofGetHeight() / 1.75, camera.getZ());
	if (camera.getY() > worldMapSVG.getHeight() - ofGetHeight()/1.75) camera.setPosition(camera.getX(), worldMapSVG.getHeight() - ofGetHeight() / 1.75, camera.getZ());



}

//--------------------------------------------------------------
void ofApp::draw(){

	camera.begin();


    //sets the colour of the countries on the map to white
    ofSetColor(255);
    //draw the map of the world
    //mapOutline.draw(0,0, mapOutline.getWidth(), mapOutline.getHeight());
	ofPushMatrix();
	ofScale(1, -1, -1);
	ofTranslate(0, -worldMapSVG.getHeight(), 0);
	worldMapSVG.draw();
	ofPopMatrix();

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
            
            if(dist - countrySize < 10){
                
                int rand;
                if((!countries[i].v_bass[0].isPlaying())&&(!countries[i].v_drum[0].isPlaying())&&(!countries[i].v_lead[0].isPlaying())){
                    rand = ofRandom(3);
                }else{
                    rand = 4;
                }
                //if the sample isnt playing play it and set the position to that of the backing track
                switch (rand) {
                    case 0:
                        if(!countries[i].v_bass[0].isPlaying()){
                            countries[i].v_bass[0].play();
                            countries[i].v_bass[0].setPosition(noise.getPosition());
                        }
                        break;
                    case 1:
                        if(!countries[i].v_drum[0].isPlaying()){
                            countries[i].v_drum[0].play();
                            countries[i].v_drum[0].setPosition(noise.getPosition());
                        }
                        break;
                    case 2:
                        if(!countries[i].v_lead[0].isPlaying()){
                            countries[i].v_lead[0].play();
                            countries[i].v_lead[0].setPosition(noise.getPosition());
                        }
                        break;
                        
                }
            }else{
                //if the distance is greater than 3 stop all the tracks -- needs work to make sure it doesnt trigger abrupt silence
                countries[i].v_bass[0].stop();
                countries[i].v_drum[0].stop();
                countries[i].v_lead[0].stop();
            }
        }
    }
    ofPopMatrix();	

	camera.end();

    
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
}

//--------------------------------------------------------------
//-------------Class Constructor for the countries--------------
country::country(string nameOfCountry){
    //get the country name form the setup when the class is constructed
    name = nameOfCountry;
    //set a radius and colour -- not used any more i think
    radius = 25;
    r = ofRandom(30,220);
    g = ofRandom(30,220);
    b = ofRandom(30,220);
    //set the spawning of the walkers to false preventing it from creating them straight awaay
    b_spawn = false;
    //load the music not image
    note.load("musicnotes/eighth-note.png");
    //set the paths for each type of track
    string path_b = "countries/" + name + "/bass/bass";
    string path_d = "countries/" + name + "/drums/drums";
    string path_l = "countries/" + name + "/lead/lead";
    //assign an image to each class
    flag.load("countries/"+name+"/flag.png");
    
    //assign each of the tracks of each type to a vector
    for(int i = 0; i < 1; i++){
        ofSoundPlayer bass,lead,drums;
		bass.load(path_b + ofToString(i) + ".ogg");
		if (!bass.isLoaded())
		{
			bass.load(path_b + ofToString(i) +".mp3");

		}

        //bass.setLoop(true);
		lead.load(path_l + ofToString(i) + ".ogg");

		if (!lead.isLoaded())
		{
			lead.load(path_l + ofToString(i) +".mp3");

		}

        // lead.setLoop(true);

		drums.load(path_d + ofToString(i) + ".ogg");
		if (!drums.isLoaded())
		{
			drums.load(path_d + ofToString(i) +".mp3");

		}

        // drums.setLoop(true);
        v_bass.push_back(bass);
        v_drum.push_back(drums);
        v_lead.push_back(lead);
    }
   //read text files to obtain start points for each country
    ofFile test;
    test.open("countries/"+name+"/startpoint.txt");
    ofBuffer buff(test);
    string coords = ofToString(buff);
    
    string xCoord = coords;
    xCoord.erase(xCoord.find(":"),xCoord.size());
    string yCoord = coords;
    yCoord.erase(0,yCoord.find(":")+1);
    
    point.x = ofToFloat(xCoord);
    point.y = ofToFloat(yCoord);
}

country::~country(){
    
}

void country::draw(float index, ofVec3f target){
    //get the elasped time and set the speed of the walkers
    time = ofGetElapsedTimef();
    float speed = 0.01;
    //if spawn is true push the origin of the country to the spawn vector and set it back to false
    if(b_spawn){
        spawn.push_back(point);
        b_spawn = false;
    }
    
    //draw the flags over the origin points
    ofSetColor(255);
    flag.draw(point.x-flag.getWidth()/20,point.y-flag.getHeight()/20,flag.getWidth()/10,flag.getHeight()/10);
    
    //if the spawn vector is greater than 0 create a middle point -- this is wrong now, should be target - this will let us use ofLerp to setp towards the target and if the country is within a certain distance it will be removed from the vector preventing too many countries spawning spawns.
    if(spawn.size() > 0){
        float spawnDist = ofDist(spawn[0].x, spawn[0].y, target.x, target.y);
        
        float xAmt,yAmt;
        xAmt = 0.005;
        yAmt = 0.005;
        
        spawn[0].x = ofLerp(spawn[0].x, target.x, xAmt);
        spawn[0].y = ofLerp(spawn[0].y, target.y, yAmt);

		ofSetColor(0, 0, 0);
		ofSetLineWidth(5);
		ofDrawLine(point, spawn[0]);


        ofSetColor(100,255,176);
        note.draw(spawn[0], note.getWidth()/30, note.getHeight()/30);
        if(spawnDist <= 20){
            spawn.pop_back();
        }
    }
}
