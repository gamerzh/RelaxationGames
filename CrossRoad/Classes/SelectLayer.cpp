#include "SelectLayer.h"
#include "SelectItem.h" 


bool SelectLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	loadView();
	return true;
}

void SelectLayer::loadView() {
	 
	auto win = Director::getInstance()->getWinSize();

	auto black = LayerColor::create(Color4B(0, 0, 0, 150), win.width, win.height);
	addChild(black);

	auto swa = MenuItem::create();
	swa->setContentSize(Size(win.width, win.height));
	auto swam = Menu::create(swa, NULL);
	addChild(swam);

	auto bg = Sprite::create("skin_box_bg.png");
	bg->setPosition(win.width/2, win.height/2);
	addChild(bg);

	auto close = MenuItemImage::create("btn_close.png","btn_close.png",CC_CALLBACK_0(SelectLayer::closeView,this));
	auto closeMenu = Menu::create(close, NULL);
	closeMenu->setPosition(win.width * 0.85, win.height * 0.84);
	addChild(closeMenu);

	for (int i = 0; i < 2; i++)
	{
		SelectItem* item = SelectItem::create(i);
		item->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		item->setPosition(win.width/10, win.height*0.675- win.height*0.168*i);
		addChild(item);
	}
}


void SelectLayer::closeView() {
	removeFromParent();
}

