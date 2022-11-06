/// 头像类
//	用来生成头像

#ifndef __HEAD_PORTRAIT_H__
#define __HEAD_PORTRAIT_H__

#include "cocos2d.h"
USING_NS_CC;

class HeadPortrait : public Node
{
public:
	CREATE_FUNC(HeadPortrait);

	bool init();
	void setHeadProtrait(int dir, std::string name, int photo, int coins);

	//void startProgress(float time);
	//void StopProgress();


	void setTimes(int times);
	void updateName();
	void updateCoin();
private:
	LabelTTF* nameLabel;
	void update(float delta);
	// 头像：【底框，背景色】，【头像，姓名，金币】
	int playerPhoto;
	int playerCoins;
	//ProgressTimer* progress;
	std::string playerName;
	Label* coinsLabel;
	int _dir = -1;;
};

#endif // end MahjongScene.h