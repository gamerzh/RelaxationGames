#include "PayingDialog.h"
#include "domain/pay/Pay.h"

PayingDialog*  PayingDialog::ShowPayDialog()
{
	auto dialog = PayingDialog::create();
	dialog->setPosition(0,0);
	Director::getInstance()->getRunningScene()->addChild(dialog, 29);
	dialog->setName("payingFrame");
	return dialog;
}
void PayingDialog::RemovePayDialog()
{
	auto circle = Director::getInstance()->getRunningScene()->getChildByName("payingFrame");
	if (circle)
	{
		circle->removeFromParentAndCleanup(1);
	}
	else
	{
		return;
	}
	
}


bool PayingDialog::init()
{
	Node::init();
	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	addChild(colorlayer, -1);

	auto bg = Sprite::create("payreq.png");
	bg->setPosition(480, 270);
	addChild(bg, 1);


	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(PayingDialog::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
	return true;
}
