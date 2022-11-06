#ifndef __AIRULE_H__
#define __AIRULE_H__

#include "Player.h"

class AIRules
{
public:
	AIRules();

	static AIRules* getInstance();

	bool init();
	Card* getCardToPlay(MahjongDrawer & drawer);
	void setPlayerDrawer(MahjongDrawer*drawer){ _playerdrawer = drawer; };
private:
	static AIRules* instance;

	int getCardToPlayIndex(MahjongDrawer & drawer);
	int getCardToPlayIndexForQingYiSe(MahjongDrawer & drawer);

	const int noDianPao = 0;
	int getFirstEquel(MahjongDrawer & drawer);
	int getFirstTrible(MahjongDrawer & drawer);
	MahjongDrawer* _playerdrawer;


	//utill;
	int getABCCardStartIndex(MahjongDrawer& drawer);///获得一副牌中ABC牌型的起始位置
};



#endif
