#include "NewbieFirstGetRewardLayer.h"
#include "utill/AnimationUtil.h"
#include "config/ConfigExp.h"
#include "widget/GiftCell.h"
#include "NewbieSureDialog.h"
#include "NewbieMannger.h"
#include "domain/bag/BagManager.h"
#include "domain/user/User.h"
#include "utill/Audio.h"
bool NewbieFirstGetRewardLayer::init()
{
	bool bRet = false;
	do 
	{
		colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer, -1);

		box = Sprite::create("game/ui/ani/firstBox/firstBox_1.png");
		box->setPosition(480, 254);
		addChild(box);
		box->setRotation(-0.3);
		auto ac = Sequence::create(RotateTo::create(0.05, 3), RotateTo::create(0.05, -3), RotateTo::create(0.05, 3), RotateTo::create(0.05, -3), RotateTo::create(0.025, 0), DelayTime::create(0.5f), nullptr);
		box->runAction(RepeatForever::create(ac));

		sPoint = Sprite::create("yellowSpoint.png");
		sPoint->setPosition(480, 450);
		addChild(sPoint);
		sPoint->runAction(RepeatForever::create(Sequence::create(EaseSineOut::create(MoveTo::create(0.6f, Vec2(480, 387))), EaseSineOut::create(MoveTo::create(0.6f, Vec2(480, 450))), nullptr)));

		sLight = Sprite::create("rorateLightCoin.png");
		sLight->setScale(2.6);
		sLight->setOpacity(153);
		sLight->setPosition(box->getContentSize() / 2);
		sLight->runAction(RepeatForever::create(RotateBy::create(7.0f, 360)));
		box->addChild(sLight,-1);

		tipTxt = Sprite::create("firstRewardTxt.png");
		tipTxt->setPosition(480, 125);
		addChild(tipTxt);
		tipTxt->runAction(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), DelayTime::create(0.2f), nullptr));

		listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(NewbieFirstGetRewardLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		bRet = true;
	} while (0);
	return bRet;
}
bool NewbieFirstGetRewardLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	if (istouched)
	{
		return true;
	}
	istouched = true;
	sPoint->removeFromParentAndCleanup(1);
	tipTxt->removeFromParentAndCleanup(1);
	box->stopAllActions();
	box->setRotation(0);
	sLight->removeFromParentAndCleanup(1);
	sLight = Sprite::create("light_2.png");
	sLight->setPosition(box->getContentSize() / 2);
	box->addChild(sLight);
	sLight->runAction(Sequence::create(Spawn::create(ScaleBy::create(2.0f, 5), FadeOut::create(2.0f), nullptr), CallFunc::create([=]{box->setVisible(false); }), RemoveSelf::create(), nullptr));
	box->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("anifirstBox"), CallFunc::create([&]
	{
		Audio::getInstance()->playSound(OPENNEWBBOX);
		auto rewards = ConfigExp::getInstance()->getLevelRewardItemsByLevelId(1);
		for (int i = 0; i < rewards.size();i++)
		{
			auto cell = GiftCell::create(rewards[i].item_id, rewards[i].num);
			cell->setPosition(box->getPosition());
			cell->setScale(0);
			cell->runAction(Sequence::create(DelayTime::create(i*0.15f),Spawn::create(ScaleTo::create(0.5f, 1.0), MoveTo::create(0.5f, Vec2(281 + i * 130, 361)), nullptr), DelayTime::create(2.0f + i*0.1f), Spawn::create(MoveTo::create(0.5f, Vec2(259.2, 48)), ScaleTo::create(0.5f, 0.5f), nullptr), CallFunc::create(
		[=]{
				auto parent = this->getParent();
				auto menu = parent->getChildByName("menu");
				auto bag = menu->getChildByName("bag");
				bag->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.1, 1.2f), ScaleTo::create(0.1, 1.0f)));

			}), RemoveSelf::create(), nullptr));
			addChild(cell);
			if (rewards[i].item_id!=1012)
			{

				if (rewards[i].item_id == 1001)
				{
					User::getInstance()->addCoins(rewards[i].num);
				}
				else if (rewards[i].item_id == 1002)
				{
					User::getInstance()->addDiamonds(rewards[i].num);
				}
				else
				{
					BagManager::getInstance()->changeItemCount(rewards[i].item_id, rewards[i].num);
				}
			}
		}
	}), nullptr));
	runAction(Sequence::create(DelayTime::create(4.7f), CallFunc::create([&]{NewbieMannger::getInstance()->setisGetFirstReward(1);auto layer = NewbieSureDialog::create(); layer->setPosition(0, 0); getParent()->addChild(layer, 20); }), RemoveSelf::create(), nullptr));
	return true;
}