#include "VipGainCoinSureDialog.h"
#include "lobby/LobbyScene.h"
#include "utill/Chinese.h"
#include "utill/FunUtil.h"
#include "lobby/signlayer/SignInLayer.h"
#include "domain/user/User.h"
#include "config/ConfigVipLevel.h"
bool VipGainCoinSureDialog::init()
{

	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	addChild(colorlayer, -1);

	auto bg = Sprite::create("TwiceSureDialog.png");
	bg->setPosition(480, 270);
	bg->setName("bg");
	addChild(bg);



	auto sure = MenuItemImage::create("btn_queding.png", "btn_queding_2.png");
	sure->setPosition(bg->getContentSize().width / 2, 45);
	sure->setCallback(CC_CALLBACK_1(VipGainCoinSureDialog::sureButtonCallBack, this));
	
	auto menu = Menu::create(sure, nullptr);
	menu->setPosition(0,0);
	bg->addChild(menu,1);


	auto label = LabelTTF::create(ChineseWord("VIPGainTheCoins").c_str(), "arial", 21);
	auto vipsp = Sprite::create("VIPtxt.png");
	vipsp->setScale(0.8);
	vipsp->setPosition(128, 177);
	bg->addChild(vipsp);
	label->setColor(Color3B(12, 64, 109));
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	label->setDimensions(Size(299, 0));
	label->setPosition(bg->getContentSize().width / 2, 155);
	bg->addChild(label);

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(VipGainCoinSureDialog::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	/////////弹出动画
	bg->setScale(0);
	bg->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), nullptr));
	showRandonBubbleAni();
	return true;
}


void VipGainCoinSureDialog::sureButtonCallBack(Ref*psend)
{
	getChildByName("bg")->removeFromParentAndCleanup(1);
	Vec2 pos = Vec2(480, 290);
	for (int i = 0; i < 15; i++)
	{
		auto aniCoin = Sprite::create();
		aniCoin->setPosition(pos.x + 40 * (rand_0_1() - 0.5), pos.y);
		aniCoin->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGold")));
		aniCoin->runAction(Sequence::create(DelayTime::create(0.05f*i), MoveBy::create(0.23f, Vec2(0, 86)), MoveBy::create(0.13f, Vec2(0, -86)), MoveBy::create(0.1f, Vec2(0, 27.5)), MoveBy::create(0.1f, Vec2(0, -27.5)), DelayTime::create(0.6f), MoveTo::create(0.16f, Vec2(285, 515)), RemoveSelf::create(1), nullptr));
		addChild(aniCoin);
	}
	runAction(Sequence::create(DelayTime::create(2.5f), CallFunc::create([=]
	{
		//TODO:
		/*auto sign = SignInLayer::createLayer(m_seqDay);
		sign->setPosition(Point::ZERO);
		getParent()->addChild(sign, 20);
		User::getInstance()->addCoins(ConfigVipLevel::getInstance()->getVipLevel(User::getInstance()->getVipLevel()).send_coins_over);
		removeFromParentAndCleanup(1);*/
	}), nullptr));
	
	
}

void VipGainCoinSureDialog::showRandonBubbleAni()
{
	auto node = getChildByName("bg");

	auto aniNode = Sprite::create();
	aniNode->setPosition(20, 100);
	node->addChild(aniNode, 5);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0));

	aniNode = Sprite::create();
	aniNode->setPosition(node->getContentSize().width - 20, 100);
	node->addChild(aniNode, 5);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0));

}