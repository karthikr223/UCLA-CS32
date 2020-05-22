#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp



void NachenBlaster::doSomething() {
	if (isAlive()) {
		if (cep <= 29)
			cep += 1;
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
				if (getX() < VIEW_WIDTH - 6) {
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
			case KEY_PRESS_SPACE:
				if (cep >= 5) {
					getWorld()->addActor(new Cabbage(getWorld(),getX() + 12, getY()));
					getWorld()->playSound(SOUND_PLAYER_SHOOT);
					cep -= 5;
				}
				break;
			case KEY_PRESS_TAB:
				if (torpedoes >= 1) {
					getWorld()->addActor(new PlayerLaunchedTorpedo(getWorld(), getX() + 12, getY()));
					getWorld()->playSound(SOUND_TORPEDO);
					torpedoes -= 1;
				}
			}
		}
	}
	else
		return;
}


Smallgon::Smallgon(StudentWorld* w, double startX, double startY) :Alien(w, startX, startY, IID_SMALLGON, 5 * (1 + (w->getLevel() - 1)*0.1), 0, 0, 2) {}

void Smallgon::doSomething() {
	if (!isAlive())
		return;
	else {
		if (getX() < 0) {
			increaseHitPoints(-hitPoints());
			getWorld()->recordAlienDestroyed();
			return;
		}
		NachenBlaster* n = getWorld()->getCollidingPlayer(this);
		if (n != nullptr) {
			n->sufferDamage(5);
			DeathSequence();
		}
		if (getY() >= VIEW_HEIGHT - 1) {
			setYdirection(0);
		}
		else if (getY() <= 0) {
			setYdirection(2);
		}
		else if (getflightpath() == 0) {
			setYdirection(randInt(0, 2));
			setFlightPath(randInt(1, 32));
		}

		if (getX() > getWorld()->getPlayer()->getX() && getY() >= getWorld()->getPlayer()->getY() - 4 && getY() <= getWorld()->getPlayer()->getY() + 4) {
			if (randInt(1, (20 / getWorld()->getLevel()) + 5) == 1) {
				getWorld()->addActor(new Turnip(getWorld(), getX() - 14, getY()));
				getWorld()->playSound(SOUND_ALIEN_SHOOT);
				return;
			}
		}
		move();
		setFlightPath(getflightpath() - 1);

		NachenBlaster* m = getWorld()->getCollidingPlayer(this);
		if (m != nullptr) {
			m->sufferDamage(5);
			DeathSequence();
		}
	}
}

void Smallgon::DeathSequence() {
	getWorld()->recordAlienKilled();
	increaseHitPoints(-hitPoints());
	getWorld()->increaseScore(250);
	getWorld()->playSound(SOUND_DEATH);
	getWorld()->addActor(new Explosion(getWorld(), this->getX(), this->getY()));
}

Smoregon::Smoregon(StudentWorld* w, double startX, double startY) :Alien(w, startX, startY, IID_SMOREGON, 5 * (1 + (w->getLevel() - 1)*0.1), 0, 0, 2) {}

void Smoregon::doSomething() {
	if (!isAlive())
		return;
	else {
		if (getX() < 0) {
			increaseHitPoints(-hitPoints());
			getWorld()->recordAlienDestroyed();
			return;
		}
		NachenBlaster* n = getWorld()->getCollidingPlayer(this);
		if (n != nullptr) {
			n->sufferDamage(5);
			DeathSequence();
		}
		if (getY() >= VIEW_HEIGHT - 1) {
			setYdirection(0);
		}
		else if (getY() <= 0) {
			setYdirection(2);
		}
		else if (getflightpath() == 0) {
			setYdirection(randInt(0, 2));
			setFlightPath(randInt(1, 32));
		}

		if (getX() > getWorld()->getPlayer()->getX() && getY() >= getWorld()->getPlayer()->getY() - 4 && getY() <= getWorld()->getPlayer()->getY() + 4) {
			if (randInt(1, (20 / getWorld()->getLevel()) + 5) == 1) {
				getWorld()->addActor(new Turnip(getWorld(), getX() - 14, getY()));
				getWorld()->playSound(SOUND_ALIEN_SHOOT);
				return;
			}
			if (randInt(1, (20 / getWorld()->getLevel()) + 5) == 1) {
				setYdirection(1);
				setFlightPath(VIEW_WIDTH);
				setSpeed(5);
			}
		}
		move();
		setFlightPath(getflightpath() - 1);

		NachenBlaster* m = getWorld()->getCollidingPlayer(this);
		if (m != nullptr) {
			m->sufferDamage(5);
			DeathSequence();
		}
	}
}

void Smoregon::DeathSequence() {
	getWorld()->recordAlienKilled();
	increaseHitPoints(-hitPoints());
	getWorld()->increaseScore(250);
	getWorld()->playSound(SOUND_DEATH);
	getWorld()->addActor(new Explosion(getWorld(), this->getX(), this->getY()));
	if (randInt(1, 3) == 1) {
		if (randInt(1, 2) == 1) {
			getWorld()->addActor(new RepairGoodie(getWorld(), this->getX(), this->getY()));
		}
		else
			getWorld()->addActor(new TorpedoGoodie(getWorld(), this->getX(), this->getY()));
	}
}

Snagglegon::Snagglegon(StudentWorld* w, double startX, double startY):Alien(w, startX, startY, IID_SNAGGLEGON, 10 * (1 + (w->getLevel() - 1)*0.1), 0, 0, 1.75) {}

void Snagglegon::doSomething() {
	if (!isAlive())
		return;
	else {
		if (getX() < 0) {
			increaseHitPoints(-hitPoints());
			getWorld()->recordAlienDestroyed();
			return;
		}
		NachenBlaster* n = getWorld()->getCollidingPlayer(this);
		if (n != nullptr) {
			n->sufferDamage(15);
			DeathSequence();
		}
		if (getY() >= VIEW_HEIGHT - 1) {
			setYdirection(0);
		}
		else if (getY() <= 0) {
			setYdirection(2);
		}
		if (getX() > getWorld()->getPlayer()->getX() && getY() >= getWorld()->getPlayer()->getY() - 4 && getY() <= getWorld()->getPlayer()->getY() + 4) {
			if (randInt(1, (15 / getWorld()->getLevel()) + 10) == 1) {
				getWorld()->addActor(new AlienLaunchedTorpedo(getWorld(), getX() - 14, getY()));
				getWorld()->playSound(SOUND_TORPEDO);
				return;
			}
		}
		move();
		NachenBlaster* m = getWorld()->getCollidingPlayer(this);
		if (m != nullptr) {
			m->sufferDamage(15);
			DeathSequence();
		}
	}
}
void Snagglegon::DeathSequence() {
	getWorld()->recordAlienKilled();
	increaseHitPoints(-hitPoints());
	getWorld()->increaseScore(1000);
	getWorld()->playSound(SOUND_DEATH);
	getWorld()->addActor(new Explosion(getWorld(), this->getX(), this->getY()));
	if (randInt(1, 6) == 1) {
		getWorld()->addActor(new ExtraLifeGoodie(getWorld(), this->getX(), this->getY()));
	}
}

void Turnip::doSomething() {	
	if (isAlive()) {
		if (getX() >= 0) {
			NachenBlaster* a = getWorld()->getCollidingPlayer(this);
			if (a != nullptr) {
				a->sufferDamage(2);
				getWorld()->playSound(SOUND_BLAST);
				setAliveStatus(false);
				return;
			}
			moveTo(getX() -6, getY());
			setDirection(getDirection() + 20);
			NachenBlaster* b = getWorld()->getCollidingPlayer(this);
			if (b != nullptr) {
				b->sufferDamage(2);
				getWorld()->playSound(SOUND_BLAST);
				setAliveStatus(false);
				return;
			}
		}
		else {
			setAliveStatus(false);
			return;
		}
	}
	else
		return;
}

void AlienLaunchedTorpedo::doSomething() {
	if (isAlive()) {
		if (getX() >= 0) {
			NachenBlaster* a = getWorld()->getCollidingPlayer(this);
			if (a != nullptr) {
				a->sufferDamage(8);
				getWorld()->playSound(SOUND_BLAST);
				setAliveStatus(false);
				return;
			}
			moveTo(getX() - 8, getY());
			NachenBlaster* b = getWorld()->getCollidingPlayer(this);
			if (b != nullptr) {
				b->sufferDamage(8);
				getWorld()->playSound(SOUND_BLAST);
				setAliveStatus(false);
				return;
			}
		}
		else {
			setAliveStatus(false);
			return;
		}
	}
	else
		return;
}

void Cabbage::doSomething() {
	if (isAlive()) {
		if (getX() < VIEW_WIDTH) {
			Actor* a = getWorld()->getOneCollidingAlien(this);
			if (a != nullptr) {
				a->sufferDamage(2);
				if (!a->isAlive()) {
					a->DeathSequence();
				}
				else {
					getWorld()->playSound(SOUND_BLAST);
				}
				setAliveStatus(false);
				return;
			}
			moveTo(getX() + 8, getY());
			setDirection(getDirection() + 20);
			Actor* b = getWorld()->getOneCollidingAlien(this);
			if (b != nullptr) {
				b->sufferDamage(2);
				if (!b->isAlive()) {
					b->DeathSequence();
				}
				else {
					getWorld()->playSound(SOUND_BLAST);
				}
				setAliveStatus(false);
				return;
			}
		}
		else {
			setAliveStatus(false);
			return;
		}
	}
	else
		return;
}


void PlayerLaunchedTorpedo::doSomething() {
	if (isAlive()) {
		if (getX() <VIEW_WIDTH) {
			Actor* a = getWorld()->getOneCollidingAlien(this);
			if (a != nullptr) {
				a->sufferDamage(8);
				if (!a->isAlive()) {
					a->DeathSequence();
				}
				else {
					getWorld()->playSound(SOUND_BLAST);
				}
				setAliveStatus(false);
				return;
			}
			moveTo(getX() + 8, getY());
			Actor* b = getWorld()->getOneCollidingAlien(this);
			if (b != nullptr) {
				b->sufferDamage(8);
				if (!b->isAlive()) {
					b->DeathSequence();
				}
				else {
					getWorld()->playSound(SOUND_BLAST);
				}
				setAliveStatus(false);
				return;
			}
		}
		else {
			setAliveStatus(false);
			return;
		}
	}
	else
		return;
}

void ExtraLifeGoodie::doSomething() {
	if (!isAlive())
		return;
	else {
		if (getX() < 0 || getY() < 0) {
			setAliveStatus(false);
			return;
		}
		NachenBlaster* a = getWorld()->getCollidingPlayer(this);
		if (a != nullptr) {
			getWorld()->increaseScore(100);
			setAliveStatus(false);
			getWorld()->playSound(SOUND_GOODIE);
			getWorld()->incLives();
			return;
		}
		move();
		NachenBlaster* b = getWorld()->getCollidingPlayer(this);
		if (b != nullptr) {
			getWorld()->increaseScore(100);
			setAliveStatus(false);
			getWorld()->playSound(SOUND_GOODIE);
			getWorld()->incLives();
			return;
		}
	}
}


void RepairGoodie::doSomething() {
	if (!isAlive())
		return;
	else {
		if (getX() < 0 || getY() < 0) {
			setAliveStatus(false);
			return;
		}
		NachenBlaster* a = getWorld()->getCollidingPlayer(this);
		if (a != nullptr) {
			getWorld()->increaseScore(100);
			setAliveStatus(false);
			getWorld()->playSound(SOUND_GOODIE);
			if (getWorld()->getPlayer()->hitPoints() > 40) {
				getWorld()->getPlayer()->increaseHitPoints(50 - (getWorld()->getPlayer()->hitPoints()));
			}
			else
				getWorld()->getPlayer()->increaseHitPoints(10);
			return;
		}
		move();
		NachenBlaster* b = getWorld()->getCollidingPlayer(this);
		if (b != nullptr) {
			getWorld()->increaseScore(100);
			setAliveStatus(false);
			getWorld()->playSound(SOUND_GOODIE);
			if (getWorld()->getPlayer()->hitPoints() > 40) {
				getWorld()->getPlayer()->increaseHitPoints(50 - (getWorld()->getPlayer()->hitPoints()));
			}
			else
				getWorld()->getPlayer()->increaseHitPoints(10);
			return;
		}
	}
}

void TorpedoGoodie::doSomething() {
	if (!isAlive())
		return;
	else {
		if (getX() < 0 || getY() < 0) {
			setAliveStatus(false);
			return;
		}
		NachenBlaster* a = getWorld()->getCollidingPlayer(this);
		if (a != nullptr) {
			getWorld()->increaseScore(100);
			setAliveStatus(false);
			getWorld()->playSound(SOUND_GOODIE);
			getWorld()->getPlayer()->increaseTorpedoes(5);
			return;
		}
		move();
		NachenBlaster* b = getWorld()->getCollidingPlayer(this);
		if (b != nullptr) {
			getWorld()->increaseScore(100);
			setAliveStatus(false);
			getWorld()->playSound(SOUND_GOODIE);
			getWorld()->getPlayer()->increaseTorpedoes(5);
			return;
		}
	}
}

