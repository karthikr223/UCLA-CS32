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

private:
	vector<Actor*> stars;
	NachenBlaster* player1;
};

#endif // STUDENTWORLD_H_
