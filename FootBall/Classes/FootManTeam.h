#pragma once
#include "cocos2d.h"
/*
	◊„«Ú∂”≈‰÷√–≈œ¢
*/
struct FootManProperty {
	std::string footImage;
	std::string name;
	float runSpeed;
	int skillType;
};

class FootManTeam : public cocos2d::Ref {
public:
	static  FootManTeam* getInstance();
	std::vector<FootManProperty> getFootManVector();
private:
	static  FootManTeam* m_instance;
	FootManTeam() {};
};