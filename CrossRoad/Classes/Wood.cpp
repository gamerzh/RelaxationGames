#include "Wood.h"
#include "MapNode.h"
#include "GeometryUtils.h"

Wood * Wood::create(Camera* ca, int type, int direction, float time, Point position)
{
	Wood* woo = new Wood();
	if (woo && woo->init(ca, type, direction, time, position)) {
		woo->autorelease();
		return woo;
	}
	else {
		CC_SAFE_DELETE(woo);
		return NULL;
	}
}

bool Wood::init(Camera* ca, int type, int direction, float time, Point position)
{
	if (!Sprite::init()) {
		return false;
	}
	this->position = position;
	this->woodType = type;
	this->woodDir = direction;
	this->woodTime = time * GeometryUtils::randomFloat(1,2);
	this->myCamera = ca;
	passtime = woodTime;
	initSpeed();
	//initWithFile(getFileNameByType(type));
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	scheduleUpdate();
	return true;
}


//  1代表短模板 2代表长木板 3代表金币 4代表火车提示灯 5代表荷叶
std::string Wood::getFileNameByType(int type) {
	//log("HHHHHHHHH %d", type);
	if (type == ObjectType::wood_long) {
		return "wood_2.png";
	}
	else if (type == ObjectType::leaf) {
		return "leaf.png";
	}
	else {
		return "wood_1.png";
	}
}

void Wood::initSpeed() {
	if (woodType != ObjectType::leaf) {
		if (woodDir == DirectionType::move_left) {
			this->woodSpeed = -GeometryUtils::randomFloat(1, 2);
		}
		else {
			this->woodSpeed = GeometryUtils::randomFloat(1, 2);
		}
	}
	else {
		this->woodSpeed = 0;//荷叶不具备移动的能力
	}
}

float Wood::getSpeedX() {
	return this->woodSpeed;
}



void Wood::drawWoods() {
	auto car = Sprite::create(getFileNameByType(woodType));
	car->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	car->setCameraMask(int(CameraFlag::USER1));
	car->setPosition(GeometryUtils::transitionObjectVec2(position, getMapIndex()).x,
		GeometryUtils::transitionObjectVec2(position, getMapIndex()).y + default_tmx_height / 10);
	addChild(car);
	if (woodType != ObjectType::leaf) {
		if (woodDir == DirectionType::move_left) {
			car->setPosition(myCamera->getPositionX() + win.width + car->getContentSize().width, (floor(position.y / default_tmx_height) + (getMapIndex() - 1)*defult_tmx_y_num)*default_tmx_height + default_tmx_height / 8);
		}
		else {
			car->setPosition(myCamera->getPositionX() - car->getContentSize().width, (floor(position.y / default_tmx_height) + (getMapIndex() - 1)*defult_tmx_y_num)*default_tmx_height + default_tmx_height / 8);
		}
	}
	boardList.push_back(car);
}


std::vector<Sprite*> Wood::getBoardList() {
	return boardList;
}

void Wood::update(float dt) {
	if (woodTime == 0) {
		drawWoods();
		woodTime = -1;
	}
	else if(woodTime > 0){
		if (passtime >= woodTime) {
			passtime = passtime - woodTime;
			drawWoods();
		}
		else {
			passtime += dt;
		}
	}
	

	for (auto woo : boardList)
	{
		if (woodType != ObjectType::leaf) {
			woo->setPosition(woo->getPositionX() + getSpeedX(), woo->getPositionY());
		}
	}

	vector<Sprite*>::iterator it;
	for (it = boardList.begin(); it != boardList.end();) {
		Sprite* car = *it;
		if ((woodDir == DirectionType::move_left && car->getPositionX() < myCamera->getPositionX() - car->getContentSize().width)
			|| (woodDir == DirectionType::move_rigth && car->getPositionX() > myCamera->getPositionX() + win.width + car->getContentSize().width)) {
			it = boardList.erase(it);
			car->removeFromParent();
		}
		else
		{
			it++;
		}
	}

}