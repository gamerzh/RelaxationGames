#include "RoomCell.h"
#include "utill/FunUtil.h"
#include "utill/Audio.h"
#include "data/GameData.h"
#include "utill/Chinese.h"
#include "core/GameScene.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "domain/bankrupt/BankruptManager.h"
#include "domain/loading/LoadingSceneLbToGm.h"
RoomCell*RoomCell::createCell(Room room)
{
	RoomCell*cell = new RoomCell();
	if (cell&&cell->init(room))
	{
		cell->autorelease();
	}
	else
	{
		cell = nullptr;
	}
	return cell;
}

bool RoomCell::init(Room room)
{
	m_room = room;
	auto str = String::createWithFormat("level_%d.png", m_room.room_id);
	initWithFile(str->getCString());
	playNormalAni();//播放基准动画
	setPlayerNum();//虚构房间人数
	lockRoom();//房间上锁
	return true;
}
RoomCell::~RoomCell()
{
	anis.clear();
}
void RoomCell::setShade(bool isShade)
{
	auto color = isShade ? Color3B(128, 128, 128) : Color3B(255, 255, 255);
	setColor(color);
	getChildByName("onLinePlayer")->setColor(color);
	getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(color);
	if (isLock)
	{
		getChildByName("lock")->setColor(color);
	}
	
}
void RoomCell::isBeClicked()
{
	Audio::getInstance()->playSound(CLICKSURE);
	if (isLock)
	{
		auto layer = TwiceSureDialog::createDialog(ChineseWord("enterRoomTip").c_str(),CC_CALLBACK_1(RoomCell::TiPCallBack,this));
		layer->setPosition(-480,-270);
		getParent()->addChild(layer, 10, "tip");
	}
	else
	{
		auto node = BankruptManager::getInstance()->getgetRewardNode();
		if (node)
		{
			node->retain();
			node->removeFromParentAndCleanup(false);

		}
		GameData::getInstance()->setRoomID(m_room.room_id);
		if (GameData::getInstance()->getisLoadMsgOnGame())
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
		}
		else
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1, LoadingSceneLbToGm::createScene()));
		}
	}
	
}
void RoomCell::setPlayerNum()
{
	
	
	///设置房间人数

	int nHour = SystemTime::getNowHour();
	int nPlayerNum = ConfigRoom::getInstance()->getPlayerCounts(nHour, m_room.room_id);
	auto sp = Sprite::create("onLinePlayer.png");
	sp->setPosition(getContentSize().width*0.4, getContentSize().height*0.14);
	addChild(sp, 0, "onLinePlayer");
	auto label = LabelAtlas::create(Value(nPlayerNum).asString().c_str(), "onLineNum.png", 13, 20, '0');
	label->setAnchorPoint(Point::ZERO);
	label->setPosition(sp->getContentSize().width, 3);
	sp->addChild(label, 0, "onLinePlayCount");
}
void RoomCell::lockRoom()
{
	//加锁和
	setIslock(false);;
	auto userLevel = User::getInstance()->getMaxTurrentLevel();
	if (userLevel < m_room.unlock_turrent_level)
	{
		auto lock = Sprite::create("lock.png");
		lock->setPosition(getContentSize().width*0.2, getContentSize().height*0.8);
		addChild(lock,0,"lock");
		setIslock(true);
	}
	
}
void RoomCell::resumeNormalAni()
{
	for (auto var : anis)
	{
		var->setVisible(true);
	}
	if (m_room.room_id==4)
	{
		IsloveOn = true;
	}

}
void RoomCell::stopNormalAni()
{
	for (auto var:anis)
	{
		var->setVisible(false);
			var->retain();
	}
	IsloveOn = false;
	auto ac = getActionByTag(888);
	if (ac)
	{
		stopActionByTag(888);
	}
	if (roomCircleLight)
	{
		roomCircleLight->removeFromParentAndCleanup(1);
		roomCircleLight = nullptr;
	}
	
	
}
void RoomCell::playNormalAni()
{

	if (m_room.room_id != 1)
	{
		auto aniNode = Sprite::create();
		aniNode->setPosition(getContentSize() / 2);
		addChild(aniNode);
		auto str = String::createWithFormat("aniRoom_id%d", m_room.room_id);
		auto ac = AnimationUtil::getInstance()->getAnimate(str->getCString());
		if (ac)
		{
			aniNode->runAction(RepeatForever::create(Sequence::create(ac,DelayTime::create(1.0f),nullptr)));
		}
		anis.push_back(aniNode);
	}
	

	auto paopaoNode = Sprite::create();
	paopaoNode->setScale(1.4);
	paopaoNode->setPosition(getContentSize().width / 2, getContentSize().height / 2);
	paopaoNode->runAction(RepeatForever::create(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniBubble"), nullptr)));
	addChild(paopaoNode);
	anis.push_back(paopaoNode);
	switch (m_room.room_id)
	{
	case 1:
	{

		auto lightsp = Sprite::create();
		lightsp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), AnimationUtil::getInstance()->getAnimate("aniLightPoint"), nullptr)));
		lightsp->setPosition(50, 135);
		addChild(lightsp);
		anis.push_back(lightsp);
		lightsp = Sprite::create();
		
		lightsp->setPosition(250, 185);
		anis.push_back(lightsp);
		addChild(lightsp);
		scheduleOnce([=](float interval)
		{
			lightsp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), AnimationUtil::getInstance()->getAnimate("aniLightPoint"), nullptr)));
		}, 0.5f,"11");

	}
	break;
	case 2:
	{
		auto lightsp = Sprite::create();
		lightsp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), AnimationUtil::getInstance()->getAnimate("aniLightPoint"), nullptr)));
		lightsp->setPosition(270, 93);
	addChild(lightsp);
	anis.push_back(lightsp); 
	lightsp = Sprite::create();
	
	lightsp->setPosition(50, 85);
	addChild(lightsp);
	anis.push_back(lightsp);
		scheduleOnce([=](float interval)
		{
			lightsp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), AnimationUtil::getInstance()->getAnimate("aniLightPoint"), nullptr)));
		}, 0.5f, "11");
		auto catNode = Sprite::create();
		catNode->setPosition(getContentSize() / 2);
	addChild(catNode);
	anis.push_back(catNode);
		catNode->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.2f), AnimationUtil::getInstance()->getAnimate("anicapLight"), nullptr)));
	}
	break;
	case 3:
	{
		auto lightsp = Sprite::create();
		lightsp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), AnimationUtil::getInstance()->getAnimate("aniLightPoint"), nullptr)));
		lightsp->setPosition(80, 112);
	addChild(lightsp, 1);
	anis.push_back(lightsp);
lightsp = Sprite::create();
	
	lightsp->setPosition(210, 185);
	addChild(lightsp, 1);
	anis.push_back(lightsp);
		scheduleOnce([=](float interval)
		{
			lightsp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), AnimationUtil::getInstance()->getAnimate("aniLightPoint"), nullptr)));
		}, 0.5f, "11");
		caidai = Sprite::create();
		caidai->setPosition(getContentSize().width/2,getContentSize().height*0.8);
	addChild(caidai);
	anis.push_back(caidai);
		caidai->runAction(RepeatForever::create(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniCaidai"), nullptr)));
	}
	break;
	case 4:
	{
		auto lightsp = Sprite::create();
		lightsp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), AnimationUtil::getInstance()->getAnimate("aniLightPoint"), nullptr)));
		lightsp->setPosition(62, 102);
	addChild(lightsp);
	anis.push_back(lightsp);
	lightsp = Sprite::create();

	lightsp->setPosition(192, 178);
	addChild(lightsp);
	anis.push_back(lightsp);
		scheduleOnce([=](float interval)
		{
				lightsp->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), AnimationUtil::getInstance()->getAnimate("aniLightPoint"), nullptr)));
		}, 0.5f, "11");
		auto ac = RepeatForever::create(Sequence::create(DelayTime::create(0.8f), CallFunc::create([&]{
			auto ac = Sequence::create(Spawn::create(MoveBy::create(2.4f, Vec2(0, 330)), FadeOut::create(2.4f), nullptr), RemoveSelf::create(), nullptr);
			auto love = Sprite::create("love.png");
			love->setPosition(getRandonNumByAtoB(getContentSize().width*0.3, getContentSize().width*0.7), 40);
			love->runAction(ac);
			love->setVisible(IsloveOn);
			addChild(love);
		}), nullptr));
			ac->setTag(889);
		runAction(ac);
	}
	break;
	default:
		break;
	}
}
void RoomCell::playScaleAni()
{
	auto ac = RepeatForever::create(Sequence::create(ScaleTo::create(0.17f, 1.1), ScaleTo::create(0.13f, 0.81), ScaleTo::create(0.13f, 1.1), ScaleTo::create(0.13f, 1),DelayTime::create(4.0f),nullptr));
	ac->setTag(888);
	runAction(ac);
	roomCircleLight = Sprite::create("roomCircleLight.png");
	roomCircleLight->setPosition(Vec2(500 - 480, -30));
	roomCircleLight->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	getParent()->addChild(roomCircleLight);
	roomCircleLight->runAction(RepeatForever::create(Sequence::create(Spawn::create(ScaleTo::create(1.5f, 3), FadeOut::create(1.5f), nullptr), DelayTime::create(0.0f), ScaleTo::create(0.0001f, 1), FadeIn::create(0.0001f), nullptr)));
}

void RoomCell::TiPCallBack(Ref*psend)
{
	auto node = getParent()->getChildByName("tip");
	node->removeFromParentAndCleanup(1);
}