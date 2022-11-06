#pragma once
#include "cocos2d.h"
#include "turret/Turret.h"
#include "domain/ai/AI.h"
#include "domain/user/user.h"
#include "domain/room/RoomPlayer.h"
#include "fish/Fish.h"
#include "config/ConfigTurrent.h"

USING_NS_CC;

struct TurretData
{
	int turrent_id;
	int turrent_ui_id; // 显示ui
	double net_per; // 打击面积系数
	double catch_per; // 捕获概率系数
	int ui_type; // 1火焰;2冰冻
	int net_type;  // 1,1张网;2,2张;3,三张
	TurretData(){};
	void init(int id, int uiid, double netPer, double catchper, int uiType, int netType){ turrent_id = id, turrent_ui_id = uiid, net_per = netPer, catch_per = catchper; ui_type = uiType, net_type = netType; }
};



class PlayerTurret : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(PlayerTurret);
	  void initWithDate(User* user,int index);
	  void initWithDate(RoomPlayer* user);
	  void createPlayerCoin(User* user, int index);
	  void createPlayerCoin(RoomPlayer* user);

	  void initTurretWithType();
	  void initTurretWithTypeForRobot();
	  void setUpgradeButton();
	  void rorateTurret(float angle);
	  void shoot(float);
	  //闪电射击
	  Point getLasterOrginPos(){ return m_turret->getLightLaughPos(); }
	  void beginLightShoot();
	  void endLightShoot();
	  void rorateAndShootOnlight(float dt);
	  void shootOnLight(float dt);
	  void setLightFish(Fish* fish);
	  Fish*getLightFish(){ return lightFish; };
	  Sprite* jiguangSp;
	  //锁定射击
	  void beginLockShoot();
	  void endLockShoot();
	  void rorateAndShootOnlock(float dt);
	  void shootOnLock(float dt);
	  void setLockFish(Fish* fish);
	  Fish*getLockFish(){ return lockFish; };
	  ///自动射击
	  void beginAutoShoot();
	  void endAutoShoot();
	  void rorateAndShootOnAuto(float dt);
	  void shootOnAuto(float dt);


	  float getRarote(){ return m_turret->getRotation(); }
	  //收割鱼
	  void getCoinByFish(Fish* fish);
	  //AI
	  void setAIinfo(AI* info);
	  void doAIthing(float dt);
	  void stopAI();
	  void addGoldFishForAi();

	  //破产
	  void onBankrupt();
	  void onAIResurgenceCallBack(Node* sender, void* data);
	  void update(float delta); 
	 
	  ///更新炮塔信息
	  void refreshTurretInfo();
	  //显示玩家信息
	  bool onTurretTouch(Point pos);
	  bool isTurretBeTouch(Point pos);
	  void showRobotInfo();
	  void showPlayerInfo();
	  void removePlayerInfo();
	  void removeRobotInfo();
	  void changeTurrentCallback(Ref*psend); //换炮
	  void autoShootCallback(Ref*psend);//自动开炮
	  void onPlayerUpgrade();//玩家升级
	  Turrent getTurrentMupltData(){ return m_turretdata; };
	  //攻击消耗金币
	  void costMoney();
	  Vec2 getCoinLabelPos(){ return m_coinLabelPos+getPosition()-getContentSize()/2; };
	  ///金币框获得金币飘数字 +XX
	  void ShowAddCoinAni(int type, int num);//type：1 金币 2：钻石

	  ///点击解锁炮
	  void ShowLockTurretTip();
	  bool TouchTheLockNode(Touch *pTouch, Event *pEvent);
	  void changeNewTurret();
	  void changeDataByBtnType();
	  void upgradeTurret(Ref* psend);
	  void degradeTurret(Ref* psend);
	  void onLockTheTurrent();


	  bool isCanShoot();
	  //进入下一个房间
	  void ChangeNextRoom(Ref*psend);

	  Vec2 getPaoWorldpos();
private:
	Vec2 m_coinLabelPos;
	Turrent  m_turretdata;
	int m_btType=0; //0普通 1升级 -1降级；
	  int turretType;
	
	  void onExit();
	  LabelAtlas* nCurLevel;
	  LabelAtlas*m_CoinLabel;
	  LabelAtlas*m_DiamondLabel;
	  AI* m_aiinfo;
	  CC_SYNTHESIZE(int, nMaxlevel, nMaxLevel);
	  bool isRobot = true;
	  TurretData turretdata;
	  Turret* m_turret;
	  int nChairNoIndex = -1;
	  int nNowMoney;
	  RoomPlayer* m_robotData;

	  CC_SYNTHESIZE(bool, m_isUsingLight, isUsingLight);
	  CC_SYNTHESIZE(bool, m_isShowInfo, IsShowInfo);
	  CC_SYNTHESIZE(Point, targetPos, TargetPos);
	  Sprite* aniFishLockNode = NULL;
	  Sprite*aniFishLightNode = NULL;	 
	  Fish* lockFish = nullptr;
	  Fish* lightFish = nullptr;
	  int goldfishcounts = 1;
};
