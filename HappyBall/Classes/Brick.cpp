#include "Brick.h"
#include "GameLayer.h"
#include "GeometryTools.h"
#include "UserData.h"
USING_NS_CC;
using namespace std;

Brick* Brick::create(int frame, int level) {
	auto brick = new Brick();
	if (brick && brick->init(frame, level)) {
		brick->autorelease();
		return brick;
	}
	else {
		CC_SAFE_DELETE(brick);
		return nullptr;
	}
}

bool Brick::init(int frame, int level)
{
	if (!Sprite::init()) {
		return false;
	}
	loadBrickFile();
	setFrameIndex(frame);
	updateBrickShape(level);
	createOutAnglesFrame();
	createDanAnglesFrame();
	//brickDebug();
	//brickOpacity(100);
	scheduleUpdate();
	return true;
}

void Brick::loadBrickFile() {
	auto brick = CSLoader::createNode(UserData::getInstance()->getBrickDataFromCsb());
	brick->setPosition(0, 0);
	this->addChild(brick);
	heroTimeLine = CSLoader::createTimeline(UserData::getInstance()->getBrickDataFromCsb(), "qqdh.csb");
	heroTimeLine->play("rotate", false);
	brick->runAction(heroTimeLine);
	part1 = brick->getChildByName("kl")->getChildByName("o1zj");
	part2_a = brick->getChildByName("kl")->getChildByName("o2zj");
	part2_b = brick->getChildByName("kl")->getChildByName("o2zjf");
	part3_a = brick->getChildByName("kl")->getChildByName("o3zj");
	part3_b = brick->getChildByName("kl")->getChildByName("o3zjf");
	part4_a = brick->getChildByName("kl")->getChildByName("o4zj");
	part4_b = brick->getChildByName("kl")->getChildByName("o4zjf");
	part5_a = brick->getChildByName("kl")->getChildByName("o5zj");
	part5_b = brick->getChildByName("kl")->getChildByName("o5zjf");
	part6_a = brick->getChildByName("kl")->getChildByName("o6zj");
	part6_b = brick->getChildByName("kl")->getChildByName("o6zjf");
	part7_a = brick->getChildByName("kl")->getChildByName("o7zj");
	part7_b = brick->getChildByName("kl")->getChildByName("o7zjf");
	part8_a = brick->getChildByName("kl")->getChildByName("o8zj");
	part8_b = brick->getChildByName("kl")->getChildByName("o8zjf");
}

void Brick::createSafeShape() {
	bool condition = true;
	int cur = 0;
	while (condition)
	{
		cur = random(0, 120);
		bool find = false;
		for (auto var : outList) {
			auto start = var.startFrame;
			auto end = var.endFrame;
			if ((start <= cur && end >= cur)
				|| (start > end && ((cur >= start && cur <= BRICK_ANIM_NUM) || (cur >= 0 && cur <= end)))) {
				find = true;
			}
		}
		if (find) {
			condition = true;
		}
		else {
			condition = false;
		}
	}
	setFrameIndex(cur);
}

void Brick::updateBrickShape(int level) {
	//由于素材的限定模块9和10被强制作为出口
	outArea.push_back(9);
	outArea.push_back(10);
	//outArea.push_back(1);
	//难度为0设置0块红色区域,出口加1个,难度为1设置1块红色区域,出口加1个,难度为2设置2块红色区域,出口加2个
	std::vector<int> origin = { 1,2,3,4,5,6,7,8 };
	if (level == 0) {
		int out1 = randomAreaModule(origin);
		outArea.push_back(out1);
	}
	else if (level == 1) {
		int dan1 = randomAreaModule(origin);
		int out1 = randomAreaModule(origin);
		outArea.push_back(out1);
		danArea.push_back(dan1);
	}
	else if (level == 2) {
		int dan1 = randomAreaModule(origin);
		int dan2 = randomAreaModule(origin);
		int out1 = randomAreaModule(origin);
		int out2 = randomAreaModule(origin);
		danArea.push_back(dan1);
		danArea.push_back(dan2);
		outArea.push_back(out1);
		outArea.push_back(out2);
	}
	else if (level == 3) {
		int dan1 = randomAreaModule(origin);
		int dan2 = randomAreaModule(origin);
		int dan3 = randomAreaModule(origin);
		int out1 = randomAreaModule(origin);
		//int out2 = randomAreaModule(origin);
		danArea.push_back(dan1);
		danArea.push_back(dan2);
		danArea.push_back(dan3);
		outArea.push_back(out1);
		//outArea.push_back(out2);
	}
	for (auto ou:outArea)
	{
		log("out area id = %d", ou);
		controlModule(ou,0);
	}
	for (auto dn : danArea)
	{
		log("dangrous area id = %d", dn);
		controlModule(dn, 1);
	}
}

void Brick::removeDangousArea() {
	for (auto dn : danArea)
	{
		controlModule(dn, 2);
	}
	danArea.clear();
	danList.clear();
}

 int Brick::randomAreaModule(std::vector<int>& origin) {
	int ran = random(0, (int)origin.size()-1);
	int result = origin.at(ran);
	std::vector<int> ::iterator it;
	for (it = origin.begin(); it != origin.end();) {
		if (*it == result) {
			it = origin.erase(it);
		}
		else {
			++it;
		}
	}
	return result;
}

 void Brick::setBrickColor(Color3B col) {
	 part1->setColor(col);
	 part2_a->setColor(col);
	 part2_b->setColor(col);
	 part3_a->setColor(col);
	 part3_b->setColor(col);
	 part4_a->setColor(col);
	 part4_b->setColor(col);
	 part5_a->setColor(col);
	 part5_b->setColor(col);
	 part6_a->setColor(col);
	 part6_b->setColor(col);
	 part7_a->setColor(col);
	 part7_b->setColor(col);
	 part8_a->setColor(col);
	 part8_b->setColor(col);
 }

 void Brick::brickOpacity(float col) {
	 brickopacity = col;
	 part1->setOpacity(col);
	 part2_a->setOpacity(col);
	 part2_b->setOpacity(col);
	 part3_a->setOpacity(col);
	 part3_b->setOpacity(col);
	 part4_a->setOpacity(col);
	 part4_b->setOpacity(col);
	 part5_a->setOpacity(col);
	 part5_b->setOpacity(col);
	 part6_a->setOpacity(col);
	 part6_b->setOpacity(col);
	 part7_a->setOpacity(col);
	 part7_b->setOpacity(col);
	 part8_a->setOpacity(col);
	 part8_b->setOpacity(col);
 }

void Brick::controlModule(int id, int type) {
	if (id == 1) {
		if (type == 0) {
			part1->setVisible(false);
		}
		else if(type == 1){
			part1->setColor(Color3B::ORANGE);
		}
		else {
			part1->setColor(Color3B(77,77,77));
		}
	}
	else if (id == 2) {
		if (type == 0) {
			part2_a->setVisible(false);
			part2_b->setVisible(false);
		}
		else if (type == 1) {
			part2_a->setColor(Color3B::ORANGE);
			part2_b->setColor(Color3B::ORANGE);
		}
		else {
			part2_a->setColor(Color3B(77, 77, 77));
			part2_b->setColor(Color3B(77, 77, 77));
		}
	}
	else if (id == 3) {
		if (type == 0) {
			part3_a->setVisible(false);
			part3_b->setVisible(false);
		}
		else if (type == 1) {
			part3_a->setColor(Color3B::ORANGE);
			part3_b->setColor(Color3B::ORANGE);
		}
		else {
			part3_a->setColor(Color3B(77, 77, 77));
			part3_b->setColor(Color3B(77, 77, 77));
		}
	}
	else if (id == 4) {
		if (type == 0) {
			part4_a->setVisible(false);
			part4_b->setVisible(false);
		}
		else if (type == 1) {
			part4_a->setColor(Color3B::ORANGE);
			part4_b->setColor(Color3B::ORANGE);
		}
		else {
			part4_a->setColor(Color3B(77, 77, 77));
			part4_b->setColor(Color3B(77, 77, 77));
		}
	}
	else if (id == 5) {
		if (type == 0) {
			part5_a->setVisible(false);
			part5_b->setVisible(false);
		}
		else if (type == 1) {
			part5_a->setColor(Color3B::ORANGE);
			part5_b->setColor(Color3B::ORANGE);
		}
		else {
			part5_a->setColor(Color3B(77, 77, 77));
			part5_b->setColor(Color3B(77, 77, 77));
		}
	}
	else if (id == 6) {
		if (type == 0) {
			part6_a->setVisible(false);
			part6_b->setVisible(false);
		}
		else if (type == 1) {
			part6_a->setColor(Color3B::ORANGE);
			part6_b->setColor(Color3B::ORANGE);
		}
		else {
			part6_a->setColor(Color3B(77, 77, 77));
			part6_b->setColor(Color3B(77, 77, 77));
		}
	}
	else if (id == 7) {
		if (type == 0) {
			part7_a->setVisible(false);
			part7_b->setVisible(false);
		}
		else if (type == 1) {
			part7_a->setColor(Color3B::ORANGE);
			part7_b->setColor(Color3B::ORANGE);
		}
		else {
			part7_a->setColor(Color3B(77, 77, 77));
			part7_b->setColor(Color3B(77, 77, 77));
		}
	}
	else if (id == 8) {
		if (type == 0) {
			part8_a->setVisible(false);
			part8_b->setVisible(false);
		}
		else if (type == 1) {
			part8_a->setColor(Color3B::ORANGE);
			part8_b->setColor(Color3B::ORANGE);
		}
		else {
			part8_a->setColor(Color3B(77, 77, 77));
			part8_b->setColor(Color3B(77, 77, 77));
		}
	}
}

void Brick::setFrameIndex(int current) {
	heroTimeLine->gotoFrameAndPause(current);
}

int Brick::getFrameIndex() {
	return heroTimeLine->getCurrentFrame();
}

void Brick::createOutAnglesFrame() {
	//合并连在一起的区域
	int len = outArea.size();
	//根据每个区域的开始值排序
	for (int i = 0; i <  len - 1; i++) {
		for (int j = 0; j < len - 1 - i; j++) {
			auto a1 = getFrameByModuleId(outArea.at(j)).startFrame;
			auto a2 = getFrameByModuleId(outArea.at(j + 1)).startFrame;
			if (a1 > a2) {
				swap(outArea[j], outArea[j + 1]);
			}
		}
	}
	//排序后尾首相连的合并
	int index = 0;
	while (index < outArea.size())
	{
		AreaFrameRange angle;
		angle.startFrame = getFrameByModuleId(outArea.at(index)).startFrame;
		while (index < outArea.size() - 1 && (getFrameByModuleId(outArea.at(index+1)).startFrame <= getFrameByModuleId(outArea.at(index)).endFrame))
		{
			++index;
		}
		angle.endFrame = getFrameByModuleId(outArea.at(index)).endFrame;
		outList.push_back(angle);
		index++;
	}
}


void Brick::createDanAnglesFrame() {
	//合并连在一起的区域
	int len = danArea.size();
	//根据每个区域的开始值排序
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - 1 - i; j++) {
			auto a1 = getFrameByModuleId(danArea.at(j)).startFrame;
			auto a2 = getFrameByModuleId(danArea.at(j + 1)).startFrame;
			if (a1 > a2) {
				swap(danArea[j], danArea[j + 1]);
			}
		}
	}
	//排序后尾首相连的合并
	int index = 0;
	while (index < danArea.size())
	{
		AreaFrameRange angle;
		angle.startFrame = getFrameByModuleId(danArea.at(index)).startFrame;
		while (index < danArea.size() - 1 && (getFrameByModuleId(danArea.at(index + 1)).startFrame <= getFrameByModuleId(danArea.at(index)).endFrame))
		{
			++index;
		}
		angle.endFrame = getFrameByModuleId(danArea.at(index)).endFrame;
		danList.push_back(angle);
		index++;
	}
}


std::vector<AreaFrameRange> Brick::getOutAnglesByFrameIndex() {
	
	return outList;
}

std::vector<AreaFrameRange> Brick::getDangousAnglesByFrameIndex() {

	return danList;
}

//数据是从UI给的素材里获得的,手工配制
AreaFrameRange Brick::getFrameByModuleId(int index) {
	switch (index)
	{
	case 1: {
		AreaFrameRange angle;
		angle.startFrame = 54 ;
		angle.endFrame = 66 ;
		return angle;
	}
	case 2: {
		AreaFrameRange angle;
		angle.startFrame = 66;
		angle.endFrame = 78;
		return angle;
	}
	case 3: {
		AreaFrameRange angle;
		angle.startFrame = 78;
		angle.endFrame = 91;
		return angle;
	}
	case 4: {
		AreaFrameRange angle;
		angle.startFrame = 88;
		angle.endFrame = 101;
		return angle;
	}
	case 5: {
		AreaFrameRange angle;
		angle.startFrame = 100;
		angle.endFrame = 113;
		return angle;
	}
	case 6: {
		AreaFrameRange angle;
		angle.startFrame = 112;
		angle.endFrame = 5;
		return angle;
	}
	case 7: {
		AreaFrameRange angle;
		angle.startFrame = 4;
		angle.endFrame = 17;
		return angle;
	}
	case 8: {
		AreaFrameRange angle;
		angle.startFrame = 16;
		angle.endFrame = 29;
		return angle;
	}
	case 9: {
		AreaFrameRange angle;
		angle.startFrame = 28;
		angle.endFrame = 41;
		return angle;
	}
	case 10: {
		AreaFrameRange angle;
		angle.startFrame = 40;
		angle.endFrame = 54;
		return angle;
	}
	default: {
		AreaFrameRange angle;
		angle.startFrame = 54 ;
		angle.endFrame = 66;
		return angle;
	}
	}

}

void Brick::update(float dt) {
	//GeometryTools::drawCollisionBox(this, getCollisionRect());
	//if (NULL != getChildByTag(615)) {
	//	((Label*)getChildByTag(615))->setString(StringUtils::format("[%d]", heroTimeLine->getCurrentFrame()));
	//}
}

void Brick::brickDebug() {
	for (int i = 0; i < outList.size(); i++) {
		auto label = Label::createWithSystemFont(StringUtils::format("[%d,%d]", outList.at(i).startFrame, outList.at(i).endFrame), "arial", 30);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setColor(Color3B::BLUE);
		label->setPosition(100 + 120 * i, -30 );
		addChild(label);
	}

	for (int j = 0; j < danList.size(); j++) {
		auto label = Label::createWithSystemFont(StringUtils::format("[%d,%d]", danList.at(j).startFrame, danList.at(j).endFrame), "arial", 30);
		label->setColor(Color3B::BLUE);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(100 + 120 * j, 10);
		addChild(label);
	}

	auto curL = Label::createWithSystemFont(StringUtils::format("[%d]", heroTimeLine->getCurrentFrame()), "arial", 30);
	curL->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	curL->setTag(615);
	curL->setColor(Color3B::GREEN);
	curL->setPosition(100, 50);
	addChild(curL);
}


