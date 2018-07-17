#include "Setting.h"
#include "ResultLayer.h"
#include "PauseLayer.h"
USING_NS_CC;

bool Setting::init() {
	if (!Layer::init()) {
		return false;
	}
	
	loadView();
	scheduleUpdate();
	return true;
}

void Setting::loadView() {

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto teamIcon1 = Sprite::create("team_icon_1.png");
	teamIcon1->setPosition(220,655);
	addChild(teamIcon1);

	auto score1 = LabelAtlas::create("00","num_gold.png",71,81,'0');
	score1->setAnchorPoint(Point::ANCHOR_MIDDLE);
	score1->setPosition(430, 660);
	addChild(score1);
	//engery
	auto energy_bg_1 = Sprite::create("energy_bg.png");
	energy_bg_1->setPosition(430, 610);
	addChild(energy_bg_1);
	auto energy_content_1 = Sprite::create("energy_pro.png");
	auto energy_timer_1 = ProgressTimer::create(energy_content_1);
	energy_timer_1->setPosition(430, 610);
	energy_timer_1->setMidpoint(Vec2(0, 1));
	energy_timer_1->setBarChangeRate(Point(1, 0));
	energy_timer_1->setType(ProgressTimer::Type::BAR);
	addChild(energy_timer_1);
	energy_timer_1->setPercentage(50);


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

	auto score2 = LabelAtlas::create("00", "num_gold.png", 71, 81, '0');
	score2->setAnchorPoint(Point::ANCHOR_MIDDLE);
	score2->setPosition(850, 660);
	addChild(score2);

	auto energy_bg_2 = Sprite::create("energy_bg.png");
	energy_bg_2->setPosition(850, 610);
	addChild(energy_bg_2);
	auto energy_content_2 = Sprite::create("energy_pro.png");
	auto energy_timer_2 = ProgressTimer::create(energy_content_2);
	energy_timer_2->setPosition(850, 610);
	energy_timer_2->setMidpoint(Vec2(0, 1));
	energy_timer_2->setBarChangeRate(Point(1, 0));
	energy_timer_2->setType(ProgressTimer::Type::BAR);
	addChild(energy_timer_2);
	energy_timer_2->setPercentage(50);

	auto teamIcon2 = Sprite::create("team_icon_1.png");
	teamIcon2->setPosition(1020, 655);
	addChild(teamIcon2);

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
	//if (UserData::getInstance()->getMusicStatus() == 0) {
	//	musicItemToggle->setSelectedIndex(1);
	//}
	auto menu = Menu::create(musicItemToggle, NULL);
	menu->setPosition(visibleSize.width-60, visibleSize.height - 50);
	this->addChild(menu);

}


void Setting::soundMenuCallBack(Ref* ref) {

}


void Setting::showTeamScore(int teamId) {


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
		if (gameTime > 0) {
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
