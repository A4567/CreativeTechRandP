#include "country.h"



//--------------------------------------------------------------
//-------------Class Constructor for the countries--------------
country::country(string nameOfCountry) {
	//get the country name form the setup when the class is constructed
	countryName = nameOfCountry;

	//set a radius and colour -- not used any more i think
	radius = 25;
	r = ofRandom(30, 220);
	g = ofRandom(30, 220);
	b = ofRandom(30, 220);
	//set the spawning of the walkers to false preventing it from creating them straight awaay
	b_spawn = false;
	//load the music not image
	note.load("musicnotes/eighth-note.png");
	//set the paths for each type of track
	string path_b = "countries/" + countryName + "/bass/bass";
	string path_d = "countries/" + countryName + "/drums/drums";
	string path_l = "countries/" + countryName + "/lead/lead";
	//assign an image to each class
	flag.load("countries/" + countryName + "/flag.png");

	//assign each of the tracks of each type to a vector
	for (int i = 0; i < 1; i++) {
		ofSoundPlayer bass, lead, drums;
		bass.load(path_b + ofToString(i) + ".ogg");
		if (!bass.isLoaded())
		{
			bass.load(path_b + ofToString(i) + ".mp3");

		}

		//bass.setLoop(true);
		lead.load(path_l + ofToString(i) + ".ogg");

		if (!lead.isLoaded())
		{
			lead.load(path_l + ofToString(i) + ".mp3");

		}

		// lead.setLoop(true);

		drums.load(path_d + ofToString(i) + ".ogg");
		if (!drums.isLoaded())
		{
			drums.load(path_d + ofToString(i) + ".mp3");

		}

		// drums.setLoop(true);
		v_bass.push_back(bass);
		v_drum.push_back(drums);
		v_lead.push_back(lead);
	}
	//read text files to obtain start points for each country
	ofFile test;
	test.open("countries/" + countryName + "/startpoint.txt");
	ofBuffer buff(test);
	string coords = ofToString(buff);

	string xCoord = coords;
	xCoord.erase(xCoord.find(":"), xCoord.size());
	string yCoord = coords;
	yCoord.erase(0, yCoord.find(":") + 1);

	point.x = ofToFloat(xCoord);
	point.y = ofToFloat(yCoord);

}

country::~country() {

}

void country::draw(float index, ofVec3f target)
{
	//get the elasped time and set the speed of the walkers
	time = ofGetElapsedTimef();
	float speed = 0.01;

	//if spawn is true push the origin of the country to the spawn vector and set it back to false
	if (b_spawn)
	{
		spawn.push_back(point);
        int randBLD = ofRandom(3);
        
        ofVec2f newTrack(randBLD,0);
        track.push_back(newTrack);
		b_spawn = false;
	}

	//draw the flags over the origin points
	ofSetColor(255);
	flag.draw(point.x - flag.getWidth() / 20, point.y - flag.getHeight() / 20, flag.getWidth() / 10, flag.getHeight() / 10);

	//if the spawn vector is greater than 0 create a middle point -- this is wrong now, should be target - this will let us use ofLerp to setp towards the target and if the country is within a certain distance it will be removed from the vector preventing too many countries spawning spawns.
	if (spawn.size() > 0) {
		float spawnDist = ofDist(spawn[0].x, spawn[0].y, target.x, target.y);

		float xAmt, yAmt;
		xAmt = 0.005;
		yAmt = 0.005;

		spawn[0].x = ofLerp(spawn[0].x, target.x, xAmt);
		spawn[0].y = ofLerp(spawn[0].y, target.y, yAmt);



		ofSetColor(0, 0, 0);
		ofSetLineWidth(5);
		ofDrawLine(point, spawn[0]);


		ofSetColor(100, 255, 176);
		note.draw(spawn[0], note.getWidth() / 30, note.getHeight() / 30);
		if (spawnDist <= 20)
		{
			spawn.pop_back();
            track.pop_back();
		}
	}
}




