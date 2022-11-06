#include "cocos2d.h"
using namespace cocos2d;


class PayingDialog :public Node {

public:

	static PayingDialog* ShowPayDialog();
	static void RemovePayDialog();
	CREATE_FUNC(PayingDialog);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	
private:
	bool init();

};

