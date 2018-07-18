#include "TeamAbility.h"
#include "UserData.h"
USING_NS_CC;

TeamAbility* TeamAbility::create(TeamAbilityType type) {
	auto res = new TeamAbility();
	if (res && res->init(type)) {
		res->autorelease();
		return res;
	}
	else {
		CC_SAFE_DELETE(res);
		return res;
	}
}

bool TeamAbility::init(TeamAbilityType type) {
	if (!Node::init()) {
		return false;
	}
	this->teamAbilityType = type;
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create(getFileNameByType(type));
	bg->setPosition(0, 0);
	addChild(bg);


	for (int i = 0; i < 5; i++) {
		auto lev = Sprite::create("point_gray.png");
		lev->setPosition(-30 + 15 * i, -37);
		lev->setTag(100 + i);
		addChild(lev);
	}

	auto imge = MenuItemImage::create("buy_prop.png", "buy_prop.png", CC_CALLBACK_0(TeamAbility::getPropLevel, this));
	auto menu = Menu::create(imge, NULL);
	menu->setPosition(0, -160);
	addChild(menu);

	auto num = LabelAtlas::create(StringUtils::format("%d", getPriceByType(type)), "brown_num.png", 17, 27, '0');
	num->setAnchorPoint(Point::ANCHOR_MIDDLE);
	num->setPosition(5, -160);
	addChild(num);

	updatePropLevel(type);

	return true;
}

void TeamAbility::getPropLevel() {
	if (teamAbilityType == TeamAbilityType::speed) {
		int level = UserData::getInstance()->getTeamSpeedLevel();
		level = level + 1;
		if (level > 5) {
			level = 5;
		}
		UserData::getInstance()->setTeamSpeedLevel(level);
	}
	else if (teamAbilityType == TeamAbilityType::shoot) {
		int level = UserData::getInstance()->getTeamShootLevel();
		level = level + 1;
		if (level > 5) {
			level = 5;
		}
		UserData::getInstance()->setTeamShootLevel(level);
	}
	else if (teamAbilityType == TeamAbilityType::energy) {
		int level = UserData::getInstance()->getTeamEnergyLevel();
		level = level + 1;
		if (level > 5) {
			level = 5;
		}
		UserData::getInstance()->setTeamEnergyLevel(level);
	}
	updatePropLevel(teamAbilityType);
}

void TeamAbility::updatePropLevel(TeamAbilityType type) {
	for (int j = 0; j < getLevelByType(type); j++) {
		((Sprite*)getChildByTag(100 + j))->setTexture("point_light.png");
	}
}


std::string TeamAbility::getFileNameByType(TeamAbilityType type) {
	auto name = "";
	if (type == TeamAbilityType::speed) {
		name = "speed_box.png";
	}
	else if (type == TeamAbilityType::shoot) {
		name = "shoot_box.png";
	}
	else if (type == TeamAbilityType::energy) {
		name = "enger_box.png";
	}
	return name;
}

int TeamAbility::getLevelByType(TeamAbilityType type) {
	int level = 0;
	if (type == TeamAbilityType::speed) {
		level = UserData::getInstance()->getTeamSpeedLevel();
	}
	else if (type == TeamAbilityType::shoot) {
		level = UserData::getInstance()->getTeamShootLevel();
	}
	else if (type == TeamAbilityType::energy) {
		level = UserData::getInstance()->getTeamEnergyLevel();
	}
	return level;
}


int TeamAbility::getPriceByType(TeamAbilityType type) {
	return 500;
}
