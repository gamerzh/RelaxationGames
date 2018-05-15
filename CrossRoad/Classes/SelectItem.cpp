#include "SelectItem.h"

SelectItem* SelectItem::create(int type) {
	auto ret = new SelectItem();
	if (ret && ret->init(type)) {
		ret->autorelease();
		return ret;
	}
	else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool SelectItem::init(int type) {
	if (!Node::init()) {
		return false;
	}

	this->type = type;
	auto win = Director::getInstance()->getWinSize();

	auto box = Sprite::create("skin_box.png");
	box->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	box->setPosition(win.width/20, 0);
	addChild(box);

	auto name = Label::createWithSystemFont("HHHHHH", "arial", 40);
	name->setColor(Color3B(0,0,0));
	name->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	name->setPosition(win.width*0.26, 80);
	addChild(name);

	auto hint = Label::createWithSystemFont("HHHHHH", "arial", 20);
	hint->setColor(Color3B(0, 0, 0));
	hint->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	hint->setPosition(win.width *0.26, 10);
	addChild(hint);

	//auto btn = MenuItemImage::create("btn_kong.png", "btn_kong.png", CC_CALLBACK_0(SelectItem::useModle, this));
	//btn->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	//auto boxMenu = Menu::create(btn, NULL);
	//boxMenu->setPosition(win.width*0.58,50);
	//addChild(boxMenu);

	return  true;
}


void SelectItem::useModle() {

}