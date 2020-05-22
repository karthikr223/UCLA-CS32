#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"


class Actor :public GraphObject {
public:
	Actor(int imageID, int startX, int startY, int direction, double size, int depth) : GraphObject(imageID, startX, startY, direction, size, depth) {}
	virtual void doSomething() = 0;
	virtual ~Actor() {
		return;
	}
private:
	
};

class Star:public Actor {
public:
	Star(int startX, int startY) :Actor(IID_STAR, startX, startY, 0, double(randInt(5, 50)) / 100, 3) {}
	void doSomething() {
		moveTo(getX() - 1, getY());
	}
private:

};

class NachenBlaster :public Actor {
public:
	NachenBlaster(StudentWorld* world) :Actor(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0), hp(50), cep(30), m_world(world) {}
	StudentWorld* getWorld() {
		return m_world;
	}
	void doSomething()
	{
		int ch;
		if (getWorld()->getKey(ch))
		{
			// user hit a key during this tick!
			switch (ch)
			{
			case KEY_PRESS_LEFT:
				if (getX() > 5) {
				moveTo(getX() - 6, getY());
				}
				break;
			case KEY_PRESS_RIGHT:
				if (getX() < VIEW_WIDTH-6) {
					moveTo(getX() + 6, getY());
				}
				break;
			case KEY_PRESS_DOWN:
				if (getY() > 5) {
					moveTo(getX(), getY() - 6);
				}
				break;
			case KEY_PRESS_UP:
				if (getY() < VIEW_HEIGHT - 6) {
					moveTo(getX(), getY() + 6);
				}
				break;
			}
		}
	}
private:
	int hp;
	int cep;
	StudentWorld* m_world;
};

#endif // ACTOR_H_

