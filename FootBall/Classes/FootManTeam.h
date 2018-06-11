#pragma once
#include "cocos2d.h"
#include "FootMan.h"

/*
�����������Ϣ
*/
struct FootManProperty {
	std::string footImage;
	std::string name;
	float runSpeed;
	int skillType;
	bool goalkeeper;
};

struct FootManTeamProperty {
	int teamId;//��ӱ��
	std::string teamName;//�������
	std::string teamBanner;//�������
	std::vector<FootManProperty> footManVec;//��Ա�����б�
};

class FootManTeam : public cocos2d::Ref {
public:
	static FootManTeam* create(int teamId,std::vector<FootManProperty> provec);
	virtual bool init(int teamId, std::vector<FootManProperty> provec);
	int getTeamId();
	std::vector<FootMan*> getAllFootMan();
private:
	std::vector<FootMan*> footManVec;
	int teamId = 0;
	void createFootMan(std::vector<FootManProperty> provec);
};