#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <cmath>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
}

int StudentWorld::init()
{
	for (int i = 0; i < 30; i++) {
		actors.push_back(new Star(this,randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1)));
	}
	player1 = new NachenBlaster(this);
	aliensKilled = 0;
	totalAliens = 0;
    return GWSTATUS_CONTINUE_GAME;

	
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;

	//all actors call doSomething for the current game tick
	for (int i = 0; i < actors.size(); i++) {
	
		actors[i]->doSomething();
		
	}
	player1->doSomething();
	
	if (!player1->isAlive()) {
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}
	//if the player has killed the appropriate number of aliens end level
	else if (aliensKilled >= (6 + (4 * getLevel()))) {
		playSound(SOUND_FINISHED_LEVEL);
		return GWSTATUS_FINISHED_LEVEL;
	}

	//remove all dead actors
	vector<Actor*>::iterator it;
	it = actors.begin();
	int i = 0;
	while (it != actors.end()) {
		if (actors[i]->isAlive() == false) {
			delete *it;
			it = actors.erase(it);
		}
		else {
			it++;
			i++;
		}
	}

	//introducing new stars
	int y = randInt(0, 14);
	if (y == 0) {
		actors.push_back(new Star(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT-1)));
	}
	 
	//introducing new aliens
	if (totalAliens < min(int(4 + (0.5*getLevel())), int(6 + (4 * getLevel()) - aliensKilled))) {
		int s1 = 60;
		int s2 = 20 + getLevel() * 5;
		int s3 = 5 + getLevel() * 10;
		int s = s1 + s2 + s3;
		int r = randInt(1, s);
		if (r <= s1) {
			actors.push_back(new Smallgon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
			totalAliens++;
		}
		else if (r > s1 && r <= s1 + s2) {
			actors.push_back(new Smoregon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
			totalAliens++;
		}
		else {
			actors.push_back(new Snagglegon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
			totalAliens++;
		}

	}
	//scoreboard
	setGameStatText("Lives:  " + to_string(getLives()) + "  Health:  " + to_string(int(((getPlayer()->hitPoints())/50)*100)) + "%  Score:  " + to_string(getScore()) + "  Level:  " + to_string(getLevel()) + "  Cabbages:  " + to_string(int(((getPlayer()->getCEP())/30)*100)) + "%  Torpedoes:  " + to_string(getPlayer()->getTorpedoes()));
	

	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	if (actors.size() > 0) {
		vector<Actor*>::iterator it;
		it = actors.begin();
		while (it != actors.end()) {
			delete *it;
			it = actors.erase(it);
		}
		delete player1;
	}
}

Actor* StudentWorld::getOneCollidingAlien(const Actor* a) const {
	for (int i = 0; i < actors.size(); i++) {
		if (euclidianDistance(a->getX(), a->getY(), actors[i]->getX(), actors[i]->getY()) < (0.75*(a->getRadius() + actors[i]->getRadius()))) {
			if (actors[i]->collidableWithPlayerFiredProjectile()) {
				return actors[i];
			}
		}

	}
	return nullptr;
}

double StudentWorld::euclidianDistance(double x1, double y1, double x2, double y2) const{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

NachenBlaster* StudentWorld::getCollidingPlayer(const Actor* a) const {
	if (euclidianDistance(a->getX(), a->getY(), player1->getX(), player1->getY()) < (0.75*(a->getRadius() + player1->getRadius()))) 
		return player1;
	return nullptr;
}


