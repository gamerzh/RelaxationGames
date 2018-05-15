#include "StartScene.h"
#include "GameScene.h"
#include "UserData.h"

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

	auto box = Sprite::create("player_box.png");
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
	auto sound = MenuItemImage::create("sound.png", "sound.png", CC_CALLBACK_0(StartScene::soundManage, this));
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
	auto goldnum = LabelAtlas::create(String::createWithFormat("%d", UserData::getInstance()->getPlayerGoldNum())->_string, "num_white.png", 16, 24, '0');
	goldnum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	goldnum->setPosition(win.width / 2, win.height*0.97);
	addChild(goldnum);
}

void StartScene::startGame() {
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void StartScene::soundManage() {


}


void StartScene::changePlayerModle() {

}