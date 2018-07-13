#pragma once
#include "cocos2d.h"
#include "FootMan.h"

//���ǵ���Ա��ͼ������,��Ա��ͳһ��ӵ�GameLayer��

class FootballTeam : public cocos2d::Node {
public:
	static FootballTeam* create(int teamId);
	virtual bool init(int teamid);
	std::vector<FootMan*> getFootManVector();
	void setTeamInLeftField(bool b);
private:
	bool teamInLeftField = true;//��ӿ�ʼʱ����볡
	FootMan* m_pControllingPlayer;//��ǰ����Ķ�Ա
	FootMan* m_pSupportingPlayer;//֧Ԯ�Ķ�Ա
	FootMan* m_pReceivingPlayer;//����Ķ�Ա
	FootMan* m_pPlayerClosestToBall;//��������Ķ�Ա
	int teamId = 0;//��ӱ��
	std::vector<FootMan*> footManVector;//��Ա����
	std::vector<cocos2d::Vec2> getLeftFieldVec2();//��ȡ��볡��Ա��ʼ��λ��
	std::vector<cocos2d::Vec2> getRightFieldVec2();//��ȡ��볡��Ա��ʼ��λ��
};