#pragma once
#include "cocos2d.h"
#include "FieldMan.h"
#include "Goalkeeper.h"
//球队状态
enum TeamStatus{
    attack,
    defend
};

class FootballTeam : public cocos2d::Node {
public:
	static FootballTeam* create(int teamId,bool teamInLeftField = true);
	virtual bool init(int teamid,bool teamInLeftField);
    void onEnter();
    void onExit();
    
    int teamScore = 0;
    FieldMan* m_pSupportingPlayer;//最佳接球人员
    FieldMan* m_pControllingPlayer;//当前控球的球员
    FieldMan* m_pCloseingPlayer;//离球最近的队员
    
    bool checkShootResult();//射门判定
    int getFootBallTeamId();
    std::string getTeamAttackDirection();//球队进攻方向
	std::vector<FieldMan*> getFootManVector();//获取球员
    Goalkeeper* getGoalkeeper();//获取守门员
    cocos2d::Rect getAttackShootRect();
    cocos2d::Vec2 getTeamShootPoint();//射门坐标
    TeamStatus getTeamStatus();
    void setTeamStatus(TeamStatus s);
    void setControllingMan(FieldMan* man);
    void setTeamInLeftField(bool b);
    void manSpeedUp();//球队加速
    void doTeamShoot();//球队射门
private:
    TeamStatus teamState;
    int teamId = 0;
    bool can_kick_ball = true;//确保开球动作只执行一次
    bool teamInLeftField = true;//队伍目前在左半场
    float teamEnergy = 0;//能量计数
    float teamEnergyRate = 0;//能量增长比率
    cocos2d::Vec2 footManAttackPos =  cocos2d::Vec2(0,0);//一次进攻的目标位置
    cocos2d::Sprite* energy_content_1;
    Goalkeeper* goalkeeper;//守门员
	std::vector<FieldMan*> footManVector;
	std::vector<cocos2d::Vec2> getFootmanFieldVec2();
    std::string getTeamIconName(int tid);
    void generateFootballTeam();
    void goalkeeperSnapBall(bool shot);//守门员扑救
    void logicUpdate(float dt);
    void update(float dt);
};
