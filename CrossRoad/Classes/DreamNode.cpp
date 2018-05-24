#include "DreamNode.h"
#include "UserData.h"
#include "Dream.h"
#include "DreamEvent.h"
#include "GameStatus.h"
#include "GameOver.h"
#include "DreamConfirm.h"

DreamNode* DreamNode::create(int dreamId, Vec2 pos) {
	DreamNode* ret = new DreamNode();
	if (ret && ret->init(dreamId, pos)) {
		ret->autorelease();
		return ret;
	}
	else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}


bool DreamNode::init(int dreamId, Vec2 pos) {
	if (!Node::init()) {
		return false;
	}
	position = pos;
	setDreamId(dreamId);

	auto win = Director::getInstance()->getWinSize();
	auto bg = Sprite::create("black_a.png");
	bg->setPosition(pos);
	addChild(bg);


	auto swa = MenuItem::create();
	swa->setContentSize(Size(win.width, win.height));
	auto swam = Menu::create(swa, NULL);
	addChild(swam);

	auto mm = Sprite::create("jxb.png");
	mm->setAnchorPoint(Vec2(0, 0));
	mm->setOpacity(40);
	mm->setPosition(pos.x-355,pos.y-635);
	addChild(mm);

	Director::getInstance()->pause();

	if (dreamId != 3) {
		auto content = Sprite::create(getContentById(dreamId));
		content->setPosition(pos);
		addChild(content);

		auto quan = MenuItem::create(CC_CALLBACK_0(DreamNode::doActionById, this));
		quan->setContentSize(Size(win.width, win.height));
		auto quanMenu = Menu::create(quan, NULL);
		quanMenu->setPosition(pos.x, pos.y);
		addChild(quanMenu);

		auto button = MenuItemImage::create(getButtonById(dreamId), getButtonById(dreamId), CC_CALLBACK_0(DreamNode::doActionById, this));
		auto menu = Menu::create(button, NULL);
		menu->setPosition(pos.x, pos.y - 300);
		addChild(menu);
		if (Dream::getInstance()->getGameDreamTimes()) {
			quan->setEnabled(false);
			mm->setVisible(false);
			auto cancel = MenuItemImage::create("cancel.png", "cancel.png", CC_CALLBACK_0(DreamNode::closeView, this));
			menu->addChild(cancel);
			menu->alignItemsHorizontallyWithPadding(30);
		}
	}
	else {
		Director::getInstance()->resume();

		auto turntable = Sprite::create("zhuanpan.png");
		turntable->setTag(1024);
		turntable->setPosition(pos);
		addChild(turntable);

		auto quan = MenuItem::create(CC_CALLBACK_0(DreamNode::startPride, this));
		quan->setContentSize(Size(win.width, win.height));
		auto start = MenuItemImage::create("zhuanpan_btn.png", "zhuanpan_btn.png", CC_CALLBACK_0(DreamNode::startPride, this));
		start->setAnchorPoint(Point::ANCHOR_MIDDLE);
		auto startMenu = Menu::create(quan,start, NULL);
		startMenu->setPosition(pos.x, pos.y + 30);
		addChild(startMenu);

	}
	if (!Dream::getInstance()->getGameDreamTimes()) {
		auto close = MenuItemImage::create("dream_btn_c.png", "dream_btn_c.png", CC_CALLBACK_0(DreamNode::closeView, this));
		auto closeMenu = Menu::create(close, NULL);
		closeMenu->setPosition(pos.x + 260, pos.y + 300);
		addChild(closeMenu, 2);
	}

	if (getDreamId() == 1) {
		Dream::getInstance()->recordEvent(jfd_1_show, jfd_1_show);
	}
	else if (getDreamId() == 2) {
		Dream::getInstance()->recordEvent(jfd_2_show, jfd_2_show);
	}
	else if (getDreamId() == 3) {
		Dream::getInstance()->recordEvent(jfd_3_show, jfd_3_show);
	}
	else if (getDreamId() == 5) {
		Dream::getInstance()->recordEvent(jfd_5_show, jfd_5_show);
	}
	else if (getDreamId() == 6) {
		Dream::getInstance()->recordEvent(jfd_6_show, jfd_6_show);
	}
	else if (getDreamId() == 7) {
		Dream::getInstance()->recordEvent(jfd_7_show, jfd_7_show);
	}
	else if (getDreamId() == 9) {
		Dream::getInstance()->recordEvent(jfd_9_show, jfd_9_show);
	}
	else if (getDreamId() == 10) {
		Dream::getInstance()->recordEvent(jfd_10_show, jfd_10_show);
	}


	return true;
}


void DreamNode::doActionById() {
	//开始执行dream代码
	Director::getInstance()->resume();
	auto win = Director::getInstance()->getWinSize();
	if (getDreamId() == 1 ) {
		//玩家金币加100
		Dream::getInstance()->recordEvent(jfd_1_pay, jfd_1_pay);
		UserData::getInstance()->setPlayerGoldNum(100 + UserData::getInstance()->getPlayerGoldNum());
		Dream::getInstance()->requestEvent(getDreamId());

		auto login = DreamNode::create(2, Vec2(win.width / 2, win.height / 2));
		getParent()->addChild(login);
	}
	else if (getDreamId() == 2) {
		Dream::getInstance()->recordEvent(jfd_2_pay, jfd_2_pay);
		UserData::getInstance()->setPlayerGoldNum(100 + UserData::getInstance()->getPlayerGoldNum());
		Dream::getInstance()->requestEvent(getDreamId());
		auto login = DreamNode::create(3, Vec2(win.width / 2, win.height / 2));
		getParent()->addChild(login);
	}
	else if (getDreamId() == 5) {
		// 双倍道具
		Dream::getInstance()->recordEvent(jfd_5_pay, jfd_5_pay);
		GameStatus::getInstance()->setDoubleScore(true);
		Dream::getInstance()->requestEvent(getDreamId());
	
	}
	else if (getDreamId() == 6) {
		//无敌
		if (!Dream::getInstance()->getGameDreamTimes()) {
			Dream::getInstance()->recordEvent(jfd_6_pay, jfd_6_pay);
			GameStatus::getInstance()->setInvincible(true);
			Dream::getInstance()->requestEvent(getDreamId());
		}
		else {
			auto infi = DreamConfirm::create(6, Vec2(win.width / 2, win.height / 2));
			//infi->setCameraMask((int)CameraFlag::USER1);
			getParent()->addChild(infi);
		}
	}
	else if (getDreamId() == 7) {
		//复活和无敌
		if (!Dream::getInstance()->getGameDreamTimes()) {
			Dream::getInstance()->recordEvent(jfd_7_pay, jfd_7_pay);
			GameStatus::getInstance()->setInvincible(true);
			GameStatus::getInstance()->setResurgence(true);
			Dream::getInstance()->requestEvent(getDreamId());
		}
		else {
			auto infi = DreamConfirm::create(7, Vec2(win.width / 2, win.height / 2));
			//infi->setCameraMask((int)CameraFlag::USER1);
			getParent()->addChild(infi);
		}
	}
	else if (getDreamId() == 9) {
		Dream::getInstance()->recordEvent(jfd_9_pay, jfd_9_pay);
		UserData::getInstance()->setPlayerGoldNum(100 + UserData::getInstance()->getPlayerGoldNum());
		Dream::getInstance()->requestEvent(getDreamId());
	}
	else if (getDreamId() == 10) {
		Dream::getInstance()->recordEvent(jfd_10_pay, jfd_10_pay);
		Dream::getInstance()->requestEvent(getDreamId());
	}
	removeFromParent();
}

void DreamNode::startPride() {
	if (NULL != getChildByTag(1024) && !isHavePride) {
		isHavePride = true;
		auto spr = (Sprite*)getChildByTag(1024);
		auto step1 = RotateTo::create(2, 360 * 10);
		auto repe = Repeat::create(step1, CC_REPEAT_FOREVER);
		spr->runAction(repe);
		auto nod = Node::create();
		addChild(nod);
		auto seq = Sequence::create(DelayTime::create(2), CallFunc::create([=]() {
			spr->stopAllActions();
			int result = random(1, 3);
			if (result == 3) {
				result = 300;
			}
			else if (result == 2) {
				result = 180;
			}
			else {
				result = 60;
			}
			spr->setRotation(result);
			//玩家金币加100
			Dream::getInstance()->recordEvent(jfd_3_pay, jfd_3_pay);
			Director::getInstance()->resume();
			UserData::getInstance()->setPlayerGoldNum(100 + UserData::getInstance()->getPlayerGoldNum());
			Dream::getInstance()->requestEvent(getDreamId());
			this->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([=]() {
				removeFromParent();
			}), NULL));
		}), NULL);
		nod->runAction(seq);
	}
}

void DreamNode::closeView() {
	Director::getInstance()->resume();
	auto win = Director::getInstance()->getWinSize();
	if (getDreamId() == 1) {
		Dream::getInstance()->recordEvent(jfd_1_close, jfd_1_close);
		auto login = DreamNode::create(2, Vec2(win.width / 2, win.height / 2));
		getParent()->addChild(login);
	}
	else if (getDreamId() == 2) {
		Dream::getInstance()->recordEvent(jfd_2_close, jfd_2_close);
		auto login = DreamNode::create(3, Vec2(win.width / 2, win.height / 2));
		getParent()->addChild(login);
	}
	else if (getDreamId() == 3) {
		Dream::getInstance()->recordEvent(jfd_3_close, jfd_3_close);
	}
	else if (getDreamId() == 5) {
		Dream::getInstance()->recordEvent(jfd_5_close, jfd_5_close);
	}
	else if (getDreamId() == 6) {
		Dream::getInstance()->recordEvent(jfd_6_close, jfd_6_close);
	}
	else if (getDreamId() == 7) {
		//复活和无敌
		Dream::getInstance()->recordEvent(jfd_7_close, jfd_7_close);
		auto over = GameOver::create();
		over->setTag(100);
		getParent()->addChild(over);
	}
	else if (getDreamId() == 9) {
		Dream::getInstance()->recordEvent(jfd_9_close, jfd_9_close);
	}
	else if (getDreamId() == 10) {
		Dream::getInstance()->recordEvent(jfd_10_close, jfd_10_close);
		Dream::getInstance()->quitGame();
	}
	removeFromParent();
}


std::string DreamNode::getContentById(int dreamId) {
	switch (dreamId)
	{
	case 1:
		return "dream_1.png";
	case 2:
		return "dream_2.png";
	case 3:
		return "dream_3.png";
	case 5:
		return "dream_4.png";
	case 6:
	{
		if (!Dream::getInstance()->getGameDreamTimes()) {
			return "dream_6.png";
		}
		else {
			return "shenmi_second.png";
		}
	}
		
	case 7:
		if (!Dream::getInstance()->getGameDreamTimes()) {
			return "dream_7.png";
		}
		else {
			return "fuhuo_second.png";
		}
	case 9:
		return "dream_8.png";
	case 10:
		return "dream_10.png";
	default:
		return "dream_1.png";
	}
}

std::string DreamNode::getButtonById(int dreamId) {
	switch (dreamId)
	{
	case 6:
		if (!Dream::getInstance()->getGameDreamTimes()) {
			return "dream_btn_1.png";
		}
		else {
			return "gou.png";
		}
	case 7:
		if (!Dream::getInstance()->getGameDreamTimes()) {
			return "dream_btn_1.png";
		}
		else {
			return "gou.png";
		}
	default:
		return "dream_btn_1.png";
	}
}