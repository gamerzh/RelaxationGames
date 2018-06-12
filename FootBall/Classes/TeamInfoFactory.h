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


class TeamFactory : public cocos2d::Ref {
public:
	static  TeamFactory* getInstance();
	FootManTeamProperty getTeamPropertyById(int teamId);
private:
	static  TeamFactory* m_instance;
	TeamFactory() {};
	std::vector<FootManTeamProperty> footManTeamPropertyVec;
	std::vector<FootManTeamProperty> getFootManTeamPropertyVector();//�����Ϣ�б�
};