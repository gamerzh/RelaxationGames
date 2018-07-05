#include "Setting.h"
#include "ResultScene.h"
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

	auto showtime = LabelAtlas::create(StringUtils::format("%.1f", gameTime),"num_green.png",29,43,'0');//
	showtime->setAnchorPoint(Point::ANCHOR_MIDDLE);
	showtime->setPosition(visibleSize.width / 2, visibleSize.height - 40);
	addChild(showtime);

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

	//选中状态精灵
	auto musicOnSpr = Sprite::create("sound_on.png");
	//未选中状态精灵
	auto musicOffSpr = Sprite::create("sound_off.png");
	auto musicOn = MenuItemSprite::create(musicOnSpr, musicOnSpr);
	auto musicOff = MenuItemSprite::create(musicOffSpr, musicOffSpr);
	//创建MenuItemToggle，第一个参数是回调函数 后面依次是要显示的MenuItem，最后必须为NULL
	musicItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::soundMenuCallBack, this), musicOn, musicOff, NULL);
	//if (UserData::getInstance()->getMusicStatus() == 0) {
	//	musicItemToggle->setSelectedIndex(1);
	//}
	auto menu = Menu::create(musicItemToggle, NULL);
	menu->setPosition(visibleSize.width-60, visibleSize.height - 50);
	//menu->setVisible(false);
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
				((Label*)getChildByTag(100))->setString(StringUtils::format("%.1f", gameTime));
			}
		}
		else {
			this->pause();
			Director::getInstance()->replaceScene(TransitionMoveInT::create(1.0f, ResultScene::create()));
		}
	}
}