#include "RulePanel.h"
bool RulePanel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->setVisible(false);
	

	//LayerColor* layerColor = CCLayerColor::create();
	//layerColor->setColor(ccc3(0, 0, 0));
	//layerColor->setOpacity(180);
	//layerColor->setContentSize(CCSizeMake(800, 480));
	//this->addChild(layerColor,-2);
	auto visibisize = Director::getInstance()->getVisibleSize();
	Sprite* frame = Sprite::create("Rule/Rule_Bottom.png");
	frame->setPosition(visibisize / 2);
	this->addChild(frame,-1);
	auto title = Sprite::create("Rule/Rule_Title.png");
	title->setPosition(visibisize.width/2, 430);
	addChild(title);
	auto txt = Sprite::create("Rule/Rule_Text.png");
	txt->setPosition(visibisize.width / 2, visibisize.height / 2);
	addChild(txt);

	Menu* menu = Menu::create();
	menu->ignoreAnchorPointForPosition(true);
	menu->setPosition(.0f, .0f);
	this->addChild(menu);



	showPanel();

	auto close = MenuItemImage::create("SetSound/Close_0.png", "SetSound/Close_1.png", [=](Ref*psend){removeFromParentAndCleanup(1); });
	close->setPosition(685, 420);
	menu->addChild(close);

	this->setPosition(400.0f, 240.0f);
	for (auto child :getChildren())
	{
		child->setPosition(child->getPosition() - getPosition());
	}
	//´¥ÃþÆÁ±Î
	listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = [=](Touch*touch, Event*event){return true; };
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
	return true;
}

void RulePanel::showPanel()
{
	this->setScale(.0f);
	this->setVisible(true);
	this->runAction(ScaleTo::create(time, 1.0f));
}
void RulePanel::hidePanel()
{
	this->runAction(Sequence::create(ScaleTo::create(time, .0f),RemoveSelf::create(true), NULL));
}
