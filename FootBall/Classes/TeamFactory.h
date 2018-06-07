#pragma once
#include "cocos2d.h"
#include "FootManTeam.h"

/*
�����������Ϣ
*/
struct FootManProperty {
	std::string footImage;
	std::string name;
	float runSpeed;
	int skillType;
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
	std::vector<FootManTeam*> getFootManTeamVector();
	std::vector<FootManTeamProperty> getFootManTeamPropertyVector();//�����Ϣ�б�
private:
	static  TeamFactory* m_instance;
	TeamFactory() {};
	std::vector<FootManTeam*> footTeamVec;
};