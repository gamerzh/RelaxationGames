#include "DreamNode.h"

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
	auto win = Director::getInstance()->getWinSize();
	setDreamId(dreamId);
	auto bg = Sprite::create("black_a.png");
	bg->setPosition(pos);
	addChild(bg);

	auto content = Sprite::create(getContentById(dreamId));
	content->setPosition(pos);
	addChild(content);


	auto button = MenuItemImage::create(getButtonById(dreamId), getButtonById(dreamId),CC_CALLBACK_0(DreamNode::doActionById,this));
	auto menu = Menu::create(button,NULL);
	menu->setPosition(pos.x, pos.y/2);
	addChild(menu);


	auto close = MenuItemImage::create("dream_btn_c.png", "dream_btn_c.png",CC_CALLBACK_0(DreamNode::closeView,this));
	auto closeMenu = Menu::create(close, NULL);
	closeMenu->setPosition(pos.x+245, pos.y +270);
	addChild(closeMenu);

	Director::getInstance()->pause();

	return true;
}


void DreamNode::doActionById() {

}

void DreamNode::closeView() {
	Director::getInstance()->resume();
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
		return "dream_6.png";
	case 7:
		return "dream_7.png";
	case 9:
		return "dream_8.png";
	default:
		return "dream_1.png";
	}
}

std::string DreamNode::getButtonById(int dreamId) {
	switch (dreamId)
	{
	case 1:
		return "dream_btn_1.png";
	case 2:
		return "dream_btn_1.png";
	case 3:
		return "dream_btn_3.png";
	case 5:
		return "dream_btn_1.png";
	case 6:
		return "dream_btn_2.png";
	case 7:
		return "dream_btn_7.png";
	case 9:
		return "dream_btn_1.png";
	default:
		return "dream_btn_1.png";
	}
}