#include "fish/FishArrangeThree.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"


void FishArrangeThree::initFishAnim(int fishID)
{
	//Ö÷Óã
	int randarray[7] = { 10, 30, 31, 32, 33, 34, 35 };
	int id = randarray[rand() % 7];

	auto maggiceff = MagicEffect::create(4, false);
	maggiceff->stopAllActions();
	maggiceff->setPosition(0,0);
	maggiceff->setAnchorPoint(Point::ZERO);
	addChild(maggiceff, 0);
	auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	mainfish->setPosition(maggiceff->getContentSize() / 2);
	addChild(mainfish,3);
	centerPos = mainfish->getPosition();
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	mainfish->runAction(ac);
	obbdatas = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(103);
	fishes.pushBack(mainfish);
	fishes.pushBack(maggiceff);
	centerPos = maggiceff->getContentSize() / 2;
	//¸±Óã
	int randarray1[6] = { 2,3,4,7,8,9};
	id = randarray1[rand() % 6];
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();
	auto ac3 = ac1->clone();



	auto maggiceff1 = MagicEffect::create(3, false);
	maggiceff1->setPosition(145,maggiceff->getContentSize().height/2);
	addChild(maggiceff1,0);
	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setPosition(maggiceff1->getPosition());
	sp->runAction(ac1);
	addChild(sp,1);
	fishes.pushBack(sp);
	fishes.pushBack(maggiceff1);

	auto maggiceff2 = MagicEffect::create(3, false);
	maggiceff2->setPosition(25, -8);
	addChild(maggiceff2,0);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setPosition(maggiceff2->getPosition());
	sp->runAction(ac2);
	addChild(sp,1);
	fishes.pushBack(sp);
	fishes.pushBack(maggiceff2);

	auto maggiceff3 = MagicEffect::create(3, false);
	maggiceff3->setPosition(25, 8+maggiceff->getContentSize().height);
	addChild(maggiceff3, 0);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setPosition(maggiceff3->getPosition());
	sp->runAction(ac3);
	addChild(sp,1);
	fishes.pushBack(sp);
	fishes.pushBack(maggiceff3);
}