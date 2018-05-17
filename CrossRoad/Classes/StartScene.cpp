#include "StartScene.h"
#include "GameScene.h"
#include "UserData.h"
#include "SelectLayer.h"
#include "Audio.h"

Scene* StartScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StartScene::create();

	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	loadView();
	return true;
}

void StartScene::loadView() {
	auto win = Director::getInstance()->getWinSize();

	auto black = LayerColor::create(Color4B(255, 255, 255, 100), win.width, win.height);
	addChild(black);

	auto box = Sprite::create("player_box.jpg");
	box->setPosition(win.width / 2, win.height / 2);
	addChild(box);

	//start_game.png
	auto start = MenuItemImage::create("start_btn.png", "start_btn.png", CC_CALLBACK_0(StartScene::startGame, this));
	auto boxMenu = Menu::create(start, NULL);
	boxMenu->setPosition(win.width / 2, win.height / 7);
	addChild(boxMenu);

	//change_player.png
	auto change = MenuItemImage::create("change_player.png", "change_player.png", CC_CALLBACK_0(StartScene::changePlayerModle, this));
	auto cangeMenu = Menu::create(change, NULL);
	cangeMenu->setPosition(win.width * 0.85, win.height *0.78);
	addChild(cangeMenu);

	//sound
	auto sound = MenuItemImage::create("sound_on.png", "sound_on.png", CC_CALLBACK_1(StartScene::soundManage, this));
	updateSound(sound);
	sound->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	auto soundMenu = Menu::create(sound, NULL);
	soundMenu->setPosition(0, win.height);
	addChild(soundMenu);

	//gold
	auto goldbg = Sprite::create("gold_box.png");
	goldbg->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	goldbg->setPosition(win.width / 2, win.height);
	addChild(goldbg);
	//num_white
	auto number = String::createWithFormat("%d", UserData::getInstance()->getPlayerGoldNum()) ->_string;
	auto goldnum = LabelAtlas::create(number, "gold_num_small.png", 41, 40, '0');
	goldnum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	float offset = 3.2 * number.size();
	goldnum->setPosition(win.width / 2+ offset, win.height*0.97);
	addChild(goldnum);

	auto playerMod = Sprite::create("player_mod_0.png");
	playerMod->setPosition(win.width / 2, win.height / 2);
	addChild(playerMod);
}

void StartScene::startGame() {
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void StartScene::soundManage(Ref* ref) {
	Audio::getInstance()->controllSound(!UserData::getInstance()->getMusicStatus());
	MenuItemImage* imge = (MenuItemImage*)ref;
	updateSound(imge);
}

void StartScene::updateSound(MenuItemImage* imge) {
	if (UserData::getInstance()->getMusicStatus()) {
		imge->setNormalImage(Sprite::create("sound_on.png"));
		imge->setSelectedImage(Sprite::create("sound_on.png"));
	}
	else {
		imge->setNormalImage(Sprite::create("sound_off.png"));
		imge->setSelectedImage(Sprite::create("sound_off.png"));
	}
}


void StartScene::changePlayerModle() {
	auto lau = SelectLayer::create();
	addChild(lau);
}