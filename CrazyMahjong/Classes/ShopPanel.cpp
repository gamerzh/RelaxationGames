#include "ShopPanel.h"
#include "ShopCell.h"
#include "PxPayMannger.h"
bool ShopPanel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->setVisible(false);
	LayerColor* layerColor = CCLayerColor::create();
	layerColor->setColor(ccc3(0, 0, 0));
	layerColor->setOpacity(180);
	layerColor->setContentSize(CCSizeMake(800, 480));
	this->addChild(layerColor,-2);
	auto visibisize = Director::getInstance()->getVisibleSize();
	Sprite* frame = Sprite::create("shop_bg.png");
	frame->setPosition(visibisize / 2);
	this->addChild(frame);
	auto title = Sprite::create("shop_Title.png");
	title->setPosition(visibisize.width/2, 430);
	addChild(title);



	Menu* menu = Menu::create();
	menu->ignoreAnchorPointForPosition(true);
	menu->setPosition(.0f, .0f);
	this->addChild(menu);


	/////create cell

	auto vec = this->getPropItems();
	float startx =100;
	auto bgsize = frame->getContentSize();
	float difx = (bgsize.width - 40.0f) /5.0f;
	for (int i = 1; i < 6;i++)
	{
		auto cell = ShopCell::create(vec.at(i - 1));
		cell->setPosition(Point(startx, bgsize.height*0.5));
		startx += difx;
		frame->addChild(cell);
		cells.push_back(cell);
	}


	showPanel();

	auto close = MenuItemImage::create("SetSound/Close_0.png", "SetSound/Close_1.png", [=](Ref*psend){hidePanel(); });
	close->setPosition(735, 405);
	menu->addChild(close);

	this->setPosition(400.0f, 240.0f);
	for (auto child :getChildren())
	{
		child->setPosition(child->getPosition() - getPosition());
	}

	//´¥ÃþÆÁ±Î
	listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(ShopPanel::onTouchBegin,this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

	auto listern2 = EventListenerKeyboard::create();
	listern2->onKeyReleased = [=](EventKeyboard::KeyCode  keyCode, Event *event)
	{
		event->stopPropagation();
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
		{
			removeFromParentAndCleanup(1);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listern2, this);

	Jniutill::getInstance()->logEventShowPayPanel(-1,1);
	return true;
}

void ShopPanel::showPanel()
{
	this->setScale(.0f);
	this->setVisible(true);
	this->runAction(ScaleTo::create(time, 1.0f));
}
void ShopPanel::hidePanel()
{
	this->runAction(Sequence::create(ScaleTo::create(time, .0f),RemoveSelf::create(true), NULL));
}
std::vector<PropItem> ShopPanel::getPropItems()
{
	std::vector<PropItem> vec;
	PayItem payitem = PxPayMannger::getItemByPaypoint(VIPGIFT);
	PropItem item;
	item.index = 1; 
	item.Paypoint = VIPGIFT;
	item.payType = payitem.PPpropType;
	item.price = payitem.PPrice;
	item.propNum = payitem.PPropNum;
	vec.push_back(item);

	payitem = PxPayMannger::getItemByPaypoint(COIN_18);
	item.index = 2;
	item.Paypoint = COIN_18;
	item.payType = payitem.PPpropType;
	item.price = payitem.PPrice;
	item.propNum = payitem.PPropNum;
	vec.push_back(item);

	payitem = PxPayMannger::getItemByPaypoint(COIN_28);
	item.index = 3;
	item.Paypoint = COIN_28;
	item.payType = payitem.PPpropType;
	item.price = payitem.PPrice;
	item.propNum = payitem.PPropNum;
	vec.push_back(item);


	payitem = PxPayMannger::getItemByPaypoint(COIN_58);
	item.index = 4;
	item.Paypoint = COIN_58;
	item.payType = payitem.PPpropType;
	item.price = payitem.PPrice;
	item.propNum = payitem.PPropNum;
	vec.push_back(item);

	payitem = PxPayMannger::getItemByPaypoint(COIN_88);
	item.index = 5;
	item.Paypoint = COIN_88;
	item.payType = payitem.PPpropType;
	item.price = payitem.PPrice;
	item.propNum = payitem.PPropNum;
	vec.push_back(item);

	return vec;
}
bool ShopPanel::onTouchBegin(Touch*touch, Event*event)
{
	Vec2 pos = touch->getLocation();
	for (auto var:cells)
	{
		auto nodePos=var->convertToNodeSpace(pos);
		if (var->getTouchRect().containsPoint(nodePos))
		{
			var->onTouched();
			return true;
		}
	}
	return true;

}