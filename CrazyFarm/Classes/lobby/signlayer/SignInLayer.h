#ifndef __SIGNINLAYER_H__
#define __SIGNINLAYER_H__
#include "cocos2d.h"
#include "SpliceCell.h"
#include "SignMannger.h"
USING_NS_CC;

class SignInLayer : public Layer
{
public:
	virtual bool init(std::vector<SignItem> items);
	static SignInLayer * createLayer(std::vector<SignItem> items);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void updata(float dt);
private:
	void gainRewardsCallback(Ref* psend);
	
	int getCurindexByRewards(SignItem item);

	Vector<SpliceCell*> SpliceCells;
	

	std::vector<SignItem> _items;

	std::vector<int> curindexs;
};






#endif