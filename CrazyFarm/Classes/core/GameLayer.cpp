#include "core/GameLayer.h"
#include "net/Net.h"
#include "utill/FunUtil.h"
#include "utill/AnimationUtil.h"
#include "utill/CircleMoveTo.h"
#include "domain/user/User.h"
#include "domain/ai/AIManager.h"
#include "fish/FishGroupData.h"
#include "data/GameData.h"
#include "config/ConfigRoom.h"
#include "fish/FishArrangeOne.h"
#include "domain/skill/skillManager.h"
#include "domain/gameConfig/gameConfig.h"
#include "fish/FishAniMannage.h"
#include "utill/CollisionUtill.h"
#include "utill/Audio.h"
#include "domain/logevent/LogEventMannger.h"
#include "bullet/Laster.h"
#include "domain/bag/BagManager.h"
#include "domain/game/GameManage.h"
#include "domain/Newbie/NewbieMannger.h"
#include "domain/bankrupt/BankruptManager.h"
#include "config/ConfigNewbieFishCatch.h"
#include "utill/OBB.h"
#include "domain/game/GameManage.h"
#include "utill/define.h"
#define BOOMRADIUS 300

enum
{
	kTagBaseturret= 10,
	kTagFrezzebg  = 11,
	kTagBoomAniNode = 12
};


bool GameLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	setIsShowYourChairno(false);
	FishManage::getInstance()->setlayer(this);
	skillManager::getInstance()->setlayer(this);
	GameManage::getInstance()->setGameyer(this);
	//add game bg to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	game_bg = Sprite::create("aniWater1.jpg");
	game_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(game_bg,-2);
	

	///水波纹
	auto anibowennode = Sprite::create();
	anibowennode->setScale(2);
	anibowennode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBowen")));
	anibowennode->setPosition(0, 0);
	anibowennode->setAnchorPoint(Point::ZERO);
	addChild(anibowennode,-1);

	anibowennode = Sprite::create();
	anibowennode->setScale(2);
	anibowennode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBowen")));
	anibowennode->setPosition(550, 0);
	anibowennode->setAnchorPoint(Point::ZERO);
	addChild(anibowennode, -1);


	

	scheduleUpdate(); 




	addTouchEvent();	
    auto roominfo = ConfigRoom::getInstance()->getRoombyId(GameData::getInstance()->getRoomID());
	players = RoomManager::getInstance()->initRoomConfig(roominfo.unlock_turrent_level);
	calculateFreeChair();
	createTurret();
	//0.1f执行一次碰撞
	schedule(schedule_selector(GameLayer::collisionUpdate), 1.0 / 40.0f, CC_REPEAT_FOREVER, 0);

	schedule(schedule_selector(GameLayer::shootUpdata), 1.0 / 60.0f, CC_REPEAT_FOREVER, 0);
	

	runAction(Sequence::create(DelayTime::create(0.01f),
		CallFunc::create([&]{
		initFishAndBulletData();
		FishManage::getInstance()->LoadOnement(MomentManager::getInstance()->getNewMomentByType(rand() % 3 + 81,rand() % (300 - 35) + 10));
	for (int i = 0; i < 5;i++)
	{
		update(1);
	}
		for (auto var : FishManage::getInstance()->getAllFishInPool())
		{
			for (int i = 0; i < 5; i++)
			{
				var->moveUpdata(1);
			}
		}
 }), nullptr));

	setbisOnSkillLock(false);

	GameData::getInstance()->setDiamondevent(MagnateManager::getInstance()->getDiamandMagnateEvent());
	GameData::getInstance()->setpropevent(MagnateManager::getInstance()->getItemMagnateEvent());


	if (!NewbieMannger::getInstance()->getisOverTeachMode())
	{
		auto txtclick = Sprite::create("TXTClickCatch.png");
		txtclick->setPosition(480, 270);
		addChild(txtclick, kZorderDialog, "clickcatch");
		txtclick->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), DelayTime::create(0.2f), nullptr)));
	}
	
	skillManager::getInstance()->init();


	auto node = BankruptManager::getInstance()->getgetRewardNode();
	if (node)
	{
		if (node->getParent())
		{
			node->removeFromParentAndCleanup(false);
		}
		node->setPosition(myTurret->getPosition()+Vec2(0,150));
		addChild(node);
	}

	createFishAcNode = Node::create();
	createFishAcNode->setPosition(0, 0);
	addChild(createFishAcNode);


	showYourChairno();
	
		


/////////////////TEST BEGIN///////////////////////////
//	Vector<Fish*> needDeadFishs;
//	for (int i = 0; i < 10;i++)
//{
//	auto fish = FishManage::getInstance()->createFishSingle(i+1);
//	fish->setPosition(rand() % 500 + 200, 100 + rand() % 200);
//	addChild(fish, 10);
//	needDeadFishs.pushBack(fish);
//}
//	if (needDeadFishs.size() > 0)
//	{
//		auto fish = FishManage::getInstance()->createFishSingle(5);
//		fish->setPosition(rand() % 500 + 200, 100 + rand() % 200);
//		addChild(fish, 10);
//		auto shandian = Sprite::create("game/ui/ani/TX_shandian/shandian_1.png");
//		shandian->setPosition(fish->getPosition());
//		shandian->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//		addChild(shandian, 2);
//		shandian->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniShandian")));
//		auto rorate = getTurretRotation(fish->getPosition(), needDeadFishs.at(0)->getPosition());
//		auto distans = fish->getPosition().distance(needDeadFishs.at(0)->getPosition());
//		shandian->setRotation(-90 + rorate);
//		shandian->setScaleX(distans / 933.0f);
//	}
//	for (int i = 0; i < needDeadFishs.size(); i++)
//	{
//		auto var = needDeadFishs.at(i);
//		//闪电光圈
//		auto sp = Sprite::create();
//		sp->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGuangqiu")));
//		sp->setPosition(var->getPosition());
//		addChild(sp, 3);
//		//闪电
//		if ((i + 1) < needDeadFishs.size())
//		{
//
//			auto shandian = Sprite::create("game/ui/ani/TX_shandian/shandian_1.png");
//			shandian->setPosition(var->getPosition());
//			shandian->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//			addChild(shandian, 2);
//			shandian->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniShandian")));
//			auto rorate = getTurretRotation(var->getPosition(), needDeadFishs.at(i + 1)->getPosition());
//			auto distans = var->getPosition().distance(needDeadFishs.at(i + 1)->getPosition());
//			shandian->setRotation( - 90 + rorate);
//			shandian->setScaleX(distans / 933.0f);
//
//
//		}
//		
//	}
//
//
//

/////////////////TEST END///////////////////////////
	

	//auto fish = FishManage::getInstance()->createFishSingle(50);
	//fish->setVisible(false);
	//fish->setisAutoRemove(false);
	//fish->setMonentEightRoute(21);
	//addChild(fish, fish->getFishZorder());

	//fish->addShader();

	_touchtypes.push_back(TouchInNormal);
	return true;
}


void GameLayer::showYourChairno()
{
	auto sp = Sprite::create("TXTYourChairno.png");
	sp->setPosition(myTurret->getPosition() + Vec2(0, 80));
	addChild(sp, 20);
	sp->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), DelayTime::create(0.2f), nullptr)));
	sp->runAction(Sequence::create(DelayTime::create(8.0f), RemoveSelf::create(), nullptr));

	auto pos = myTurret->getPosition() + Vec2(0, 130);
	auto sPoint = Sprite::create("yellowSpoint.png");
	sPoint->setPosition(pos);
	addChild(sPoint, 20);
	sPoint->runAction(RepeatForever::create(Sequence::create(EaseSineOut::create(MoveBy::create(0.6f, Vec2(0, 30))), EaseSineOut::create(MoveBy::create(0.6f, Vec2(0, -30))), nullptr)));

	sPoint->runAction(Sequence::create(DelayTime::create(8.0f), RemoveSelf::create(), nullptr));
}


void GameLayer::createTurret(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto vec = players;
	auto user = User::getInstance();

	myTurret = PlayerTurret::create();
	const Point turretPos[4] =
	{
		Vec2(visibleSize.width *0.3, myTurret->getBoundingBox().size.height / 2),
		Vec2(visibleSize.width *0.7, myTurret->getBoundingBox().size.height / 2),
		Vec2(visibleSize.width *0.7, visibleSize.height - myTurret->getBoundingBox().size.height / 2),
		Vec2(visibleSize.width *0.3, visibleSize.height - myTurret->getBoundingBox().size.height / 2)
	};
	
	myTurret->initWithDate(user, m_index);
	myTurret->setAnchorPoint(ccp(0.5, 0.5));
	myTurret->setPosition(turretPos[m_index]);
	this->addChild(myTurret, kZorderTurrent);

	for (auto player:vec)
	{
		auto otherTurret = PlayerTurret::create();
		otherTurret->setAnchorPoint(ccp(0.5, 0.5));
		otherTurret->setPosition(turretPos[player.getRoomPosition()]);
		otherTurret->initWithDate(&player);
		otherTurrets.pushBack(otherTurret);
		addChild(otherTurret, kZorderMenu, kTagBaseturret + player.getRoomPosition());
		
	}
	
}




void GameLayer::addTouchEvent(){
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	m_touchType = TouchInNormal;
}

void GameLayer::shootUpdata(float dt)
{
	static float temp = 0;
	temp -= dt;
	if (temp<=0)
	{
		isShoot = true;
		
	}
	if (istouched == true)
	{
		if (!isShoot)
		{
			return ;
		}
		temp = GameConfig::getInstance()->getShootData().shootInterval;
		float degree = getTurretRotation(myTurret->getPosition(), touchpos);
		degree -= 360;
		if (degree<-85||degree>85)
		{
			//射击角度范围（-85，85）；
			return;
		}
		myTurret->shoot(degree);
		isShoot = false;
	}
}

bool GameLayer::onTouchBegan(Touch *touch, Event  *event)
{
	auto node = getChildByName("clickcatch");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
		

		NewbieMannger::getInstance()->setisOverTeachMode(1);
	}
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return true;
	}
	if (GameData::getInstance()->getisOnBankrupt()&&!BankruptManager::getInstance()->getgetRewardNode())
	{
		auto pay = payLayer::createLayer(1);
		pay->setPosition(0, 0);
		pay->setEventPont(19);
		GameManage::getInstance()->getGuiLayer()->addChild(pay, 30);
		return true;
	}
	removePlayerInfo();
	
	istouched = true;
	touchpos = touch->getLocation();
	return true;
}
void GameLayer::removePlayerInfo()
{
	if (myTurret->getIsShowInfo())
	{
		myTurret->removePlayerInfo();
		myTurret->setIsShowInfo(false);
	}
	for (auto var:otherTurrets)
	{
		if (var->getIsShowInfo())
		{
			var->removePlayerInfo();
			var->setIsShowInfo(false);
		}
	}
}
bool GameLayer::lockTouchEvent(Touch *touch, Event  *event)
{
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return false;
	}
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
	removePlayerInfo();
	auto fish = FishManage::getInstance()->getFishByPosInPool(touchPos);
	if (fish)
	{
		myTurret->setLockFish(fish);
	}
	return false;
}


void GameLayer::onTouchMoved(Touch *touch, Event  *event)
{
	touchpos = touch->getLocation();
}

void  GameLayer::onTouchEnded(Touch *touch, Event  *event)
{
	istouched = false; 
}




void GameLayer::rotateTurret(float degree,PlayerTurret* turret){
	turret->rorateTurret(degree);
}

void GameLayer::update(float dt){



	FishManage::getInstance()->UpdateWhenController(dt);
	FishManage::getInstance()->UpdataCreateFish(dt);
}


void GameLayer::createNet(Bullet *bullet){
	Net* fishNet = Net::create();
	fishNet->setAnchorPoint(Point::ANCHOR_MIDDLE);
	fishNet->setBullet(bullet);
	float dotdistance = bullet->getContentSize().height*0.2;
	float angle = bullet->getRotation();
	auto dotpos = Vec2(dotdistance*sin(CC_DEGREES_TO_RADIANS(angle)), dotdistance*cos(CC_DEGREES_TO_RADIANS(angle)));
	fishNet->setPosition(bullet->getPosition()/* + dotpos*/);
	fishNet->setRotation(bullet->getRotation());
	fishNet->initNetByType();
	this->addChild(fishNet, kZorderNet);
}


void GameLayer::calculateFreeChair()
{
	auto maxlv = User::getInstance()->getMaxTurrentLevel();
	if (maxlv<5)
	{
		m_index = 1;
	}
	else
	{
		m_index = rand() % 1;
	}
	std::vector<int> freeChairno;
	for (int i = 0; i < 4;i++)
	{
		if (i==m_index)
		{
			continue;
		}
		else
		{
			freeChairno.push_back(i);
		}
	}
	for (int i = 0; i < 3;i++)
	{
		players[i].setRoomPosition(freeChairno[i]);
	}
}

void GameLayer::AiUpdata(float dt)
{
	//AIManager::getInstance()->mainUpdata(dt);
}
bool GameLayer::sortFish(const Fish * m1, const Fish * m2) {
	auto _tempBullerPos = GameData::getInstance()->getTempBullerPos();
	float distans1 = m1->getPosition().distance(_tempBullerPos);
	float distans2 = m2->getPosition().distance(_tempBullerPos);
	return distans1 < distans2;
}
void GameLayer::collisionUpdate(float dt)
{
	//TODO 碰撞逻辑
	//step1 获取子弹列表
	auto allBullets = BulletManage::getInstance()->getAllBullets();
	//step2 获取鱼的列表
	auto allFish = FishManage::getInstance()->getAllFishInPool();
	//step3 碰撞检查
	Vector<Bullet*> bulletNeedRemove;

	for (auto bullet : allBullets)
	{
		GameData::getInstance()->setTempBullerPos(bullet->getPosition());
		std::sort(allFish.begin(), allFish.end(), GameLayer::sortFish);
		for (auto fish : allFish)
		{
			if (CollisionUtill::isCollisionFishAAndBullet(fish, bullet)){
				//发生碰撞,移除子弹,在这里计算捕获鱼，渔网只有UI作用，无影响
				bulletNeedRemove.pushBack(bullet);
				bullet->setVisible(false);
				auto turretdata = bullet->getTurretdata();
				auto curryFish = fish;
				if (curryFish == nullptr)
				{
					return;
				}	
				LogEventFish::getInstance()->addFishHitTimes(curryFish->getFishID());
				float k = rand_0_1();
				float per = curryFish->getGrabProbability();

				if (!bullet->getPlayerTurret()->isRobot)
				{
					LogEventFish::getInstance()->addFishUserCostCoin(curryFish->getFishID(), bullet->getPlayerTurret()->getTurrentMupltData().multiple);
					float perForLevel = ConfigNewbieFishCatch::getInstance()->getperByLevelAndFishID(User::getInstance()->getLevelData().levelId, fish->getFishID());
					if (perForLevel>0)
					{
						per = perForLevel;
					}
				}
				if (k < (per*turretdata.catch_per))
				{
					GameManage::getInstance()->CatchTheFishOntheTurrent(curryFish, 1, bullet->getPlayerTurret());
				}
				//打开渔网
				createNet(bullet);
				break;
			}
		}
		
	}

	for (Bullet* bullet : bulletNeedRemove){
		bullet->removeFromParentAndCleanup(1);
		BulletManage::getInstance()->removeBullet(bullet);
	}
	
	
	FishManage::getInstance()->removeFishWhichSwimOut();
}
void GameLayer::initFishAndBulletData()
{
	if (isInitData == false)
	{
		FishManage::getInstance()->cleanVector();
		BulletManage::getInstance()->ClearManage();
		GameData::getInstance()->setisOnGroupComing(false);
		isInitData = true;
	}
}
void GameLayer::onEnter()
{
	Layer::onEnter();
	
}
void GameLayer::onExit()
{
	
	Layer::onExit();
	
}
void GameLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	
}
void GameLayer::loadNewMonent(float ffTime)
{
	FishManage::getInstance()->LoadOnement(MomentManager::getInstance()->getNewMoment(ffTime));
}

void GameLayer::RefreShmyPlayerTurret()
{
	myTurret->refreshTurretInfo();
}
bool GameLayer::lightTouchEvent(Touch *touch, Event *event)
{
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return false;
	}
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
	removePlayerInfo();
	auto fish = FishManage::getInstance()->getFishByPosInPool(touchPos);
	if (fish)
	{
		myTurret->setLightFish(fish);
	}
	return false;
}
void GameLayer::beginLight()
{
	_touchtypes.push_back(TouchInLight);
	m_lasttouchType = m_touchType;
	myTurret->beginLightShoot();
	changeTouchFunByTouchType(TouchInLight);

	auto txt = Sprite::create("TXTUseLight.png");
	txt->setPosition(myTurret->getPosition() + Vec2(0, 100));
	addChild(txt, kZorderDialog, "TXTTip");
}
void GameLayer::endLight()
{
	_touchtypes.remove(TouchInLight);
	myTurret->endLightShoot();
	changeTouchFunByTouchType(_touchtypes.back());
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
}

void GameLayer::beginLock()
{
	_touchtypes.push_back(TouchInLock);
	m_lasttouchType = m_touchType;
	myTurret->beginLockShoot();
	changeTouchFunByTouchType(TouchInLock);

	auto txt = Sprite::create("TXTUseLock.png");
	txt->setPosition(myTurret->getPosition() + Vec2(0, 100));
	txt->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.8f), FadeOut::create(0.8f), nullptr)));
	addChild(txt, kZorderDialog, "TXTTip");
}
void GameLayer::endLock()
{
	_touchtypes.remove(TouchInLock);
	myTurret->endLockShoot();
	changeTouchFunByTouchType(_touchtypes.back());
	auto node = getChildByName("TXTTip");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
}

void GameLayer::beginSkillBoom()
{
	_touchtypes.push_back(TouchInBoom);
	m_lasttouchType = m_touchType;
	changeTouchFunByTouchType(TouchInBoom);

	auto txt = Sprite::create("TXTUseBomb.png");
	txt->setPosition(myTurret->getPosition() + Vec2(0, 100));
	addChild(txt, kZorderDialog, "TXTTip");
}
void GameLayer::endSkillBoom()
{
	_touchtypes.remove(TouchInBoom);
	changeTouchFunByTouchType(_touchtypes.back());

	auto txttip = getChildByName("TXTTip");
	if (txttip)
	{
		txttip->removeFromParentAndCleanup(1);
	}
	
}


void GameLayer::onBoomCatchFish(Point pos)
{
	auto fishPool = FishManage::getInstance()->getAllFishInPool();
	auto data = GameData::getInstance();
	for (auto fish : fishPool)
	{
		if (CollisionUtill::isCollisionFishAAndRect(fish, Rect(pos.x - 200, pos.y - 200, 400, 400)))
		{
			GameManage::getInstance()->CatchTheFishOntheTurrent(fish, 1, myTurret);
		}

	}
	endSkillBoom();
}

bool GameLayer::boomTouchEvent(Touch *touch, Event  *event)
{
	auto pos = touch->getLocation();
	if (onTouTurret(pos))
	{
		return true;
	}
	removePlayerInfo();
	auto sp = Sprite::create("sign_1006.png");
	sp->setPosition(myTurret->getPosition());
	sp->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.13f, 1), MoveTo::create(0.13f, pos), nullptr), RemoveSelf::create(), CallFunc::create([=]{
		auto boombg = Sprite::create("boomBg.png");
		boombg->setPosition(pos);
		boombg->setScale(2);
		addChild(boombg);
		boombg->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), nullptr));

		auto anisp = Sprite::create();
		anisp->setPosition(pos);
		anisp->setScale(2);
		addChild(anisp);
		onBoomCatchFish(pos);
		anisp->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniTXTBoom"),RemoveSelf::create(),nullptr));
	}),nullptr));
	addChild(sp);


	return true;
}


bool GameLayer::onTouTurret(Point pos)
{
	if (myTurret->onTurretTouch(pos))
	{
		return true;
	}
	for (auto var : otherTurrets)
	{
		if (var->onTurretTouch(pos))
		{
			return true;
		}
	}
	return false;
}

void GameLayer::changeTouchFunByTouchType(TouchType type)
{
	switch (type)
	{
	case TouchInNormal:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
		break;
	case TouchInLock:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::lockTouchEvent, this);
		break;
	case TouchInBoom:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::boomTouchEvent, this);
		break;
	case TouchInAutoShoot:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::AutoShootTouchEvent, this);
		break;
	case TouchInLight:
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::lightTouchEvent, this);
		break;
	default:
		break;
	}
	m_touchType = type;
}


void GameLayer::beginAutoShoot()
{
	autoShootPos = Point(-1, -1);
	m_lasttouchType = m_touchType;
	_touchtypes.push_back(TouchInAutoShoot);
	changeTouchFunByTouchType(TouchInAutoShoot);
	myTurret->beginAutoShoot();
	
}
void GameLayer::endAutoShoot()
{
	_touchtypes.remove(TouchInAutoShoot);
	changeTouchFunByTouchType(_touchtypes.back());
	myTurret->endAutoShoot();
}
bool GameLayer::AutoShootTouchEvent(Touch *touch, Event *event)
{
	auto touchPos = touch->getLocation();
	if (onTouTurret(touchPos))
	{
		return false;
	}
	myTurret->setTargetPos(touchPos);
}

void GameLayer::useFreeze(PlayerTurret*turret)
{
	unscheduleUpdate();
	createFishAcNode->pause();
	auto bg = ProgressTimer::create(Sprite::create("iceFram4.jpg"));
	bg->setType(ProgressTimer::Type::BAR);
	bg->setMidpoint(Vec2(0, 0));
	bg->setBarChangeRate(Vec2(1, 0));
	addChild(bg, 0, kTagFrezzebg);
	bg->setPosition(480, 270);
	bg->runAction(ProgressTo::create(2, 100));



	auto bg1 = ProgressTimer::create(Sprite::create("onFreezeTop.png"));
	bg1->setScale(2);
	bg1->setType(ProgressTimer::Type::BAR);
	bg1->setMidpoint(Vec2(0, 0));
	bg1->setBarChangeRate(Vec2(1, 0));
	addChild(bg1, kZorderFishXL+11, "kTagFrezzebg");
	bg1->setPosition(480, 270);
	bg1->runAction(ProgressTo::create(2, 100));




	auto aniSp = ProgressTimer::create(Sprite::create("game/ui/ani/TX_DongJie/TX_qpdj_1.png"));
	aniSp->setType(ProgressTimer::Type::BAR);
	aniSp->setMidpoint(Vec2(0, 0));
	aniSp->setBarChangeRate(Vec2(1, 0));
	aniSp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	aniSp->setPosition(Vec2(aniSp->getContentSize().width*0.4,150));
	turret->addChild(aniSp);

	aniSp->runAction(Sequence::create(ProgressTo::create(1, 100), CallFunc::create([=]{
		auto anisp = Sprite::create();
		anisp->setPosition(aniSp->getPosition());
		turret->addChild(anisp, 0, "freezetxt");
		anisp->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniTXTdj")));
		aniSp->removeFromParentAndCleanup(1);

	}
	), nullptr));
}

void GameLayer::onFreezeEnd(PlayerTurret*turret)
{
	scheduleUpdate();
	createFishAcNode->resume();
	getChildByTag(kTagFrezzebg)->removeFromParentAndCleanup(1);
	getChildByName("kTagFrezzebg")->removeFromParentAndCleanup(1);
	turret->getChildByName("freezetxt")->removeFromParentAndCleanup(1);
}

void GameLayer::onClearFish()
{
	/*createFishAcNode->pause();*/

	auto txt = Sprite::create("yuchaoTXT.png");
	txt->setPosition(480, 270);
	addChild(txt,kZorderFishXL+2,"yuchaotxt");

	auto lang = Sprite::create("wave.png");
	lang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lang->setPosition(1100, 270);
	lang->runAction(Sequence::create(MoveTo::create(5, Vec2(-300, 270)), CallFunc::create([&]{
		unschedule(schedule_selector(GameLayer::onClearFishUpdata)); 
		getChildByName("yuchaotxt")->removeFromParentAndCleanup(1);
	}), RemoveSelf::create(), nullptr));
	addChild(lang, kZorderFishXL+1, "lang");

	
	schedule(schedule_selector(GameLayer::onClearFishUpdata), 0, CC_REPEAT_FOREVER, 0);
	Audio::getInstance()->playSound(CLEARFISH);
}

void GameLayer::onClearFishUpdata(float dt)
{
	auto node = (Sprite*)getChildByName("lang");
	if (node)
	{
		auto rect = node->getBoundingBox();
		rect.setRect(rect.origin.x,rect.origin.y-200, rect.size.width, rect.size.height + 400);


		auto vec = FishManage::getInstance()->getAllFishInPool();
		Vector<Fish*> needRemove;
		for (auto var:vec)
		{
			if (CollisionUtill::isCollisionFishAAndRect(var, rect))
			{
				needRemove.pushBack(var);
			}
			
		}
		for (auto fish : needRemove)
		{
			GameManage::getInstance()->CatchTheFishOntheTurrent(fish, 0, nullptr);

		}


		auto vec1 = BulletManage::getInstance()->getAllBullets();
		Vector<Bullet*> needRemove1;
		for (auto var : vec1)
		{
			if (CollisionUtill::isCollisionNodeAAndRect(var,rect))
			{
				needRemove1.pushBack(var);
			}

		}
		for (auto bullet : needRemove1)
		{
			BulletManage::getInstance()->removeBullet(bullet);
			if (bullet->getParent())
			{
				bullet->removeFromParentAndCleanup(1);
			}

		}
	}

}
void GameLayer::onClearFishFinish()
{
	Audio::getInstance()->playBGM(GAMEBGM);
}

void GameLayer::addReward(int itemid, int num)
{
	BagManager::getInstance()->changeItemCount(itemid, num);
	if (itemid==1001)
	{
		User::getInstance()->addCoins(num);
	}
	else if (itemid ==1002)
	{

		User::getInstance()->addDiamonds(num);
	}
}

void GameLayer::onGetReward(int itemid, int num)
{
	auto spPath = String::createWithFormat("sign_%d.png", itemid);

	auto sp = Sprite::create(spPath->getCString());
	sp->setPosition(480, 300);
	GameManage::getInstance()->getGuiLayer()->addChild(sp, kZorderDialog+2);	


	auto txt = String::createWithFormat(":%d", num);
	auto spnum = LabelAtlas::create(txt->getCString(), "turntableCellNum.png", 15, 23, '0');
	spnum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	spnum->setPosition(sp->getContentSize().width*0.5, sp->getContentSize().height*-0.05);
	sp->addChild(spnum);


	auto lightsp = Sprite::create("light1.png");
	lightsp->setPosition(sp->getContentSize()/2);
	lightsp->runAction(RotateBy::create(2.0f, 360.0));
	lightsp->setScale(2);
	sp->addChild(lightsp,-1);
	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	GameManage::getInstance()->getGuiLayer()->addChild(colorlayer, kZorderDialog+1);

	auto aninode = Sprite::create();
	aninode->setPosition(480, 270);
	GameManage::getInstance()->getGuiLayer()->addChild(aninode, kZorderDialog+1);
	aninode->setScale(4);
	aninode->runAction(Sequence::create(Repeat::create(AnimationUtil::getInstance()->getAnimate("aniShengji"), 2), RemoveSelf::create(), nullptr));
	sp->runAction(Sequence::create( ScaleTo::create(1.5f, 1.4f), CallFunc::create([=]{colorlayer->removeFromParentAndCleanup(1); }),Spawn::create(MoveTo::create(1.0f, myTurret->getPaoWorldpos()),ScaleTo::create(1.0f,0.5f),nullptr), CallFunc::create([=]{addReward(itemid, num); }), RemoveSelf::create(1), nullptr));

}


void GameLayer::onGetRewardByfish(PlayerTurret*turrent, Fish*fish, int itemid, int num)
{
	Sprite*sp;
	if (itemid ==1002)
	{
		sp = Sprite::create("bigDiamond.png");
		auto ani = Sprite::create("dropLightRorate.png");
		ani->setPosition(sp->getContentSize() / 2);
		sp->addChild(ani, -1);
		ani->runAction(RepeatForever::create(RotateBy::create(5.0, 360)));
	}
	else
	{
		auto str = String::createWithFormat("item_%d.png", itemid);
		sp = Sprite::create(str->getCString());
	}
	sp->setPosition(480,270);
	sp->setScale(0);
	GameManage::getInstance()->getGuiLayer()->addChild(sp,20);
	auto distans = turrent->getPaoWorldpos().distance(sp->getPosition());

	Point curPos = GameManage::getInstance()->getGuiLayer()->getItemPos(itemid);



	sp->runAction(Sequence::create(Spawn::create(MoveBy::create(0.5f, Vec2(0, 0)), ScaleTo::create(0.5f, 1.0f), nullptr), EaseExponentialIn::create(MoveTo::create(1.0f, curPos)), CallFunc::create([=]
	{
		BagManager::getInstance()->addreward(itemid, num);
		if (itemid==1001)
		{
			turrent->ShowAddCoinAni(1, num);
		}
		else if (itemid == 1002)
		{
			turrent->ShowAddCoinAni(2, num);
			if (User::getInstance()->getMaxTurrentLevel()==1&&!NewbieMannger::getInstance()->getisTeachUpgradeTurrent())
			{
				NewbieMannger::getInstance()->setisTeachUpgradeTurrent(1);
				GameManage::getInstance()->getGuiLayer()->ShowUpgradeTurretTip();
			}


		}
		
	}), RemoveSelf::create(1), nullptr));

}