#include "ShopCell.h"
#include "ChineseWorld.h"
#include "User.h"
#include "GameFlow.h"
#include "PxPayMannger.h"
#include "Jniutill.h"
ShopCell*ShopCell::create(PropItem item)
{
	ShopCell*cell = new (std::nothrow)ShopCell();
	if (cell&&cell->init(item))
	{
		cell->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(cell);
		cell = nullptr;
	}
	return cell;
}



bool ShopCell::init(PropItem item)
{
	if (!Node::init())
	{
		return false;
	}
	_item =item;
	//bg
	auto str = String::createWithFormat("shopItem_%d.png",item.index);
	auto bg = Sprite::create(str->getCString());
	bg->setPosition(Point::ZERO);
	auto bgsize = bg->getContentSize();
	addChild(bg,0,"bg");

	//bt
	//auto bt = MenuItemImage::create("bt_shopcell_1.png", "bt_shopcell_2.png", [=](Ref*psend)
	//{
	//	PxPayMannger::getInstance()->doWxPay(item.Paypoint);

	//});
	//bt->setPosition(bgsize.width / 2, bgsize.height*0.13);
	//auto menu = Menu::create(bt, nullptr);
	//menu->setPosition(0, 0);
	//bg->addChild(menu);
	auto bt = Sprite::create("bt_shopcell_1.png");
	bt->setPosition(bgsize.width / 2, bgsize.height*0.13);
	bg->addChild(bt);
	auto btDescPath = String::createWithFormat("bt_price_%d.png", item.index);
	auto btDesc = Sprite::create(btDescPath->getCString());
	btDesc->setPosition(bt->getContentSize() / 2);
	bt->addChild(btDesc);
	

	return true;
}

void ShopCell::onTouched()
{
	CCLOG("shopcell id = %d is be touched", _item.Paypoint);
	PxPayMannger::getInstance()->doWxPay(_item.Paypoint);
}

Rect ShopCell::getTouchRect()
{
	return getChildByName("bg")->getBoundingBox();
}