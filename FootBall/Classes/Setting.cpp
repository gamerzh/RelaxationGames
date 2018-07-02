#include "Setting.h"
#include "ResultScene.h"
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
	auto teamIcon = Sprite::create("team_icon_1.png");
	teamIcon->setPosition(200,680);
	addChild(teamIcon);

	auto showtime = Label::createWithSystemFont(StringUtils::format("%.1f", gameTime), "arial", 40);
	showtime->setTag(100);
	showtime->setColor(Color3B::WHITE);
	showtime->setPosition(visibleSize.width / 2, visibleSize.height - 40);
	addChild(showtime);


	auto teamIcon2 = Sprite::create("team_icon_1.png");
	teamIcon2->setPosition(1080, 680);
	addChild(teamIcon2);

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