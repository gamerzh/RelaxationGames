#include "DreamConfirm.h"
#include "Dream.h"
#include "DreamEvent.h"
#include "GameStatus.h"
#include "GameOver.h"

DreamConfirm* DreamConfirm::create(int dreamId, Vec2 pos) {
	DreamConfirm* ret = new DreamConfirm();
	if (ret && ret->init(dreamId, pos)) {
		ret->autorelease();
		return ret;
	}
	else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool DreamConfirm::init(int dreamId, Vec2 pos) {
	if (!Node::init()) {
		return false;
	}
	Director::getInstance()->pause();

	dream_id = dreamId;
	auto win = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("black_a.png");
	bg->setAnchorPoint(Vec2(0.5,0.5));
	bg->setPosition(pos);
	addChild(bg);

	auto cont = Sprite::create();
	if (dreamId == 6) {
		cont->setTexture("shengmi_2.png");
	}
	else {
		cont->setTexture("fuhuo_2.png");
	}
	cont->setPosition(pos);
	addChild(cont);

	auto confirm = MenuItemImage::create("gou.png", "gou.png", CC_CALLBACK_0(DreamConfirm::confirmDream, this));
	auto cancel = MenuItemImage::create("cancel.png", "cancel.png", CC_CALLBACK_0(DreamConfirm::closeView, this));
	auto confirmMenu = Menu::create(confirm, cancel, NULL);
	confirmMenu->setPosition(pos.x,pos.y-200);
	confirmMenu->alignItemsHorizontallyWithPadding(30);
	addChild(confirmMenu);

	return true;
}


void DreamConfirm::confirmDream() {
	if (dream_id == 6) {
		//нч╣п
		Dream::getInstance()->recordEvent(jfd_6_pay, jfd_6_pay);
		GameStatus::getInstance()->setInvincible(true);
		Dream::getInstance()->requestEvent(dream_id);
	}
	else if (dream_id  == 7) {
		Dream::getInstance()->recordEvent(jfd_7_pay, jfd_7_pay);
		GameStatus::getInstance()->setInvincible(true);
		GameStatus::getInstance()->setResurgence(true);
		Dream::getInstance()->requestEvent(dream_id);
	}
	Director::getInstance()->resume();
	removeFromParent();
}

void DreamConfirm::closeView() {
	if (dream_id == 7) {
		auto over = GameOver::create();
		over->setTag(100);
		addChild(over);
	}
	else {
		Director::getInstance()->resume();
		removeFromParent();
	}
}