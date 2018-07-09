#pragma once
#include "cocos2d.h"

enum TeamAbilityType
{
	speed,
	shoot,
	energy
};

class TeamAbility : public cocos2d::Node {
public:
	static TeamAbility* create(TeamAbilityType type);
	virtual bool init(TeamAbilityType type);
private:
	void getPropLevel();
	std::string getFileNameByType(TeamAbilityType type);
	int getLevelByType(TeamAbilityType type);
	int getPriceByType(TeamAbilityType type);
};