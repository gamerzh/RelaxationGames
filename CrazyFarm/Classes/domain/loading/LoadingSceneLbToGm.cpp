#include "domain/loading/LoadingSceneLbToGm.h"
#include "config/ConfigSign.h"
#include "config/ConfigManager.h"
#include "fish/FishAniMannage.h"
#include "utill/AnimationUtil.h"
#include "utill/FunUtil.h"
#include "server/HttpMannger.h"
#include "domain/user/User.h"
#include "lobby/LobbyScene.h"
#include "domain/user/DeviceInfo.h"
#include "domain/login/LoginMannger.h"
#include "utill/Chinese.h"
#include "utill/CircleMoveTo.h"
#include "core/GameScene.h"
#include "data/GameData.h"
#include "domain/loading/LoadingScene.h"
Scene* LoadingSceneLbToGm::createScene()
{
	auto scene = Scene::create();

	auto layer = LoadingSceneLbToGm::create();

	scene->addChild(layer, 0, 888);

	return scene;
}

bool LoadingSceneLbToGm::init()
{
	if (!Layer::init())
	{
		return false;
	}
	GameData::getInstance()->setisLoadMsgOnGame(true);
	auto bg = Sprite::create("loading2.jpg");
	bg->setPosition(480, 270);
	addChild(bg);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/bubble/aniBubble%d.png", "aniBubble", 3.5f, 46);
	load();

	auto aniNode = Sprite::create();
	aniNode->setPosition(900, 150);
	addChild(aniNode, 5);
	aniNode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBubble")));

	aniNode = Sprite::create();
	aniNode->setPosition(76, 150);
	addChild(aniNode, 5);
	aniNode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBubble")));


	auto loadingbarFrame = Sprite::create("loadingbar1.png");
	loadingbarFrame->setPosition(480,75);
	addChild(loadingbarFrame);

	loadingBar = ui::LoadingBar::create("loadingbar2.png");
	loadingBar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	loadingBar->setPosition(loadingbarFrame->getContentSize() / 2+Size(10,0));
	loadingbarFrame->addChild(loadingBar);
	showTip();

	scheduleUpdate();

	

	return true;
}

void LoadingSceneLbToGm::update(float dt)
{
	loadingBar->setPercent(((float)temp) / 46.0f*100+1);
	if (temp>=46)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::create()));
		unscheduleUpdate();
	}
}
void LoadingSceneLbToGm::load()
{
	loadRes();
}


void LoadingSceneLbToGm::loadAniWithPng(const char *filepath, const char *animatname, float time, int numOfpng)
{
	for (int i = 1; i <= numOfpng;i++)
	{
		auto path = String::createWithFormat(filepath, i);
		LoadAniData*data = nullptr;
		if (i==numOfpng)
		{
			data = new LoadAniData();
			strcpy(data->animatname, animatname);
			strcpy(data->filepath, filepath);
			data->time = time;
			data->numOfpng = numOfpng;
		}
		Director::getInstance()->getTextureCache()->addImageAsync(path->getCString(),
			CC_CALLBACK_1(LoadingSceneLbToGm::imageAsyncCallback, this, data));
		
	}
}
void LoadingSceneLbToGm::imageAsyncCallback(Texture2D* texture, void*aniData)
{
	if (aniData == nullptr)
	{
		return;
	}
	LoadAniData*data = (LoadAniData*)aniData;
	AnimationUtil::getInstance()->addAnimationBySpriteName(data->filepath, data->animatname, data->time, data->numOfpng);
	delete data;
	temp++;
}

void LoadingSceneLbToGm::loadFishAni(const char* PngName, const char* jsonName, const char* plistName)
{
	LoadFishAniData*data = new LoadFishAniData();
	strcpy(data->jsonName, jsonName);
	strcpy(data->plistName, plistName);
	Director::getInstance()->getTextureCache()->addImageAsync(PngName,
		CC_CALLBACK_1(LoadingSceneLbToGm::imageFishAniAsyncCallback, this, data));
}
void LoadingSceneLbToGm::imageFishAniAsyncCallback(Texture2D* texture, void*aniData)
{
	LoadFishAniData*data = (LoadFishAniData*)aniData;
	FishAniMannage::getInstance()->loadAniByJsonAndPlist(data->jsonName, data->plistName);
	delete data;
	temp++;
}






void LoadingSceneLbToGm::loadRes()
{
	//ÓÎÏ·ÄÚ¶¯»­
	loadAniWithPng("game/ui/ani/TX_DianGuang/TX_DianGuang_%d.png", "aniJiGuangBottom", 0.4f, 6);
	loadAniWithPng("game/ui/ani/TX_JiGuang/TX_JiGuang_%d.png", "aniJiGuangBar", 0.2f, 3);
	loadAniWithPng("game/ui/ani/TX_BossLight/TX_BOSS_%d.png", "aniBossLight", 1.0f, 16);
	loadAniWithPng("game/ui/ani/TX_GoldFish/aniGoldfish_%d.png", "aniGoldfish", 2.0f, 18);
	loadAniWithPng("game/ui/ani/TX_DianQiu/TX_DianQiu_%d.png", "aniDianQiu", 1.0f, 13);
	loadAniWithPng("game/ui/ani/TX_shandian/shandian_%d.png", "aniShandian", 0.2f, 4);
	loadAniWithPng("game/ui/ani/TX_huanpao/aniHuanpao_%d.png", "aniHuanpao", 0.3f, 7);
	loadAniWithPng("game/ui/ani/TX_guangquan/guangqiu_%d.png", "aniGuangqiu", 0.15f, 5);
	loadAniWithPng("game/ui/ani/shootFire/aniShoot%d.png", "aniShoot", 0.3f, 5);
	loadAniWithPng("game/ui/ani/net_ice/netIce%d.png", "iceNet", 0.7f, 18);
	loadAniWithPng("game/ui/ani/net_fire/netFire%d.png", "fireNet", 0.7f, 18);
	loadAniWithPng("game/ui/ani/gold/goldAni_%d.png", "aniGold", 0.3f, 5);
	loadAniWithPng("game/ui/ani/silver/yinbi_%d.png", "aniSilver", 0.3f, 5);
	loadAniWithPng("game/ui/ani/zhaohuan/TX_ZhaoHuan_%d.png", "aniZhaoHuan", 1.1f, 37);
	loadAniWithPng("game/ui/ani/TX_DongJie/TX_qpdj_%d.png", "aniTXTdj", 1.1f, 14);
	loadAniWithPng("game/ui/ani/TX_BaoZha/TX_BaoZha_%d.png", "aniTXTBoom", 2.2f, 28);
	loadAniWithPng("game/ui/ani/TX_ShiYongJiNeng/TX_SYJN_%d.png", "aniTurretLock", 0.5f, 6);
	loadAniWithPng("game/ui/ani/TX_MiaoZhun/TX_MiaoZhun_%d.png", "aniFishLock", 0.8f, 10);
	loadAniWithPng("game/ui/ani/TX_ShengJi/TX_ShengJi_%d.png", "aniShengji", 1.5f, 21);
	//load fish ani
	for (int i = 1; i <= 10; i++)
	{
		auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", i);
		auto pngPath = String::createWithFormat("game/ui/fish/fish_frame_%d.png", i);
		loadFishAni(pngPath->getCString(), jsonPath->getCString(), plistPath->getCString());
	}
	for (int i = 30; i <= 37; i++)
	{
		auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", i);
		auto pngPath = String::createWithFormat("game/ui/fish/fish_frame_%d.png", i);
		loadFishAni(pngPath->getCString(), jsonPath->getCString(), plistPath->getCString());
	}
	for (int i = 40; i <= 44; i++)
	{
		auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", i);
		auto pngPath = String::createWithFormat("game/ui/fish/fish_frame_%d.png", i);
		loadFishAni(pngPath->getCString(), jsonPath->getCString(), plistPath->getCString());
	}
	for (int i = 50; i <= 52; i++)
	{
		auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", i);
		auto pngPath = String::createWithFormat("game/ui/fish/fish_frame_%d.png", i);
		loadFishAni(pngPath->getCString(), jsonPath->getCString(), plistPath->getCString());
	}
	auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", 60);
	auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", 60);
	auto pngPath = String::createWithFormat("game/ui/fish/fish_frame_%d.png", 60);
	loadFishAni(pngPath->getCString(), jsonPath->getCString(), plistPath->getCString());
}







void LoadingSceneLbToGm::showTip()
{
	int randNum = rand() % 10 + 1;
	auto str = String::createWithFormat("LoadingTip%d", randNum);
	auto label = LabelTTF::create(ChineseWord(str->getCString()).c_str(), "arial", 21);
	label->setColor(Color3B::WHITE);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	label->setPosition(480, 30);
	addChild(label);
}