#include "lobby/viplayer/VipLayer.h"
#include "config/ConfigItem.h"
#include "domain/user/User.h"
#include "widget/MyTableView.h"
#include "utill/Chinese.h"
#include "lobby/shop/payLayer.h"
#include "domain/logevent/LogEventPageChange.h"

void VIPView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size VIPView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(220, 400);
}
cocos2d::extension::TableViewCell* VIPView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	VipCell *cell = (VipCell*)table->dequeueCell();
	if (!cell) {
		cell = VipCell::create();
	}
	else
	{

	}
	cell->setValue(idx+1);
	return cell;
}
ssize_t VIPView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return 9;
}




















Scene* VIPLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = VIPLayer::create();

	scene->addChild(layer);

	return scene;
}

bool VIPLayer::init()
{
	if ( !BaseLayer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		tableviewDelegate = new VIPView();
		Size visibleSize = Director::getInstance()->getVisibleSize();
	
		auto bg = Sprite::create("VIP_di.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg);

		////再充值XX元成为VIP
		auto nowVip = User::getInstance()->getVipLevel();
		auto nowChargeMoney = User::getInstance()->getChargeMoney();
		auto vipConfig = ConfigVipLevel::getInstance();
		auto nextVip = vipConfig->getVipLevel(nowVip + 1);
	




		

		auto VipExpFram = Sprite::create("VIP_exp.png");
		VipExpFram->setPosition(visibleSize.width*0.37, visibleSize.height*0.2);
		addChild(VipExpFram);

		auto VIPtitle = Sprite::create("VIPtxt.png");
		VIPtitle->setPosition(visibleSize.width*0.1, visibleSize.height*0.2);
		addChild(VIPtitle);


		auto VIPTTF = LabelAtlas::create(Value(nowVip).asString(), "VIPnum.png", 31, 43, '0');
		VIPTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
		VIPTTF->setPosition(visibleSize.width*0.1 + 40, visibleSize.height*0.2);
		addChild(VIPTTF);
		VIPTTF->setScale(0.7);
		auto scale = ((float)nowChargeMoney) / ((float)nextVip.charge_money)*302;

		auto VipExpBar = Sprite::create("VIP_expBar.png");
		VipExpBar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		VipExpBar->setPosition(10,VipExpFram->getContentSize().height/2+1.2);
		VipExpBar->setTextureRect(Rect(0, 0, scale, 31));
		VipExpFram->addChild(VipExpBar);

		auto VIPtitle1 = Sprite::create("VIPtxt.png");
		VIPtitle1->setPosition(visibleSize.width*0.60, visibleSize.height*0.2);
		addChild(VIPtitle1);

		auto VIPTTF1 = LabelAtlas::create(Value(nowVip+1).asString(), "VIPnum.png", 31, 43, '0');
		VIPTTF1->setAnchorPoint(Point::ANCHOR_MIDDLE);
		VIPTTF1->setPosition(visibleSize.width*0.60 + 40, visibleSize.height*0.2);
		addChild(VIPTTF1);

		VIPTTF1->setScale(0.7);

		auto frame = Scale9Sprite::create("txtPriceDes.png");
		frame->setContentSize(Size(670, 36));
		frame->setPosition(visibleSize.width*0.4+41/2, visibleSize.height*0.1);
		addChild(frame);

		auto expPercentum = String::createWithFormat("%d:%d", nowChargeMoney, nextVip.charge_money);
		auto expPercentLabel = LabelAtlas::create(expPercentum->getCString(), "VIPexp_num.png", 14, 22, '0');
		VipExpFram->addChild(expPercentLabel, 1);
		expPercentLabel->setPosition(VipExpFram->getContentSize().width*0.45, VipExpFram->getContentSize().height / 2);
		expPercentLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);

		auto chinaword = ChineseWord("VIPdes");
		auto ttf = LabelTTF::create(chinaword.c_str(), "Airal", 20);
		ttf->setColor(Color3B::YELLOW);
		ttf->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		ttf->setPosition(95, visibleSize.height*0.1);
		addChild(ttf);


		
		auto attention = Sprite::create("attention.png");
		attention->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		attention->setPosition(80, visibleSize.height*0.1);
		addChild(attention);

		///, nextVip.charge_money - nowChargeMoney, nextVip.vip_level
		auto needPayMoney = LabelAtlas::create(Value(nextVip.charge_money - nowChargeMoney).asString(), "multipleNum.png", 15, 21, '0');
		needPayMoney->setPosition(190, visibleSize.height*0.1);
		needPayMoney->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(needPayMoney);

		auto vipSp = Sprite::create("VIPtxt.png");
		vipSp->setPosition(400, visibleSize.height*0.1);
		
		addChild(vipSp);

		auto VIPLvTTF = LabelAtlas::create(Value(nextVip.vip_level).asString(), "VIPnum.png", 31, 43, '0');
		VIPLvTTF->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		VIPLvTTF->setPosition(vipSp->getPosition()+Vec2(vipSp->getContentSize().width/2,0));
		addChild(VIPLvTTF);
		VIPLvTTF->setScale(0.6);
		vipSp->setScale(0.8);

		attention = Sprite::create("attention.png");
		attention->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		attention->setPosition(VIPLvTTF->getPosition()+Vec2(VIPLvTTF->getContentSize().width/2+10,0));
		addChild(attention);


		//tableview
		MyTableView* tableView = MyTableView::create(tableviewDelegate, Size(800,600));
		tableView->setDirection(ScrollView::Direction::HORIZONTAL);
		tableView->setPosition(63,160);
		tableView->setDelegate(tableviewDelegate);
		tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(tableView);
		tableView->reloadData();
		tableView->setContentOffset(Vec2(nowVip*-210, 0));


	

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(VIPLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(VIPLayer::closeButtonCallBack, this));
		close->setPosition(885, 492);

		auto quickPay = MenuItemImage::create("quickPay_1.png", "quickPay_2.png", CC_CALLBACK_1(VIPLayer::chankanCallBack, this));
		quickPay->setPosition(812, 90);

		auto menu = Menu::create(close, quickPay,nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);






	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			removeFromParentAndCleanup(1);
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (0);
	



	return bRet;
}

void VIPLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void VIPLayer::chankanCallBack(Ref*pesend)
{
	auto layer = payLayer::createLayer(1);
	layer->setPosition(Point::ZERO);
	layer->setEventPont(21);
	getParent()->addChild(layer,30);
	removeFromParentAndCleanup(1);
	LogEventPageChange::getInstance()->addEventItems(7, 13,0 );
}