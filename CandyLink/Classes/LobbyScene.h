#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;


class LobbyScene : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void startGame();
    void music();
    void musicCallback(Ref* pSender);
    void updateScene(float dt);
    void showMoreGame();
    void payTehui();
    CREATE_FUNC(LobbyScene);
    void ShowAni(float dt);
    void BallAniCallback(Node* pSender);
    void onTouchEnded(Touch *touch, Event *unused_event);
    bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
    void update(float delta);
    void autobegingame(float dt);
    void ShowPayPoints(float dt);
    void LogEventOnExit();
    void ballani(float dt);
    //DAY 
    int getDayCnt(const char* key);
    void addDayCnt(const char* key);
    int  XygGetToday();
private:
    MenuItemImage* start_btn;
    MenuItemSprite* settingBtnOkItem_tehui;
    Sprite*     Title;
    Vector<Sprite*> balls;
    void quitGame();
};
#endif
