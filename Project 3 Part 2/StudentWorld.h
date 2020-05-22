#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>
class Actor;
class NachenBlaster;
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
	~StudentWorld() {
		cleanUp();
	}
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	Actor* getOneCollidingAlien(const Actor* a)const ;
	// If the player has collided with a, return a pointer to the player;
	// otherwise, return a null pointer.
	NachenBlaster* getCollidingPlayer(const Actor* a) const;

	void recordAlienDestroyed() {
		totalAliens -= 1;
	}
	void recordAlienKilled() {
		aliensKilled += 1;
		totalAliens -= 1;
	}
	void addActor(Actor* a) {
		actors.push_back(a);
	}
	NachenBlaster* getPlayer() const {
		return player1;
	}

	

private:
	vector<Actor*> actors;
	NachenBlaster* player1;
	double euclidianDistance(double x1, double y1, double x2, double y2)const;
	int aliensKilled;
	int totalAliens;
};

#endif // STUDENTWORLD_H_
