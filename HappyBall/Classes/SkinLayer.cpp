#include "SkinLayer.h"
#include "UserData.h"
#include "DreamLayer.h"
#include "Dream.h"
#include "ChineseWorld.h"
#include "SetingLayer.h"
USING_NS_CC;
using namespace std;

bool SkinLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto skinBg = Sprite::create("main_layer_bg.png");
	skinBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(skinBg);

	auto skinBox = Sprite::create("skin_box.png");
	skinBox->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(skinBox);

	auto closeImg = MenuItemImage::create("close_btn.png", "close_btn.png", CC_CALLBACK_0(SkinLayer::closeView, this));
	auto menu = Menu::create(closeImg, NULL);
	menu->setPosition(visibleSize.width / 2 + 300, visibleSize.height / 2 + 430);
	addChild(menu);


	skinBtn_0 = MenuItemImage::create("used_btn.png", "used_btn.png", CC_CALLBACK_1(SkinLayer::changeSkin, this));
	skinBtn_0->setTag(SKIN_BTN_0);
	skinBtn_1 = MenuItemImage::create("gold_1000.png", "gold_1000.png", CC_CALLBACK_1(SkinLayer::changeSkin, this));
	skinBtn_1->setTag(SKIN_BTN_1);
	skinBtn_2 = MenuItemImage::create("gold_1000.png", "gold_1000.png", CC_CALLBACK_1(SkinLayer::changeSkin, this));
	skinBtn_2->setTag(SKIN_BTN_2);
	skinBtn_3 = MenuItemImage::create("gold_2000.png", "gold_2000.png", CC_CALLBACK_1(SkinLayer::changeSkin, this));
	skinBtn_3->setTag(SKIN_BTN_3);
	skinBtn_4 = MenuItemImage::create("gold_2000.png", "gold_2000.png", CC_CALLBACK_1(SkinLayer::changeSkin, this));
	skinBtn_4->setTag(SKIN_BTN_4);
	skinBtn_5 = MenuItemImage::create("gold_5000.png", "gold_5000.png", CC_CALLBACK_1(SkinLayer::changeSkin, this));
	skinBtn_5->setTag(SKIN_BTN_5);
	skinBtn_6 = MenuItemImage::create("gold_10000.png", "gold_10000.png", CC_CALLBACK_1(SkinLayer::changeSkin, this));
	skinBtn_6->setTag(SKIN_BTN_6);

	auto menuSKin = Menu::create(skinBtn_0, skinBtn_1, skinBtn_2, skinBtn_3, skinBtn_4, skinBtn_5, skinBtn_6, NULL);
	menuSKin->setPosition(visibleSize.width / 2 + 200, visibleSize.height / 2 - 55);
	menuSKin->alignItemsVerticallyWithPadding(55);
	addChild(menuSKin);

	updateButtonState();

	return true;
}

void SkinLayer::updateButtonState() {
	//根据玩家的信息来显示按钮的最新内容
	std::vector<std::string> playerSkins = UserData::getInstance()->getPlayerMod();
	for (auto var : playerSkins) {
		if (var == SKIN_0) {
			skinBtn_0->setNormalImage(Sprite::create("use_btn.png"));
			skinBtn_0->setSelectedImage(Sprite::create("use_btn.png"));
		}
		else if (var == SKIN_1) {
			skinBtn_1->setNormalImage(Sprite::create("use_btn.png"));
			skinBtn_1->setSelectedImage(Sprite::create("use_btn.png"));
		}
		else if (var == SKIN_2) {
			skinBtn_2->setNormalImage(Sprite::create("use_btn.png"));
			skinBtn_2->setSelectedImage(Sprite::create("use_btn.png"));
		}
		else if (var == SKIN_3) {
			skinBtn_3->setNormalImage(Sprite::create("use_btn.png"));
			skinBtn_3->setSelectedImage(Sprite::create("use_btn.png"));
		}
		else if (var == SKIN_4) {
			skinBtn_4->setNormalImage(Sprite::create("use_btn.png"));
			skinBtn_4->setSelectedImage(Sprite::create("use_btn.png"));
		}
		else if (var == SKIN_5) {
			skinBtn_5->setNormalImage(Sprite::create("use_btn.png"));
			skinBtn_5->setSelectedImage(Sprite::create("use_btn.png"));
		}
		else if (var == SKIN_6) {
			skinBtn_6->setNormalImage(Sprite::create("use_btn.png"));
			skinBtn_6->setSelectedImage(Sprite::create("use_btn.png"));
		}
	}
	//显示当前装备的皮肤
	if (UserData::getInstance()->getCurrentMod() == SKIN_0) {
		skinBtn_0->setNormalImage(Sprite::create("used_btn.png"));
		skinBtn_0->setSelectedImage(Sprite::create("used_btn.png"));
	}
	else if (UserData::getInstance()->getCurrentMod() == SKIN_1) {
		skinBtn_1->setNormalImage(Sprite::create("used_btn.png"));
		skinBtn_1->setSelectedImage(Sprite::create("used_btn.png"));
	}
	else if (UserData::getInstance()->getCurrentMod() == SKIN_2) {
		skinBtn_2->setNormalImage(Sprite::create("used_btn.png"));
		skinBtn_2->setSelectedImage(Sprite::create("used_btn.png"));
	}
	else if (UserData::getInstance()->getCurrentMod() == SKIN_3) {
		skinBtn_3->setNormalImage(Sprite::create("used_btn.png"));
		skinBtn_3->setSelectedImage(Sprite::create("used_btn.png"));
	}
	else if (UserData::getInstance()->getCurrentMod() == SKIN_4) {
		skinBtn_4->setNormalImage(Sprite::create("used_btn.png"));
		skinBtn_4->setSelectedImage(Sprite::create("used_btn.png"));
	}
	else if (UserData::getInstance()->getCurrentMod() == SKIN_5) {
		skinBtn_5->setNormalImage(Sprite::create("used_btn.png"));
		skinBtn_5->setSelectedImage(Sprite::create("used_btn.png"));
	}
	else if (UserData::getInstance()->getCurrentMod() == SKIN_6) {
		skinBtn_6->setNormalImage(Sprite::create("used_btn.png"));
		skinBtn_6->setSelectedImage(Sprite::create("used_btn.png"));
	}
}


void SkinLayer::updateSkinState(std::string name) {
	if (name == SKIN_0) {
		UserData::getInstance()->setCurrentMod(SKIN_0);
		UserData::getInstance()->addPlayerMod(SKIN_0);
	}
	else if (name == SKIN_1) {
		UserData::getInstance()->setCurrentMod(SKIN_1);
		UserData::getInstance()->addPlayerMod(SKIN_1);
	}
	else if (name == SKIN_2) {
		UserData::getInstance()->setCurrentMod(SKIN_2);
		UserData::getInstance()->addPlayerMod(SKIN_2);
	}
	else if (name == SKIN_3) {
		UserData::getInstance()->setCurrentMod(SKIN_3);
		UserData::getInstance()->addPlayerMod(SKIN_3);
	}
	else if (name == SKIN_4) {
		UserData::getInstance()->setCurrentMod(SKIN_4);
		UserData::getInstance()->addPlayerMod(SKIN_4);
	}
	else if (name == SKIN_5) {
		UserData::getInstance()->setCurrentMod(SKIN_5);
		UserData::getInstance()->addPlayerMod(SKIN_5);
	}
	else if (name == SKIN_6) {
		UserData::getInstance()->setCurrentMod(SKIN_6);
		UserData::getInstance()->addPlayerMod(SKIN_6);
	}
	//((SetingLayer*)getParent())->updateHeroSkin();
}

void SkinLayer::changeSkin(cocos2d::Ref* ref) {
	MenuItemImage* temp = (MenuItemImage*)ref;
	std::string skinName = getSkinIdByTag(temp->getTag());
	std::vector<std::string> playerSkins = UserData::getInstance()->getPlayerMod();
	bool have = false;
	for (auto var : playerSkins) {
		if (skinName == var) {
			have = true;
		}

	}
	if (have) {
		//拥有皮肤改写状态
		updateSkinState(skinName);
	}
	else {
		//判断玩家金币
		if (UserData::getInstance()->getPlayerGoldNum() >= getPriceByName(skinName)) {
			UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() - getPriceByName(skinName));
			updateSkinState(skinName);
		}
		else {
			//弹出计费点
			if (!Dream::getInstance()->getDreamTimes()) {
				DreamLayer* nod = DreamLayer::create(9);
				addChild(nod, 10);
			}
			else {
				auto labe = Label::createWithSystemFont(ChineseWord("TEXT_1"), "Arial", 40);
				labe->setPosition(360, 640);
				labe->setColor(Color3B::WHITE);
				addChild(labe);
				labe->runAction(FadeOut::create(1.5f));
			}
		}
		//updateSkinState(skinName);
	}
	updateButtonState();
}

void SkinLayer::closeView() {
	removeFromParent();
}


std::string SkinLayer::getSkinIdByTag(int tag) {
	switch (tag)
	{
	case SKIN_BTN_0:
		return SKIN_0;
	case SKIN_BTN_1:
		return SKIN_1;
	case SKIN_BTN_2:
		return SKIN_2;
	case SKIN_BTN_3:
		return SKIN_3;
	case SKIN_BTN_4:
		return SKIN_4;
	case SKIN_BTN_5:
		return SKIN_5;
	case SKIN_BTN_6:
		return SKIN_6;
	default:
		return SKIN_0;
	}

}

int SkinLayer::getPriceByName(std::string name) {
	if (name == SKIN_1) {
		return 1000;
	}
	else if (name == SKIN_2) {
		return 1000;
	}
	else if (name == SKIN_3) {
		return 2000;
	}
	else if (name == SKIN_4) {
		return 2000;
	}
	else if (name == SKIN_5) {
		return 5000;
	}
	else if (name == SKIN_6) {
		return 10000;
	}
	else {
		return 0;
	}
}