#pragma once
#include "cocos2d.h"
#include "FootMan.h"

//球队状态
enum TeamStatus{
    attack,
    defend,
    neutrality//中立
};

class FootballTeam : public cocos2d::Node {
public:
    int teamScore =0;
	static FootballTeam* create(int teamId,bool teamInLeftField = true);
	virtual bool init(int teamid,bool teamInLeftField);
    void onEnter();
    void onExit();
    int getFootBallTeamId();
    bool checkShootResult();
    void doTeamShoot();//球队射门
    std::string getTeamAttackDirection();
	std::vector<FootMan*> getFootManVector();
    cocos2d::Rect getAttackShootRect();
    cocos2d::Vec2 getTeamShootPoint();//射门坐标
    FootMan* getGoalkeeper();//获取守门员
    FootMan* m_pSupportingPlayer;//最佳接球人员
    FootMan* m_pControllingPlayer;//当前控球的球员
    FootMan* m_pCloseingPlayer;//离球最近的队员
    TeamStatus getTeamStatus();
    void setTeamStatus(TeamStatus s);
    void setControllingMan(FootMan* man);
    void setTeamInLeftField(bool b);
    void setFootballTeamAI(FootMan* man = nullptr);//设置队伍的AI
    void manSpeedUp();//球队加速
private:
    TeamStatus teamState;
    int teamId = 0;
    bool teamInLeftField = true;//队伍目前在左半场
    bool goalkeeperReady = true;//守门员在传球
    float teamEnergy = 0;//能量计数
    float teamEnergyRate = 0;//能量增长比率
    cocos2d::Vec2 footManAttackPos =  cocos2d::Vec2(0,0);//一次进攻的目标位置
    FootMan* goalkeeper;//守门员
	std::vector<FootMan*> footManVector;
	std::vector<cocos2d::Vec2> getLeftFieldVec2();
	std::vector<cocos2d::Vec2> getRightFieldVec2();
    std::string getTeamIconName(int tid);
    void generateFootballTeam();
    void logicUpdate(float dt);
    void update(float dt);
};
