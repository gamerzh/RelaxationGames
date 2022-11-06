#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "utill/OBB.h"
USING_NS_CC;


class ConfigFishCollisionOBB {
    
public:
	ConfigFishCollisionOBB();
	static ConfigFishCollisionOBB* getInstance();
    
	bool LoadConfig();

	std::vector<ObbData> getFishFOBBPoints(int uiId);



private:
	static ConfigFishCollisionOBB* _instance;
	std::map<int, std::vector<ObbData>> uiidToOBBdatas;
};

