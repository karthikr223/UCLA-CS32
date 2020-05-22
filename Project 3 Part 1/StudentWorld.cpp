#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
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
		stars.push_back(new Star(randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1)));
	}
	player1 = new NachenBlaster(this);
    return GWSTATUS_CONTINUE_GAME;

	
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;

	vector<Actor*>::iterator it;
	it = stars.begin();
	int i = 0;
	while (it != stars.end()) {
		if (stars[i]->getX() == 0) {
			delete *it;
			it = stars.erase(it);
		}
		else {
			it++;
			i++;
		}
	}
	
	for (int i = 0; i < stars.size(); i++) {
	
			stars[i]->doSomething();
		
	}

	int y = randInt(0, 14);
	if (y == 0) {
		stars.push_back(new Star(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT-1)));
	}

	player1->doSomething();
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	if (stars.size() > 0) {
		vector<Actor*>::iterator it;
		it = stars.begin();
		while (it != stars.end()) {
			delete *it;
			it = stars.erase(it);
		}
		delete player1;
	}
}
