#include "ResultLayer.h"
#include "GlobalProperty.h"
#include "LobbyScene.h"
#include "GameStatus.h"
#include "UserData.h"
#include "Dream.h"
#include "GameScene.h"

USING_NS_CC;

ResultLayer* ResultLayer::create(bool win) {
	auto ret = new ResultLayer();
	if (ret && ret->init(win)) {
		ret->autorelease();
		return ret;
	}
	else {
		CC_SAFE_DELETE(ret);
		return NULL;
	}
}

bool ResultLayer::init(bool win) {
	if (!Layer::init()) {
		return false;
	}
    this->isWin = win;
	auto black = LayerColor::create(Color4B(0, 0, 0, 100), 1280, 720);
	addChild(black);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create();
	bg->setPosition(visibleSize.width/2, visibleSize.height/2+70);
	addChild(bg);
	if (win) {
		bg->setTexture("sl.png");
        //打开新的关卡
        if(GameStatus::getInstance()->getCurrentGameType() == GameStatus::GameType::worldCup){
            if(UserData::getInstance()->getWorldCupLevel()==GameStatus::getInstance()->getCurrentSelectedLevel()
               &&GameStatus::getInstance()->getCurrentSelectedLevel()<MAX_LEVEL_NUM){
                UserData::getInstance()->setWorldCupLevel(UserData::getInstance()->getWorldCupLevel()+1);
            }
        }else if(GameStatus::getInstance()->getCurrentGameType() == GameStatus::GameType::masterCup){
            if(UserData::getInstance()->getMasterCupLevel()==GameStatus::getInstance()->getCurrentSelectedLevel()
               &&GameStatus::getInstance()->getCurrentSelectedLevel()<MAX_LEVEL_NUM){
                UserData::getInstance()->setMasterCupLevel(GameStatus::getInstance()->getCurrentSelectedLevel()+1);
            }
        }
	}
	else {
		bg->setTexture("sb.png");
	}

	auto img1 = MenuItemImage::create("result_lobby.png","result_lobby.png",CC_CALLBACK_0(ResultLayer::gotoLobby, this));
	auto img2 = MenuItemImage::create("result_con.png", "result_con.png",CC_CALLBACK_0(ResultLayer::continueGame, this));
	auto menu = Menu::create(img1, img2,NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2-180);
	menu->alignItemsHorizontallyWithPadding(50);
	addChild(menu);
    
    auto gold1 = LabelAtlas::create("100","white_num.png",16,23,'0');
    gold1->setPosition(visibleSize.width / 2+60, visibleSize.height / 2-10);
    addChild(gold1);
    
    auto gold2 = LabelAtlas::create("100","white_num.png",16,23,'0');
    gold2->setPosition(visibleSize.width / 2+60, visibleSize.height / 2-95);
    addChild(gold2);
    
    if(!Dream::getInstance()->getDreamTimes()){
        auto y = Sprite::create("dream/price_twenty.png");
        y->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
        y->setPosition(1280 ,5);
        addChild(y);
    }

	return true;
}

void ResultLayer::continueGame(){
    doResultDream();
    getParent()->getParent()->getParent()->cleanup();
    Director::getInstance()->replaceScene(GameScene::create());
}

void ResultLayer::gotoLobby(){
    doResultDream();
    Director::getInstance()->replaceScene(LobbyScene::create());
}

void ResultLayer::doResultDream(){
    if(isWin){
        Dream::getInstance()->requestEvent(9);
    }else{
        Dream::getInstance()->requestEvent(10);
    }
     UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + 200);
}
