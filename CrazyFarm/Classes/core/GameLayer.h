#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "fish/FishManage.h"
#include "bullet/BulletManage.h"
#include "turret/PlayerTurret.h"
#include "net/Net.h"
#include "domain/room/RoomManager.h"
#include "domain/magnate/MagnateManager.h"
USING_NS_CC;
enum TouchType
{
	TouchInNormal,
	TouchInLock,
	TouchInBoom,
	TouchInAutoShoot,
	TouchInLight
};

class GameLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void loadNewMonent(float ffTime);
	void RefreShmyPlayerTurret();
	
	void addReward(int itemid, int num);



	Vector<PlayerTurret*> GetOtherTurret(){ return otherTurrets; }

	void createNet(Bullet *bullet);//������
	PlayerTurret* GetMyTurret(){ return myTurret; }
	//�齱�����������̻�
	void onGetReward(int itemid, int num);
	//ĳ���������߻���ʯ
	void onGetRewardByfish(PlayerTurret*turrent,Fish*fish,int itemid,int num);
private:
	void createTurret();//����������������
	void addTouchEvent();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	//�����ӵ�	

	void rotateTurret(float degree, PlayerTurret* turret);//��ת����

	void showYourChairno();

	void AiUpdata(float dt);
	void onExit();
	void onEnter();
	virtual void onEnterTransitionDidFinish();
	//Updata
	void collisionUpdate(float dt);
	void update(float dt);
	void shootUpdata(float dt);
	//����
public:
	void beginLight();
	void endLight();
	void LightUpdata(float dt);
	bool lightTouchEvent(Touch *touch, Event  *event);
 //����
public:
	void beginLock();
	void endLock();
private:
	void LockUpdata(float dt);
	bool lockTouchEvent(Touch *touch, Event  *event);
	CC_SYNTHESIZE(bool, bIsOnSkillLock, bisOnSkillLock);
//�˵�
public:
	void beginSkillBoom();
	void endSkillBoom(); 
	void onBoomCatchFish(Point pos); 
private:
	bool boomTouchEvent(Touch *touch, Event  *event);
	
//�Զ�����
public:
	void beginAutoShoot();
	void endAutoShoot();
private:
	Point autoShootPos;
	bool AutoShootTouchEvent(Touch *touch, Event  *event);
////////////����
public:
	void useFreeze(PlayerTurret*turret);
	void onFreezeEnd(PlayerTurret*turret);
////�㳱����
	void onClearFish();
	void onClearFishUpdata(float dt);
	void onClearFishFinish();
private:
	void initFishAndBulletData();

	//�����
	bool onTouTurret(Point pos);
	void removePlayerInfo();
	void calculateFreeChair();
	//utill
	static bool sortFish(const Fish * m1, const Fish * m2);

	PlayerTurret* myTurret;
	Vector<PlayerTurret*> otherTurrets;
	std::vector<RoomPlayer> players;
	int m_index = -1;
	EventListenerTouchOneByOne* touchListener;
	bool isShoot = true;
//����¼�
	void changeTouchFunByTouchType(TouchType type);
	TouchType m_touchType;
	TouchType m_lasttouchType;


	std::list<TouchType> _touchtypes;
	Sprite* game_bg;

	CC_SYNTHESIZE(Node*, createFishAcNode, CreateFishAcNode);
	CC_SYNTHESIZE(bool, isShowYourChairno, IsShowYourChairno);
	Point touchpos;
	bool istouched = false;
	float shootTemp = 0;


	bool isInitData = false;


	DrawNode* drawnode;
	Fish* fish;
};
#endif