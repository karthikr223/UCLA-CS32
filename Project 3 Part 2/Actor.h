#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
const int HIT_BY_SHIP = 0;
const int HIT_BY_PROJECTILE = 1;

class StudentWorld;
class Cabbage;

class Actor :public GraphObject {
public:
	Actor(StudentWorld* w,int imageID, int startX, int startY, int direction, double size, int depth) : GraphObject(imageID, startX, startY, direction, size, depth), m_world(w) {}
	virtual void doSomething() = 0;

	virtual void DeathSequence() {
		return;
	}

	StudentWorld* getWorld() const {
		return m_world;
	}
	virtual bool isAlive() const = 0;
	virtual void sufferDamage(double amt) {
		return;
	}
	virtual bool collidableWithPlayerFiredProjectile() const {
		return false;
	}
private:
	StudentWorld* m_world;
	
};

class Star:public Actor {
public:
	Star(StudentWorld* w, int startX, int startY) :Actor(w, IID_STAR, startX, startY, 0, double(randInt(5, 50)) / 100, 3) {}
	void doSomething() {
		moveTo(getX() - 1, getY());
	}
	bool isAlive() const {
		if (getX() < 0) {
			return false;
		}
		return true;
	}

private:

};

class Goodie : public Actor
{
public:
	Goodie(StudentWorld* w, double startX, double startY, int imageID) :Actor(w, imageID, startX, startY, 0, 0.5, 1), aliveStatus(true) {}
	void move() {	
		moveTo(getX() - 0.75, getY() - 0.75);
	}
	bool isAlive() const {
		return aliveStatus;
	}
	void setAliveStatus(bool a) {
		aliveStatus = a;
	}
private:
	bool aliveStatus;
};

class ExtraLifeGoodie : public Goodie
{
public:
	ExtraLifeGoodie(StudentWorld* w, double startX, double startY) :Goodie(w, startX, startY, IID_LIFE_GOODIE) {}
	void doSomething();
};

class RepairGoodie : public Goodie
{
public:
	RepairGoodie(StudentWorld* w, double startX, double startY) : Goodie(w, startX, startY, IID_REPAIR_GOODIE) {}
	void doSomething();
};

class TorpedoGoodie : public Goodie
{
public:
	TorpedoGoodie(StudentWorld* w, double startX, double startY) : Goodie(w, startX, startY, IID_TORPEDO_GOODIE) {}
	void doSomething();
};

class DamageableObject : public Actor
{
public:
	DamageableObject(StudentWorld* w, int imageID, double startX, double startY,
		int startDir, double size, int depth, double hitPoints) :Actor(w, imageID, startX, startY, startDir, size, depth), hp(hitPoints) {}

	// How many hit points does this actor have left?
	double hitPoints() const {
		return hp;
	}

	// Increase this actor's hit points by amt.
	void increaseHitPoints(double amt) {
		hp += amt;
	}

	// This actor suffers an amount of damage caused by being hit by either
	// a ship or a projectile (see constants above).
	void sufferDamage(double amt) {
		hp -= amt;
	}
private:
	double hp;
};

class Alien : public DamageableObject
{
public:
	Alien(StudentWorld* w, double startX, double startY, int imageID,
		double hitPoints, int flightpath, int yDir, double speed) :DamageableObject(w, imageID, startX, startY, 0, 1.5, 1, hitPoints), m_speed(speed),m_Ydir(yDir),m_flightpath(flightpath)  {}

	bool collidableWithPlayerFiredProjectile() const {
		return true;
	}
    //moves the alien as per its y direction and speed
	void move() {
		if (m_Ydir == 2)
			moveTo(getX() - m_speed, getY() + m_speed);
		if (m_Ydir == 1)
			moveTo(getX() - m_speed, getY());
		if (m_Ydir == 0)
			moveTo(getX() - m_speed, getY() - m_speed);
	}

	// Set the alien's y direction.
	void setYdirection(int dy) {
		m_Ydir = dy;
	}

	// Set the alien's speed.
	void setSpeed(double speed) {
		m_speed = speed;
	}

	int getflightpath() const {
		return m_flightpath;
	}

	void setFlightPath(int a) {
		m_flightpath = a;
	}

private:
	double m_speed;
	int m_flightpath;
	int m_Ydir;
};

class Smallgon : public Alien
{
public:
	Smallgon(StudentWorld* w, double startX, double startY);
	bool isAlive() const {
		if (hitPoints() <= 0)
			return false;
		else
			return true;
	}
	void doSomething();
	void DeathSequence();
};

class Smoregon :public Alien{
public:
	Smoregon(StudentWorld* w, double startX, double startY);
	bool isAlive() const {
		if (hitPoints() <= 0)
			return false;
		else
			return true;
	}
	void doSomething();
	void DeathSequence();
};

class Snagglegon : public Alien {
public:
	Snagglegon(StudentWorld* w, double startX, double startY);
	bool isAlive() const {
		if (hitPoints() <= 0)
			return false;
		else
			return true;
	}
	void doSomething();
	void DeathSequence();
};
class NachenBlaster :public DamageableObject {
public:
	NachenBlaster(StudentWorld* world) :DamageableObject(world, IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, 50), cep(30), torpedoes(0) {}

	void doSomething();
	
	bool isAlive() const {
		if (hitPoints() <= 0)
			return false;
		return true;
	}
	double getCEP() const {
		return cep;
	}

	int getTorpedoes() const{
		return torpedoes;
	}

	void increaseTorpedoes(int a) {
		torpedoes += a;
	}

private:
	double cep;
	int torpedoes;
};

class Projectile : public Actor {
public:
	Projectile(StudentWorld*w, int imageID, int startX, int startY, int direction, double size, double depth) :Actor(w, imageID, startX, startY, direction, size, depth), aliveStatus(true) {}

	bool isAlive() const {
		return aliveStatus;
	}
	void setAliveStatus(bool a) {
		aliveStatus = a;
	}
private:
	bool aliveStatus;
};
class Cabbage : public Projectile {
public:
	Cabbage(StudentWorld* w, int startX, int startY) :Projectile(w, IID_CABBAGE, startX, startY, 0, 0.5, 1) {}
	void doSomething();
};

class Turnip :public Projectile {
public:
	Turnip(StudentWorld* w, double startX, double startY) :Projectile(w, IID_TURNIP, startX, startY, 0, 0.5, 1) {}
	void doSomething();
};

class Torpedo : public Projectile
{
public:
	Torpedo(StudentWorld* w, double startX, double startY, int imageDir) :Projectile(w, IID_TORPEDO, startX, startY, imageDir, 0.5, 1) {}
};

class PlayerLaunchedTorpedo : public Torpedo
{
public:
	PlayerLaunchedTorpedo(StudentWorld* w, double startX, double startY) :Torpedo(w, startX, startY, 0) {}
	void doSomething();
};

class AlienLaunchedTorpedo : public Torpedo
{
public:
	AlienLaunchedTorpedo(StudentWorld* w, double startX, double startY) :Torpedo(w, startX, startY, 180) {}
	void doSomething();
};


class Explosion : public Actor
{
public:
	Explosion(StudentWorld* w, double startX, double startY) :Actor(w, IID_EXPLOSION, startX, startY, 0, 1, 0), lifespan(4) {}
	void doSomething() {
		if (isAlive()) {
			setSize(getSize()*1.5);
			lifespan -= 1;
		}
	}
	bool isAlive() const {
		if (lifespan > 0)
			return true;
		return false;
	}
private:
	int lifespan;
};

#endif // ACTOR_H_
