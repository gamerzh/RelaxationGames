#include "Hero.h"
#include "UserData.h"
USING_NS_CC;

bool Hero::init() {
	if (!Sprite::init()) {
		return false;
	}
	this->speed_y = SPEED_Y;
	setScale(0.8);
	//initWithSpriteFrameName("10000.png");
	currentMod = atoi(UserData::getInstance()->getCurrentMod().c_str());
	changeHeroSkin(currentMod);
	scheduleUpdate();
	ParticleSystem* m_emitter2 = ParticleSystemQuad::create("weib.plist");
	m_emitter2->setScale(0.3);
	m_emitter2->setPosition(40, 50);
	addChild(m_emitter2,-1);
	actionNode = Node::create();
	addChild(actionNode);
	return true;
}

void Hero::addPhysicsHero() {
	//auto hero = Sprite::create("HelloWorld.png");
	//hero->setScale(0.2f);
	//hero->setPosition(360, 640);
	//addChild(hero);
}

void Hero::changeHeroSkin(int id) {
	
	if (id == 0) {
		loadHeroAnim1();
	}
	else if (id == 1) {
		loadHeroAnim2();
	}
	else if (id == 2) {
		loadHeroAnim3();
	}
	else if (id == 3) {
		loadHeroAnim4();
	}
	else if (id == 4) {
		loadHeroAnim5();
	}
	else if (id == 5) {
		loadHeroAnim6();
	}
	else if (id == 6) {
		loadHeroAnim7();
	}
}

void Hero::flipSpeedY() {
	speed_y = speed_y * -1;
	//ParticleSystem* m_emitter1 = ParticleSystemQuad::create("feij.plist");
	//m_emitter1->setPosition(20, 0);
	//addChild(m_emitter1);
	//m_emitter1->runAction(FadeOut::create(0.4f));
}

bool Hero::isDirectionDown() {
	if (speed_y > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Hero::loadHeroAnim1() {
	Vector<SpriteFrame*> frames;
	for (int i = 0; i <= 18; i++)
	{
		std::string imageName;

		if (i < 10) {
			imageName = StringUtils::format("l1000%d.png", i);
		}
		else {
			imageName = StringUtils::format("l100%d.png", i);
		}
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageName);
		frames.pushBack(frame);
	}
	auto animation = Animation::create();
	animation->initWithSpriteFrames(frames);
	animation->setDelayPerUnit(3.0f / 36.0f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	this->stopAllActions();
	this->runAction(Repeat::create(action, CC_REPEAT_FOREVER));
}

void Hero::loadHeroAnim2() {

	Vector<SpriteFrame*> frames;
	for (int i = 0; i <= 18; i++)
	{
		std::string imageName;

		if (i < 10) {
			imageName = StringUtils::format("1000%d.png", i);
		}
		else {
			imageName = StringUtils::format("100%d.png", i);
		}
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageName);
		frames.pushBack(frame);
	}
	auto animation = Animation::create();
	animation->initWithSpriteFrames(frames);
	animation->setDelayPerUnit(3.0f / 36.0f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	this->stopAllActions();
	this->runAction(Repeat::create(action, CC_REPEAT_FOREVER));
}

void Hero::loadHeroAnim3() {
	Vector<SpriteFrame*> frames;
	for (int i = 0; i < 7; i++)
	{
		std::string imageName;
		imageName = StringUtils::format("skin_0%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageName);
		frames.pushBack(frame);
	}
	auto animation = Animation::create();
	animation->initWithSpriteFrames(frames);
	animation->setDelayPerUnit(3.0f / 36.0f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	this->stopAllActions();
	this->runAction(Repeat::create(action, CC_REPEAT_FOREVER));
}

void Hero::loadHeroAnim4() {
	Vector<SpriteFrame*> frames;
	for (int i = 20; i < 28; i++)
	{
		std::string imageName;
		imageName = StringUtils::format("skin_%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageName);
		frames.pushBack(frame);
	}
	auto animation = Animation::create();
	animation->initWithSpriteFrames(frames);
	animation->setDelayPerUnit(3.0f / 36.0f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	this->stopAllActions();
	this->runAction(Repeat::create(action, CC_REPEAT_FOREVER));
}

void Hero::loadHeroAnim5() {
	Vector<SpriteFrame*> frames;
	for (int i = 10; i < 20; i++)
	{
		std::string imageName;
		imageName = StringUtils::format("skin_%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageName);
		frames.pushBack(frame);
	}
	auto animation = Animation::create();
	animation->initWithSpriteFrames(frames);
	animation->setDelayPerUnit(3.0f / 36.0f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	auto actionNode = Sprite::create();
	this->stopAllActions();
	this->runAction(Repeat::create(action, CC_REPEAT_FOREVER));
}

void Hero::loadHeroAnim6() {
	Vector<SpriteFrame*> frames;
	for (int i = 40; i < 50; i++)
	{
		std::string imageName;
		imageName = StringUtils::format("skin_%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageName);
		frames.pushBack(frame);
	}
	auto animation = Animation::create();
	animation->initWithSpriteFrames(frames);
	animation->setDelayPerUnit(3.0f / 36.0f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	this->stopAllActions();
	this->runAction(Repeat::create(action, CC_REPEAT_FOREVER));
}

void Hero::loadHeroAnim7() {
	Vector<SpriteFrame*> frames;
	for (int i = 30; i < 39; i++)
	{
		std::string imageName;
		imageName = StringUtils::format("skin_%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageName);
		frames.pushBack(frame);
	}
	auto animation = Animation::create();
	animation->initWithSpriteFrames(frames);
	animation->setDelayPerUnit(3.0f / 36.0f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	this->stopAllActions();
	this->runAction(Repeat::create(action, CC_REPEAT_FOREVER));
}

void Hero::update(float dt) {
	float py = getPositionY();
	this->setPositionY(py - speed_y);
	if (speed_y < 0) {
		if (moveupPath < HERO_MOVE_PATH) {
			moveupPath += abs(speed_y);
		}
		else {
			moveupPath = 0;
			flipSpeedY();
		}
	}
	if (currentMod != atoi(UserData::getInstance()->getCurrentMod().c_str())) {
		currentMod = atoi(UserData::getInstance()->getCurrentMod().c_str());
		changeHeroSkin(currentMod);
	}
}
