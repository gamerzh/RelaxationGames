#pragma once
#include "cocos2d.h"
#include "FootMan.h"

//���ǵ���Ա��ͼ������,��Ա��ͳһ��ӵ�GameLayer��

class FootballTeam : public cocos2d::Node {
public:
	static FootballTeam* create(int teamId);
	virtual bool init(int teamid);
	std::vector<FootMan*> getFootManVector();

private:
	FootMan* m_pControllingPlayer;//��ǰ����Ķ�Ա
	FootMan* m_pSupportingPlayer;//֧Ԯ�Ķ�Ա
	FootMan* m_pReceivingPlayer;//����Ķ�Ա
	FootMan* m_pPlayerClosestToBall;//��������Ķ�Ա
	int teamId = 0;//��ӱ��
	std::vector<FootMan*> footManVector;//��Ա����
};