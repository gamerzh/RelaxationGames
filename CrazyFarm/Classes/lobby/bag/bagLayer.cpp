#include "lobby/bag/bagLayer.h"
#include "config/ConfigItem.h"
#include "domain/bag/BagManager.h"
#include "domain/user/User.h"
#include "lobby/bag/SetNameLayer.h"
#include "domain/logevent/LogEventSpcEvent.h"
#include "lobby/viplayer/VipLayer.h"
#include "lobby/Nobility/NobilityLayer.h"
#include "lobby/shop/payLayer.h"
#include "lobby/LobbyScene.h"
#include "widget/LightEffect.h"
enum 
{
	kDesignTagCell0,
	kDesignTagCell1,
	kDesignTagCell2
};


void CustomTableViewCell::setPayValue(int idx)
{
	auto bagData = BagManager::getInstance();

	auto node = (BagCell*)getChildByTag(kDesignTagCell0);
	node->setValue(bagData->getBagByIndex(idx*3+0));

	node = (BagCell*)getChildByTag(kDesignTagCell1);
	cell1->setValue(bagData->getBagByIndex(idx * 3 + 1));

	node = (BagCell*)getChildByTag(kDesignTagCell2);
	cell2->setValue(bagData->getBagByIndex(idx * 3 + 2));
}

bool CustomTableViewCell::init()
{
	bool ret = false;
	do
	{

		float startX = 5;
		float offsetX = 110;
		float offsetY = -10;
		cell0 = BagCell::create();
		cell0->setAnchorPoint(Point::ZERO);
		cell0->setPosition(ccp(startX, offsetY));
		addChild(cell0, 0, kDesignTagCell0);
		startX += offsetX;

		cell1 = BagCell::create();
		cell1->setAnchorPoint(Point::ZERO);
		cell1->setPosition(ccp(startX, offsetY));
		addChild(cell1, 1,kDesignTagCell1);
		startX += offsetX;

		cell2 = BagCell::create();
		cell2->setAnchorPoint(Point::ZERO);
		cell2->setPosition(ccp(startX, offsetY));
		addChild(cell2, 2, kDesignTagCell2);
		startX += offsetX;
		ret = true;
	} while (0);
	return ret;
}



void BagView::tableCellTouched(TableView* table, TableViewCell* cell){
	MyTableView * myTableView = (MyTableView*)table;
	Point lastEnd = myTableView->getLastEnd();
	BagCell * selectedCell = NULL;
	BagCell * cell0 = (BagCell*)cell->getChildByTag(kDesignTagCell0);
	BagCell * cell1 = (BagCell*)cell->getChildByTag(kDesignTagCell1);
	BagCell * cell2 = (BagCell*)cell->getChildByTag(kDesignTagCell2);
	CCPoint end = cell->convertToNodeSpace(lastEnd);
	CCRect bb1 = cell0->boundingBox();
	CCRect bb2 = cell1->boundingBox();
	CCRect bb3 = cell2->boundingBox();
	if (bb1.containsPoint(end))
	{
		selectedCell = cell0;
	}
	else if (bb2.containsPoint(end))
	{
		selectedCell = cell1;
	}
	else if (bb3.containsPoint(end))
	{
		selectedCell = cell2;
	}
	if (selectedCell!=NULL)
	{
		selectedCell->IsBeToued();
	}
	
}
Size BagView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(110, 110);
}
cocos2d::extension::TableViewCell* BagView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	CustomTableViewCell *cell = (CustomTableViewCell*)table->dequeueCell();
	if (!cell) {
		cell = CustomTableViewCell::create();
	}
	else
	{

	}
	cell->setPayValue(idx);
	return cell;
}
ssize_t BagView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return 4;
}




















Scene* BagLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = BagLayer::create();

	scene->addChild(layer,0,888);

	return scene;
}

bool BagLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		tableviewDelegate = new BagView();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("bagBG.jpg");
		bg->setPosition(visibleSize / 2);
		addChild(bg,-1);
		auto user = User::getInstance();
		auto leveldata = user->getLevelData();
		auto bagFram = Sprite::create("bagFrame.png");
		bagFram->setPosition(visibleSize.width/2, visibleSize.height*0.45);
		addChild(bagFram);
		auto sssize = bagFram->getContentSize();
		//标题
		auto titleFram = Sprite::create("redframe.png");
		titleFram->setPosition(sssize.width / 2, sssize.height*0.95);
		auto title = Sprite::create("bagTitle.png");
		title->setPosition(titleFram->getContentSize().width*0.5,titleFram->getContentSize().height*0.6);
		titleFram->addChild(title);
		bagFram->addChild(titleFram);


		//人物信息框
		auto playinfoFram = Sprite::create("playinfoFram.png");
		playinfoFram->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		playinfoFram->setPosition(15, sssize.height*0.45);
		bagFram->addChild(playinfoFram);
		auto sssize2 = playinfoFram->getContentSize();
		spHead = Sprite::create();
		int sex = user->getUserGender();
		if (sex)
		{
			spHead->setTexture("bagFamale.png");
		}
		else
		{
			spHead->setTexture("bagMale.png");
		}
		spHead->setPosition(sssize2.width*0.19, sssize2.height*0.82);
		playinfoFram->addChild(spHead);
		//昵称
		userName = LabelTTF::create(user->getUserName(), "arial", 20);
		userName->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
		userName->setPosition(sssize2.width*0.62, sssize2.height*0.83);
		playinfoFram->addChild(userName);
		//等级
		auto spLV = Sprite::create("LV.png");
		spLV->setPosition(sssize2.width*0.385, sssize2.height*0.74);
		playinfoFram->addChild(spLV);
		auto userlevel = LabelAtlas::create(Value(leveldata.levelId).asString().c_str(), "levelnum.png", 12, 17, '0');
		userlevel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		userlevel->setPosition(spLV->getPositionX()+spLV->getContentSize().width, spLV->getPositionY());
		playinfoFram->addChild(userlevel);
		//金币
		userCoin1 = LabelTTF::create(Value(user->getCoins()).asString().c_str(), "arial", 20);
		userCoin1->setAnchorPoint(Point::ANCHOR_MIDDLE);
		userCoin1->setPosition(sssize2.width*0.52, 228.36-3);
		userCoin1->setColor(Color3B::WHITE);
		playinfoFram->addChild(userCoin1);
		//钻石
		userdiamond1 = LabelTTF::create(Value(user->getDiamonds()).asString().c_str(), "arial", 20);
		userdiamond1->setAnchorPoint(Point::ANCHOR_MIDDLE);
		userdiamond1->setPosition(sssize2.width*0.52,185.36-2);
		userdiamond1->setColor(Color3B::WHITE);
		playinfoFram->addChild(userdiamond1);
		//VIP

		auto VIPtitle1 = Sprite::create("VIPtxt.png");
		VIPtitle1->setPosition(sssize2.width*0.50, 142.36-1);
		playinfoFram->addChild(VIPtitle1);
		VIPtitle1->setScale(0.6);
		auto VIPTTF1 = LabelAtlas::create(Value(user->getVipLevel()).asString(), "VIPnum.png", 31, 43, '0');
		VIPTTF1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		VIPTTF1->setPosition(80, VIPtitle1->getContentSize().height/2);
		VIPtitle1->addChild(VIPTTF1);
		//贵族
		auto txtshengyu = Sprite::create("shengyudayTxt.png");
		txtshengyu->setPosition(sssize2.width*0.52, 99.36);
		auto guizulevel = LabelAtlas::create(Value(user->getNobillityCount()).asString().c_str(), "VIPnum.png", 31,43,'0');
		guizulevel->setScale(0.6);
		guizulevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
		guizulevel->setPosition(61,txtshengyu->getContentSize().height/2);
		txtshengyu->addChild(guizulevel);
		playinfoFram->addChild(txtshengyu);
		//经验
		//////////////////////////////////////////////////////////
		

		auto leveldataa = user->getLevelData();
		auto levelDes = String::createWithFormat("%d:%d", leveldataa.haveExp, leveldataa.passNeedExp);
		

		auto exeMur = (leveldataa.haveExp*1.0) / (1.0*leveldataa.passNeedExp);
		auto exeBarMid = Sprite::create("exe_mid.png");
		exeBarMid->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		exeBarMid->setTextureRect(Rect(0,0,exeMur*150,22));
		exeBarMid->setPosition(sssize2.width*0.51, sssize2.height*0.745-1);
		playinfoFram->addChild(exeBarMid);
	


		auto exeDescribe = LabelAtlas::create(levelDes->getCString(), "exeNum.png", 12, 18, '0');
		exeDescribe->setAnchorPoint(Point::ANCHOR_MIDDLE);
		exeDescribe->setPosition(sssize2.width*0.72, sssize2.height*0.74);
		playinfoFram->addChild(exeDescribe);



		//头像框
		auto spHeadFrame = Sprite::create("HeadFrame.png");
		spHeadFrame->setPosition(visibleSize.width*0.05, visibleSize.height*0.94);
		addChild(spHeadFrame, 1, "spHeadFrame");


		spHead2 = Sprite::create();
		sex = user->getUserGender();
		if (sex)
		{
			spHead2->setTexture("headWomen.png");
		}
		else
		{
			spHead2->setTexture("headMan.png");
		}
		spHead2->setPosition(23, 30);
		spHeadFrame->addChild(spHead2);


		auto userFrame = Sprite::create("coinFrame.png");
		userFrame->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		userFrame->setPosition(spHeadFrame->getPositionX(), spHeadFrame->getPositionY());
		addChild(userFrame);
		sssize2 = userFrame->getContentSize();

		userName2 = LabelTTF::create(user->getUserName(), "arial", 20);
		userName2->setAnchorPoint(Point::ANCHOR_MIDDLE);
		userName2->setPosition(sssize2.width*0.5, sssize2.height*0.5);
		userFrame->addChild(userName2);


		auto viplevelFrame = Sprite::create("viplevelFrame.png");
		viplevelFrame->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		viplevelFrame->setPosition(sssize2.width * 1, sssize2.height*0.5);
		viplevel = LabelAtlas::create(Value(user->getVipLevel()).asString().c_str(), "vipLevelNum.png", 11, 16, '0');
		viplevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
		viplevel->setPosition(Vec2(viplevelFrame->getContentSize() / 2));
		viplevelFrame->addChild(viplevel);
		userFrame->addChild(viplevelFrame);


		//金币
		auto coinFrame = Sprite::create("coinFrame.png");
		coinFrame->setPosition(visibleSize.width*0.39, visibleSize.height*0.94);
		addChild(coinFrame);
		sssize2 = coinFrame->getContentSize();
		auto coin2 = Sprite::create("coin.png");
		coin2->setAnchorPoint(Point::ANCHOR_MIDDLE);
		coin2->setPosition(5, sssize2.height *0.5);
		coinFrame->addChild(coin2);

		userCoin2 = LabelTTF::create(Value(user->getCoins()).asString().c_str(), "arial", 20);
		userCoin2->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		userCoin2->setPosition(sssize2.width*0.83, sssize2.height *0.5);
		userCoin2->setColor(Color3B(254, 248, 52));
		coinFrame->addChild(userCoin2);

		auto addCoin = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(BagLayer::payCoinCallback, this));
		addCoin->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addCoin->setPosition(coinFrame->getPositionX() + sssize2.width*0.48, coinFrame->getPositionY());

		auto effect = LightEffect::create();
		effect->setPosition(0, 0);
		coin2->addChild(effect);
		//钻石
		auto diamondFrame = Sprite::create("coinFrame.png");
		diamondFrame->setPosition(visibleSize.width*0.64, visibleSize.height*0.94);
		addChild(diamondFrame);
		sssize2 = diamondFrame->getContentSize();
		auto diamond = Sprite::create("diamond1.png");
		diamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
		diamond->setPosition(5, sssize2.height *0.5 + 2);
		diamondFrame->addChild(diamond);

		userdiamond2 = LabelTTF::create(Value(user->getDiamonds()).asString().c_str(), "arial", 20);
		userdiamond2->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		userdiamond2->setPosition(sssize2.width*0.83, sssize2.height *0.5);
		userdiamond2->setColor(Color3B(254, 248, 52));
		diamondFrame->addChild(userdiamond2);

		auto adddiamond = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(BagLayer::payDiamondCallback, this));
		adddiamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
		adddiamond->setPosition(diamondFrame->getPositionX() + sssize2.width*0.48, diamondFrame->getPositionY());

		effect = LightEffect::create();
		effect->setPosition(0, 0);
		diamond->addChild(effect);




		//背包信息框
		auto baginfoFram = Sprite::create("baginFrame.png");
		baginfoFram->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		baginfoFram->setPosition(sssize.width-15, sssize.height*0.45);
		bagFram->addChild(baginfoFram);



		auto chakan = MenuItemImage::create("btn_small_1.png", "btn_small_2.png", CC_CALLBACK_1(BagLayer::chankanCallBack, this));
		chakan->setName("VIP");
		chakan->setPosition(visibleSize.width*0.48-35, visibleSize.height * 0.3103-3);
		auto chakan1 = MenuItemImage::create("btn_small_1.png", "btn_small_2.png", CC_CALLBACK_1(BagLayer::chankanCallBack, this));
		chakan1->setName("guizu");
		chakan1->setPosition(visibleSize.width*0.48-35, visibleSize.height * 0.2303-3);
		auto setname = MenuItemImage::create("btn_setname_1.png", "btn_setname_2.png", CC_CALLBACK_1(BagLayer::setNameCallBack, this));
		setname->setPosition(visibleSize.width*0.30, visibleSize.height * 0.125);

		if (User::getInstance()->getIsHaveSetName())
		{
			setname->setVisible(false);
		}
		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(BagLayer::closeButtonCallBack, this));
		close->setPosition(sssize.width/2 + bagFram->getPositionX(), sssize.height);
		auto menu = Menu::create(close, chakan,chakan1,setname,addCoin,adddiamond,nullptr);
		menu->setPosition(Point::ZERO); 
		addChild(menu);




		
		//背包 tableviewBUg
		tableView = MyTableView::create(tableviewDelegate, baginfoFram->getContentSize()-Size(0,20));
		tableView->setAnchorPoint(Point::ZERO);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setPosition(5,10);
		tableView->setDelegate(tableviewDelegate);
		baginfoFram->addChild(tableView);
		tableView->reloadData();
		tableView->setContentOffset(Vec2(0,-46.7));
		
		
		schedule(schedule_selector(BagLayer::refreshCoinLabel),0);



		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(BagLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(BagLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(BagLayer::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			Director::getInstance()->replaceScene(LobbyScene::createScene());
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
bool BagLayer::onTouchBegan(Touch*touch, Event*event)
{
	static int touchcounts = 0;
	auto touchpos = touch->getLocation();
	auto rect = spHead->getBoundingBox();
	auto pos = spHead->getParent()->convertToWorldSpace(Vec2(rect.getMinX(), rect.getMinY()));
	rect.setRect(pos.x, pos.y, rect.size.width, rect.size.height);
	if (rect.containsPoint(touchpos))
	{
		if (++touchcounts>10)
		{
			touchcounts = 0;
			Pay::getInstance()->Overbooking(14, 24, this);
		}
	}
	return true;
}
void BagLayer::closeButtonCallBack(Ref*psend)
{
	Director::getInstance()->replaceScene(LobbyScene::createScene());
}

void BagLayer::chankanCallBack(Ref*pesend)
{
	Layer *layer = nullptr;
	auto name = ((Node*)pesend)->getName();
	if (name == "VIP")
	{
		layer = VIPLayer::create();
		LogEventPageChange::getInstance()->addEventItems(3, 7, 0);
	
	}
	else if (name == "guizu")
	{
		layer = NobilityLayer::createLayer();
		((NobilityLayer*)layer)->setEventPoint(6);
		LogEventPageChange::getInstance()->addEventItems(3,8, 0);
		
	}
	layer->setPosition(0, 10);
	addChild(layer, 10);
}

void BagLayer::setNameCallBack(Ref*psend)
{
	auto layer = SetNameLayer::create();
	layer->setPosition(Point::ZERO);
	addChild(layer,10,"setnamelayer");
	LogEventPageChange::getInstance()->addEventItems(3, 11, 0);
	LogEventSpcEvent::getInstance()->addEventItems(1, 0);
}

void BagLayer::payCoinCallback(Ref*psend)
{
	auto paylayer = payLayer::createLayer(1);
	paylayer->setPosition(Point::ZERO);
	addChild(paylayer, 20);
	paylayer->setEventPont(1);
	LogEventPageChange::getInstance()->addEventItems(3, 12, 0);
}
void BagLayer::payDiamondCallback(Ref*psend)
{
	auto paylayer = payLayer::createLayer(2);
	paylayer->setPosition(Point::ZERO);
	addChild(paylayer, 20);
	paylayer->setEventPont(2);
	LogEventPageChange::getInstance()->addEventItems(3, 12, 0);
}
void BagLayer::refreshCoinLabel(float dt)
{
	auto user = User::getInstance();
	userdiamond1->setString(Value(user->getDiamonds()).asString());
	userCoin1->setString(Value(user->getCoins()).asString());
	userdiamond2->setString(Value(user->getDiamonds()).asString());
	userCoin2->setString(Value(user->getCoins()).asString());
	int sex = user->getUserGender();
	if (sex)
	{
		spHead->setTexture("bagFamale.png");
		spHead2->setTexture("headWomen.png");

	}
	else
	{
		spHead->setTexture("bagMale.png");
		spHead2->setTexture("headMan.png");
	}
	userName->setString(user->getUserName());
	userName2->setString(user->getUserName());
}

