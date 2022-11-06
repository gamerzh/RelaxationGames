#include "domain/ranklist/RanklistLayer.h"
#include "domain/ranklist/RanklistManager.h"
#include "utill/Chinese.h"
#include "domain/user/User.h"
#include "domain/ToolTip/ToolTipMannger.h"
void RanklistView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size RanklistView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(892, 90);
}
cocos2d::extension::TableViewCell* RanklistView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	RanklistCell *cell = (RanklistCell*)table->dequeueCell();
	if (!cell) {
		cell = RanklistCell::create();
	}
	else
	{

	}
	if (m_type == 1)
	{
		cell->setExpValue(idx);
	}
	else
	{
		cell->setCoinValue(idx);
	}
	return cell;
}
ssize_t RanklistView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	if (m_type==1)
	{
		return RanklistManager::getInstance()->getExpRankListData().size();
	}
	else
	{
		return RanklistManager::getInstance()->getCoinRankListData().size();
	}
}




Scene* RanklistLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = RanklistLayer::create();

	scene->addChild(layer);

	return scene;
}

bool RanklistLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		tableviewDelegate = new RanklistView();
		tableviewDelegate->setType(2);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("ranklistBg.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg);

		auto title = Sprite::create("ranklistTitle.png");
		title->setPosition(480, 511);
		addChild(title);



		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(RanklistLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

		EventListenerCustom* _listener2 = EventListenerCustom::create("get_ranklist_coin_info", [=](EventCustom* event){

			RanklistValue*value = static_cast<RanklistValue*>(event->getUserData());
			if (value->_errorcode == 0)
			{
				RanklistManager::getInstance()->setCoinRankListData(value->_rankItems);
				RanklistManager::getInstance()->setRankCoinRange(value->_rankRange);




				//tableview
				tableView = MyTableView::create(tableviewDelegate, Size(894, 387));
				tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
				tableView->setDirection(ScrollView::Direction::VERTICAL);
				tableView->setPosition(35, 20);
				tableView->setDelegate(tableviewDelegate);
				addChild(tableView);
				tableView->reloadData();

				auto cStr = ChineseWord("wopaizaiXXming");
				auto label = LabelTTF::create(cStr.c_str(), "arial", 20);
				label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
				label->setPosition(427, 445);
				addChild(label);


				bool isZero = (User::getInstance()->getCoins() <= 0);
				auto rank = RanklistManager::getInstance()->getRankByCoin(User::getInstance()->getCoins());
				std::string rankTxt = Value(rank).asString().c_str();
				if (isZero)
				{
					rankTxt += ":";
				}
				labelRank = LabelAtlas::create(rankTxt.c_str(), "rankListNum.png", 16, 22, '0');
				labelRank->setPosition(554, 445);
				labelRank->setAnchorPoint(Point::ANCHOR_MIDDLE);
				addChild(labelRank);



				//拥有金币
				haveCoinTTF = LabelTTF::create(ChineseWord("haveCoin").c_str(), "arial", 20);
				haveCoinTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
				haveCoinTTF->setPosition(700, 445);
				addChild(haveCoinTTF);

				coinsp = Sprite::create("coin.png");
				coinsp->setAnchorPoint(Point::ANCHOR_MIDDLE);
				coinsp->setPosition(765, 445);
				addChild(coinsp);
				auto coinStr = String::createWithFormat("%ld", User::getInstance()->getCoins())->getCString();
				CoinNumTTF = LabelAtlas::create(coinStr, "coinnumTxt.png", 14, 18, '0');
				CoinNumTTF->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
				CoinNumTTF->setPosition(915, 445);
				addChild(CoinNumTTF);




				auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(RanklistLayer::closeButtonCallBack, this));
				close->setPosition(960, 540);
				close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);

				auto coinButton = MenuItemImage::create("coinRanklist_1.png", "coinRanklist_2.png", CC_CALLBACK_1(RanklistLayer::changeTypeCallBack, this));
				coinButton->setName("coin");
				coinButton->setPosition(128, 436);
				coinButton->setEnabled(false);

				auto expButton = MenuItemImage::create("expRanklist_1.png", "expRanklist_2.png", CC_CALLBACK_1(RanklistLayer::changeTypeCallBack, this));
				expButton->setName("exp");
				expButton->setPosition(321, 436);
				auto menu = Menu::create(close, coinButton, expButton, nullptr);
				menu->setPosition(Point::ZERO);
				addChild(menu);
				coinButton->selected();


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




			}
			else
			{
				removeFromParentAndCleanup(1);
				ToolTipMannger::showDioag(value->_errormsg);
			}
			CC_SAFE_DELETE(value);
			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_ranklist_coin_info");

		});
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
		RanklistManager::getInstance()->loadCoin();




		bRet = true;
	} while (0);
	

	return bRet;
}

void RanklistLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void RanklistLayer::changeTypeCallBack(Ref*psend)
{
	auto bt = (MenuItemImage*)(psend);
	auto btName = bt->getName();
	if (btName == "coin")
	{
		bt->setEnabled(false);
		bt->selected();
		auto otherBt = (MenuItemImage*)bt->getParent()->getChildByName("exp");
		otherBt->unselected();
		otherBt->setEnabled(true);
		changeToCoinRanklist();
	}
	else
	{
		bt->setEnabled(false);
		bt->selected();
		auto otherBt = (MenuItemImage*)bt->getParent()->getChildByName("coin");
		otherBt->unselected();
		otherBt->setEnabled(true);
		changeToexpRanklist();
	}
}
void RanklistLayer::changeToexpRanklist()
{
	EventListenerCustom* _listener2 = EventListenerCustom::create("get_ranklist_exp_info", [=](EventCustom* event){

		RanklistValue*value = static_cast<RanklistValue*>(event->getUserData());
		if (value->_errorcode == 0)
		{
			RanklistManager::getInstance()->setExpRankListData(value->_rankItems);
			RanklistManager::getInstance()->setRankExpRange(value->_rankRange);
			coinsp->setTexture("EXP.png");

			haveCoinTTF->setString(ChineseWord("haveExp").c_str());
			CoinNumTTF->setString(Value(User::getInstance()->getExp()).asString().c_str());




			bool isZero = (User::getInstance()->getExp() <= 0);
			auto rank = RanklistManager::getInstance()->getRankByExp(User::getInstance()->getExp());
			std::string rankTxt = Value(rank).asString().c_str();
			if (isZero)
			{
				rankTxt += ":";
			}
			labelRank->setString(rankTxt.c_str());
			tableviewDelegate = new RanklistView();
			tableviewDelegate->setType(1);
			tableView->setDelegate(tableviewDelegate);
			tableView->setDataSource(tableviewDelegate);
			tableView->reloadData();
		}
		else
		{
			ToolTipMannger::showDioag(value->_errormsg);
		}
		CC_SAFE_DELETE(value);
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_ranklist_exp_info");

	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
	RanklistManager::getInstance()->loadExp();

	
}

void RanklistLayer::changeToCoinRanklist()
{

	EventListenerCustom* _listener2 = EventListenerCustom::create("get_ranklist_coin_info", [=](EventCustom* event){

		RanklistValue*value = static_cast<RanklistValue*>(event->getUserData());
		if (value->_errorcode == 0)
		{
			RanklistManager::getInstance()->setCoinRankListData(value->_rankItems);
			RanklistManager::getInstance()->setRankCoinRange(value->_rankRange);
			coinsp->setTexture("coin.png");
			haveCoinTTF->setString(ChineseWord("haveCoin").c_str());
			auto coinStr = String::createWithFormat("%ld", User::getInstance()->getCoins())->getCString();
			CoinNumTTF->setString(coinStr);




			bool isZero = (User::getInstance()->getCoins() <= 0);
			auto rank = RanklistManager::getInstance()->getRankByCoin(User::getInstance()->getCoins());
			std::string rankTxt = Value(rank).asString().c_str();
			if (isZero)
			{
				rankTxt += ":";
			}
			labelRank->setString(rankTxt.c_str());
			tableviewDelegate = new RanklistView();
			tableviewDelegate->setType(2);
			tableView->setDelegate(tableviewDelegate);
			tableView->setDataSource(tableviewDelegate);
			tableView->reloadData();
		}
		else
		{
			ToolTipMannger::showDioag(value->_errormsg);
		}
		CC_SAFE_DELETE(value);
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_ranklist_coin_info");

	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
	RanklistManager::getInstance()->loadCoin();





}