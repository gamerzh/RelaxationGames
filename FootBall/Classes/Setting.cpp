#include "Setting.h"
#include "ResultLayer.h"
#include "PauseLayer.h"
#include "UserData.h"
#include "GlobalProperty.h"
USING_NS_CC;

bool Setting::init() {
	if (!Layer::init()) {
		return false;
	}
    gameTime = GAME_TIME;
	loadView();
	scheduleUpdate();
	return true;
}

void Setting::loadView() {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto timeBg = Sprite::create("time_bg.png");
	timeBg->setPosition(visibleSize.width / 2, visibleSize.height - 50);
	addChild(timeBg);

    int timeLeft = gameTime/60;
    auto showtimeLeft = LabelAtlas::create(StringUtils::format("0%d", timeLeft),"num_green.png",29,43,'0');
    showtimeLeft->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    showtimeLeft->setTag(100);
    showtimeLeft->setPosition(visibleSize.width / 2-10, visibleSize.height - 40);
    addChild(showtimeLeft);
    
    auto po = Sprite::create("point_green.png");
    po->setPosition(visibleSize.width / 2, visibleSize.height - 40);
    addChild(po);
    
    int timeRight = gameTime%60;
	auto showtimeRight = LabelAtlas::create(StringUtils::format("%d", timeRight),"num_green.png",29,43,'0');
	showtimeRight->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    showtimeRight->setTag(101);
	showtimeRight->setPosition(visibleSize.width / 2+10, visibleSize.height - 40);
	addChild(showtimeRight);

	//pause
	auto pauseImg = MenuItemImage::create("pause_btn.png", "pause_btn.png",CC_CALLBACK_0(Setting::pauseGame,this));
	auto pauseMenu = Menu::create(pauseImg,NULL);
	pauseMenu->setPosition(visibleSize.width-140, visibleSize.height - 50);
	addChild(pauseMenu);

	auto musicOnSpr = Sprite::create("sound_on.png");
	auto musicOffSpr = Sprite::create("sound_off.png");
	auto musicOn = MenuItemSprite::create(musicOnSpr, musicOnSpr);
	auto musicOff = MenuItemSprite::create(musicOffSpr, musicOffSpr);
	musicItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::soundMenuCallBack, this), musicOn, musicOff, NULL);
    if (UserData::getInstance()->getMusicStatus() == 0) {
        musicItemToggle->setSelectedIndex(1);
    }
	auto menu = Menu::create(musicItemToggle, NULL);
	menu->setPosition(visibleSize.width-60, visibleSize.height - 50);
	this->addChild(menu);

}


void Setting::soundMenuCallBack(Ref* ref) {
    MenuItemToggle* temp = (MenuItemToggle*)ref;
    UserData::getInstance()->setMusicStatus((temp->getSelectedIndex()+1)%2);
}

void Setting::pauseGame() {
	auto pau = PauseLayer::create();
	addChild(pau);

}


void Setting::update(float dt) {

	passTime += dt;
	if (passTime > timestep) {
		gameTime -= timestep;
		passTime -= timestep;
		if (gameTime >= 0) {
			if (NULL != getChildByTag(100)) {
				((LabelAtlas*)getChildByTag(100))->setString(StringUtils::format("0%d", gameTime/60));
			}
            if (NULL != getChildByTag(101)) {
                int t =gameTime%60;
                if(t < 10){
                    ((LabelAtlas*)getChildByTag(101))->setString(StringUtils::format("0%d", t));
                }else{
                    ((LabelAtlas*)getChildByTag(101))->setString(StringUtils::format("%d", t));
                }
                
            }
		}
		else {
			this->pause();
			auto layer = ResultLayer::create(true);
			addChild(layer);
		}
	}
}
