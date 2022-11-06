#include "domain/game/GameManage.h"
#include "domain/bag/BagManager.h"
#include "core/UpgradeSureDialog.h"
#include "utill/CShake.h"
#include "config/ConfigChest.h"
#include "domain/Newbie/NewbieMannger.h"
#include "core/GetRewardNode.h"
#include "widget/MyLabelAtlas.h"
GameManage* GameManage::_instance = 0;

GameManage* GameManage::getInstance(){
	if (_instance == 0){
		_instance = new GameManage();
	}
	return _instance;
}

GameManage::GameManage(){
	
}
void GameManage::showLockTurrent()
{
	m_pGuilayer->showLockUpgradeTurret();
}

void GameManage::showGainMoneyTurrent()
{
	m_pGuilayer->showGainMoneyTurrent();
}



void  GameManage::CatchTheFishOntheTurrent(Fish*fish, bool isDead, PlayerTurret* turret)
{
	if (fish->getTargeLightTurret())
	{
		fish->getTargeLightTurret()->setLightFish(nullptr);
	}
	if (fish->getTargeLockTurret())
	{
		fish->getTargeLockTurret()->setLockFish(nullptr);
	}
	fish->removeAllBullet();
	FishManage::getInstance()->getAllFishInPool().eraseObject(fish);
	if (isDead)
	{

		if (fish->getFishType() == GoldFish||fish->getFishType() == ArrangeFish||fish->getFishType() == BossFish)
		{
			//黄金鱼捕获动画
			auto ac = Director::getInstance()->getRunningScene()->getActionByTag(666);
			if (!ac)
			{
				auto acShake = CCShake::create(0.2, 30);
				acShake->setTag(666);
				Director::getInstance()->getRunningScene()->runAction(acShake);
			}
			
			auto aninode = Node::create();
			aninode->setPosition(0, 0);
			turret->addChild(aninode, 1, "goldfichCatch");

			
			auto sp = Sprite::create("goldFishCatchTable.png");
			sp->setPosition(Vec2(80, 180));
			aninode->addChild(sp);
			sp->runAction(RepeatForever::create(RotateBy::create(0.5, 360)));
			sp->setScale(0.7);


			Audio::getInstance()->playSound(ONGOLDFISHDEAD);

			auto aninode1 = Sprite::create("quickStart.png");
			aninode1->setPosition(sp->getPosition());
			aninode->addChild(aninode1,-1);
			aninode1->runAction(RepeatForever::create(Sequence::create(Spawn::create(FadeIn::create(0.001), ScaleTo::create(0.001, 0), nullptr), Spawn::create(FadeOut::create(2.0), ScaleTo::create(2.0, 2.0f), nullptr), nullptr)));


			auto num = fish->getFishGold()* turret->getTurrentMupltData().multiple*ConfigChest::getInstance()->getChestByLevel(User::getInstance()->getUserBoxLevel()).catch_per;
			auto lb = MyLabelAtlas::create(Value(Value(num).asInt()).asString(), "goldFishNum.png", 28, 41, '0',120);
			lb->setAnchorPoint(Point::ANCHOR_MIDDLE);
			lb->setPosition(Vec2(80, 180));
			lb->setRotation(-30);
			lb->runAction(RepeatForever::create(Sequence::create(RotateTo::create(0.45f, 30), RotateTo::create(0.45f, -30), nullptr)));
			aninode->addChild(lb);


			auto txtframe = Sprite::create("goldFishCatch.png");
			txtframe->setPosition(Vec2(80, 130));
			aninode->addChild(txtframe);
			String* str;
			auto id = fish->getFishID();
			if (id>=40&&id<=44)
			{
				str= String::createWithFormat("TXTGoldFish_%d.png", id);
			}
			else
			{
				str = String::create("TXTGoldFish_XX.png");
			}		
			auto txt = Sprite::create(str->getCString());
			txt->setPosition(txtframe->getContentSize() / 2);
			txtframe->addChild(txt);
			aninode->runAction(Sequence::create(DelayTime::create(4.0f), RemoveSelf::create(1), nullptr));	
		}
		LogEventFish::getInstance()->addFishCatchTimes(fish->getFishID());
		switch (fish->getFishType())
		{
		case BoomFish:
		{
			FishManage::getInstance()->onBoomFishDead(fish, turret);
			auto aninode = Sprite::create();
			aninode->setPosition(fish->getPosition());
			aninode->setScale(2);
			aninode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniTXTBoom"), RemoveSelf::create(1), nullptr));
			m_pGameyer->addChild(aninode, 1);
		}
			
			break;
		case AllKilledFish:
			FishManage::getInstance()->onAllKilledFishDead(fish, turret);
			break;
		default:
			break;
		}
		turret->getCoinByFish(fish);
		//如果是自己捕获到
		if (!turret->isRobot&&fish->getFishType()==GoldFish)
		{
			showGainMoneyTurrent();
		}
		if (!turret->isRobot)
		{
			//美人鱼任务相关
			auto data = GameData::getInstance();
			if (data->getIsOnMaridTask())
			{
				auto vec = data->getmermaidTask()->getMermaidTaskOnlineInfo().mermaidTaskItems;
				for (auto var : vec)
				{
					if (fish->getFishID() == var.fishId&&!turret->isRobot)
					{
						data->getmermaidTask()->addOneCatchFishById(fish->getFishID());
						break;
					}
				}
			}
			//锁定技能引导相关
			if (NewbieMannger::getInstance()->getNBShootCounts() >= 10)
			{
				NewbieMannger::getInstance()->setNBShootCounts(-1);
				m_pGuilayer->ShowUseLockTip(fish->getPosition());
			}





		}
		
		fish->onDead();
	}
	else
	{
		fish->removeself();
	}
	fish = nullptr;

}

void GameManage::onBrokeBySomeTurret(PlayerTurret*turret, int lefttime, float waittime)
{
	if (lefttime > 0)
	{
		Bankrupt baknrupt;
		baknrupt.time = lefttime;
		baknrupt.wait_time = waittime;
		auto layer = m_pGuilayer;
		auto node = GetRewardNode::create(baknrupt);
		node->setPosition(turret->getPosition() + Vec2(0, 150));
		layer->addChild(node, 100);
		BankruptManager::getInstance()->setgetRewardNode(node);
	}
	else if (lefttime == 0)
	{
		auto pay = payLayer::createLayer(1);
		pay->setPosition(0, 0);
		pay->setEventPont(19);
		GameManage::getInstance()->getGuiLayer()->addChild(pay, 20);
	}
}
void GameManage::onRebirthBySomeTurret(int reward_coins)
{
	User::getInstance()->addCoins(reward_coins);
	BankruptManager::getInstance()->getgetRewardNode()->removeFromParentAndCleanup(1);
	BankruptManager::getInstance()->setgetRewardNode(nullptr);
	BankruptManager::getInstance()->addTodayRequestTime();
}
void GameManage::onPlayerUpgrade()
{
	auto rewards = ConfigExp::getInstance()->getLevelRewardItemsByLevelId(User::getInstance()->getLevelData().levelId);
	Audio::getInstance()->playSound(UPDATALEVEL);
	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	m_pGuilayer->addChild(colorlayer, 30);
	auto aninode = Sprite::create();
	aninode->setPosition(480, 270);
	m_pGuilayer->addChild(aninode, 30);
	aninode->setScale(4);
	auto txt = Sprite::create("TXTUpGrade.png");
	txt->setPosition(480, 350);
	m_pGuilayer->addChild(txt, 30);
	txt->setScale(0);
	auto addcoinani = Sprite::create("UpdateLight.png");
	addcoinani->setPosition(txt->getContentSize()/2+Size(0,0));
	addcoinani->setVisible(false);
	addcoinani->runAction(RepeatForever::create(RotateBy::create(5, 360)));
	txt->addChild(addcoinani,-1);
	txt->runAction(Sequence::create(ScaleTo::create(0.2, 1.4), ScaleTo::create(0.2, 0.7), ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 1.0), CallFunc::create([=]{addcoinani->setVisible(true); }), nullptr));

	aninode->runAction(Sequence::create(Repeat::create(AnimationUtil::getInstance()->getAnimate("aniShengji"), 2), CallFunc::create([=]{txt->removeFromParentAndCleanup(1); auto node = UpgradeSureDialog::create(rewards);
	node->setPosition(0, 0);
	m_pGuilayer->addChild(node, 30); colorlayer->removeFromParentAndCleanup(1); }), RemoveSelf::create(), nullptr));
	
}