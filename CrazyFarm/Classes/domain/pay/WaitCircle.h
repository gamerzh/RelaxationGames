#include "cocos2d.h"
using namespace cocos2d;


class WaitCircle :public Sprite {

public:

	static WaitCircle* ShowPayWaitCircle();
	static void RemovePayWaitCircle(std::string prepayid);
	static void sendRequestWaitCirCle(std::string prepayid);
	CREATE_FUNC(WaitCircle);
	void DemandEntry();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void setMyPrepayid(std::string prepayid){ m_prepayid = prepayid; };
private:
	
	bool init();
	float nNowTime = 0;
	std::string m_prepayid;
	int reqnum = 0;
};

