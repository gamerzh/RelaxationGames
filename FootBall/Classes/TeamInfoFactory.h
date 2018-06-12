#pragma once
#include "cocos2d.h"

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


class TeamInfoFactory : public cocos2d::Ref {
public:
	static  TeamInfoFactory* getInstance();
	FootManTeamProperty getTeamPropertyById(int teamId);
	std::vector<FootManTeamProperty> getFootManTeamPropertyVector();//�����Ϣ�б�
private:
	static  TeamInfoFactory* m_instance;
	TeamInfoFactory() {};
	std::vector<FootManTeamProperty> footManTeamPropertyVec;
};