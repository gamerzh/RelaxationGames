#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "config/ConfigRoom.h"
#include "network/HttpClient.h"
#include "domain/globalschedule/GlobalSchedule.h"
using namespace cocos2d::network;
USING_NS_CC;


class  roomCell:public MenuItemImage
{
public:
	static roomCell * createCell(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback);
	CC_SYNTHESIZE(int, minEnterLevel, MinEnterLevel);
	CC_SYNTHESIZE(bool, isLock, Islock);
	CC_SYNTHESIZE(int, roomid, Roomid);
};





class LobbyScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void update(float delta);
	
    CREATE_FUNC(LobbyScene);
	void guizuCallback(Ref*psend);
	void refreshCoinLabel();
	void showVipCallBack(Ref*psend);
	void quickBeginCallback(Ref*psend);
	void showSign(float dt);
private:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	
	void showMarquee(float dt);
	void createRoomLayer();
	///°´Å¥»Øµ÷
	void payCoinCallback(Ref*psend);
	void payDiamondCallback(Ref*psend);
	void bagButtonCallback(Ref*psend);
	void changeRewardCallback(Ref*psend);

	void RankListCallback(Ref*psend);
	void FirstPayCallback(Ref*psend);
	void onExitCallback(Ref*psend);
	void onAudioOnOffCallback(Ref*psend);
	void feedBackCallback(Ref*psend);

	void onExitSureCallback(Ref*psend);
	void endGameCallback(Ref*psend);
private:
	LabelTTF* userdiamond;
	LabelTTF* userCoin;
	MenuItemImage* fistPay;
	Sprite*lang;
	Sprite*langspEmpty;
	Vector<roomCell*> roomCells;
	LabelTTF* userName;
	LabelAtlas *viplevel;
};
#endif