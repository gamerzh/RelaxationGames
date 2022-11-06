#include "fish/FishArrangeTwo.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"


void FishArrangeTwo::initFishAnim(int fishID)
{
	//Ö÷Óã
	int randarray[7] = { 10, 30, 31, 32, 33, 34, 35 };
	int id = randarray[rand() % 7];
	auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));

	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	mainfish->runAction(ac);
	auto maggiceff = MagicEffect::create(1, false);
	maggiceff->stopAllActions();
	maggiceff->setPosition(maggiceff->getContentSize()/2);
	addChild(maggiceff, 1);
	mainfish->setPosition(maggiceff->getPosition());
	addChild(mainfish,1);
	fishes.pushBack(mainfish);
	obbdatas = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(102);
	centerPos = maggiceff->getContentSize() / 2;
	fishes.pushBack(maggiceff);
	//¸±Óã
	int randarray1[6] = { 2,4,7,8,32,33 };
	id = randarray1[rand() % 6];
	auto mainSize = getContentSize();
	auto AffiliateSize = FishAniMannage::getInstance()->getSpriteById(id)->getOriginalSize();
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();
	auto ac3 = ac1->clone();
	auto ac4 = ac1->clone();
	setAnchorPoint(Point::ANCHOR_MIDDLE);
	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	maggiceff = MagicEffect::create(3, false);
	maggiceff->setPosition(-15,-15);
	addChild(maggiceff, 0);
	sp->setPosition(maggiceff->getPosition());
	sp->runAction(ac1);
	addChild(sp,1);
	fishes.pushBack(sp);
	fishes.pushBack(maggiceff);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	maggiceff = MagicEffect::create(3, false);
	maggiceff->setPosition(-15, -15 + 132);
	addChild(maggiceff, 0);
	sp->setPosition(maggiceff->getPosition());
	sp->runAction(ac2);
	addChild(sp,1);
	fishes.pushBack(sp);
	fishes.pushBack(maggiceff);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	maggiceff = MagicEffect::create(3, false);
	maggiceff->setPosition(-15 + 132, -15 + 132);
	addChild(maggiceff, 0);
	sp->setPosition(maggiceff->getPosition());
	sp->runAction(ac3);
	addChild(sp,1);
	fishes.pushBack(sp);
	fishes.pushBack(maggiceff);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	maggiceff = MagicEffect::create(3, false);
	maggiceff->setPosition(-15 + 132, -15 );
	addChild(maggiceff, 0);
	sp->setPosition(maggiceff->getPosition() );
	sp->runAction(ac3);
	addChild(sp,1);
	fishes.pushBack(sp);
	fishes.pushBack(maggiceff);
}

