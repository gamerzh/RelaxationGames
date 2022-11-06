#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class FishAniMannage{
public:
	static FishAniMannage* getInstance();
	static void destroyInstance();

	bool loadAniByJsonAndPlist(const char* jsonName, const char* plistName);
	Animate* getAnimate(const char *animatname);	
	SpriteFrame *getSpriteById(int fishid);
private:
	static FishAniMannage* _pInstance;
	std::map<int, std::vector<std::string>> map_FishidToAnis;
};