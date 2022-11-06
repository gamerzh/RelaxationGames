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
	int turrent_ui_id; // ��ʾui
	double net_per; // ������ϵ��
	double catch_per; // �������ϵ��
	int ui_type; // 1����;2����
	int net_type;  // 1,1����;2,2��;3,����
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
	  //�������
	  Point getLasterOrginPos(){ return m_turret->getLightLaughPos(); }
	  void beginLightShoot();
	  void endLightShoot();
	  void rorateAndShootOnlight(float dt);
	  void shootOnLight(float dt);
	  void setLightFish(Fish* fish);
	  Fish*getLightFish(){ return lightFish; };
	  Sprite* jiguangSp;
	  //�������
	  void beginLockShoot();
	  void endLockShoot();
	  void rorateAndShootOnlock(float dt);
	  void shootOnLock(float dt);
	  void setLockFish(Fish* fish);
	  Fish*getLockFish(){ return lockFish; };
	  ///�Զ����
	  void beginAutoShoot();
	  void endAutoShoot();
	  void rorateAndShootOnAuto(float dt);
	  void shootOnAuto(float dt);


	  float getRarote(){ return m_turret->getRotation(); }
	  //�ո���
	  void getCoinByFish(Fish* fish);
	  //AI
	  void setAIinfo(AI* info);
	  void doAIthing(float dt);
	  void stopAI();
	  void addGoldFishForAi();

	  //�Ʋ�
	  void onBankrupt();
	  void onAIResurgenceCallBack(Node* sender, void* data);
	  void update(float delta); 
	 
	  ///����������Ϣ
	  void refreshTurretInfo();
	  //��ʾ�����Ϣ
	  bool onTurretTouch(Point pos);
	  bool isTurretBeTouch(Point pos);
	  void showRobotInfo();
	  void showPlayerInfo();
	  void removePlayerInfo();
	  void removeRobotInfo();
	  void changeTurrentCallback(Ref*psend); //����
	  void autoShootCallback(Ref*psend);//�Զ�����
	  void onPlayerUpgrade();//�������
	  Turrent getTurrentMupltData(){ return m_turretdata; };
	  //�������Ľ��
	  void costMoney();
	  Vec2 getCoinLabelPos(){ return m_coinLabelPos+getPosition()-getContentSize()/2; };
	  ///��ҿ��ý��Ʈ���� +XX
	  void ShowAddCoinAni(int type, int num);//type��1 ��� 2����ʯ

	  ///���������
	  void ShowLockTurretTip();
	  bool TouchTheLockNode(Touch *pTouch, Event *pEvent);
	  void changeNewTurret();
	  void changeDataByBtnType();
	  void upgradeTurret(Ref* psend);
	  void degradeTurret(Ref* psend);
	  void onLockTheTurrent();


	  bool isCanShoot();
	  //������һ������
	  void ChangeNextRoom(Ref*psend);

	  Vec2 getPaoWorldpos();
private:
	Vec2 m_coinLabelPos;
	Turrent  m_turretdata;
	int m_btType=0; //0��ͨ 1���� -1������
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
