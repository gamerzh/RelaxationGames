#include "Automobile.h"
#include "MapNode.h"

Automobile* Automobile::create(Camera* camera, int type, int direction, float speed, float interval, Point pos) {
	auto automoblie = new Automobile();
	if (automoblie && automoblie->init(camera,type, direction, speed, interval,pos)) {
		automoblie->autorelease();
		return automoblie;
	}
	else {
		CC_SAFE_DELETE(automoblie);
		return NULL;
	}
}

bool Automobile::init(Camera* camera, int type, int direction, float speed, float interval, Point pos) {
	if (!Sprite::init()) {
		return false;
	}
	this->camera = camera;
	this->speed = speed*3;
	this->direction = direction;
	this->interval = interval*2;
	this->time = random(1,3);
	this->automobileType = type;
	this->postion = pos;
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	scheduleUpdate();
	return true;
}

string Automobile:: getFileNameByType(int type, int direction) {
	if (type == 1 && direction == 2) {
			return "car_1.png";
	}
	else if(type == 1 && direction == 1)
	{
		return "car_2.png";
	}
	else if (type == 2 && direction == 1)
	{
		return "car_2.png";
	}
	else {
		return "car_1.png";
	}
	
}


void Automobile::drawCar(int type, int direction) {
	auto car = Sprite::create(getFileNameByType(type, direction));
	car->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	car->setCameraMask(int(CameraFlag::USER1));
	car->setScale(0.7f);
	addChild(car);
	if (direction == 1) {
		car->setPosition(postion.x+car->getContentSize().width, floor(postion.y/default_tmx_height)*default_tmx_height+ default_tmx_height/6);
	}
	else {
		car->setPosition(postion.x -car->getContentSize().width, floor(postion.y / default_tmx_height)*default_tmx_height + default_tmx_height/6);
	}
	carList.push_back(car);
}

vector<Sprite*> Automobile::getCarList() {
	return carList;
}


void Automobile::update(float dt) {
	if (time >= interval) {
		time = 0;
		drawCar(automobileType, direction);
	}
	else {
		time += dt;
	}
	auto win = Director::getInstance()->getWinSize();
	if (carList.size() > 0) {
		for (auto var : carList) {
			Vec2 p = var->getPosition();
			if (direction == 1) {
				var->setPosition(p.x - speed, p.y);
			}
			else {
				var->setPosition(p.x + speed, p.y);
			}
		}
		vector<Sprite*>::iterator it;
		for (it = carList.begin(); it != carList.end();) {
			Sprite* car = *it;
			if ((direction == 1 && car->getPositionX() < camera->getPositionX() - car->getContentSize().width)
				|| (direction == 2 && car->getPositionX()> camera->getPositionX() + win.width + car->getContentSize().width)) {
				it = carList.erase(it);
				car->removeFromParent();
			}
			else
			{
				it++;
			}
		}
	}
	
}