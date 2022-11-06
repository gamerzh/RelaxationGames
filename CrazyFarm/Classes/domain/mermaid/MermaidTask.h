#pragma once
#include "cocos2d.h"

using namespace cocos2d;

struct MermaidTaskConfigInfo {
    int start_wait_time;    //获取任务开始等待时间
    int continue_time;      //获取任务持续时间
};

struct MermaidTaskItem {
    int fishId;
    int goal_num;
    int current_num;
};

struct MermaidTaskOnlineInfo {
    int coins;    // 金币消耗
    std::vector<MermaidTaskItem> mermaidTaskItems;      //任务状态
};

class MermaidTask {

public:
    static MermaidTask* getNewMermaidTask();
    static bool isAllowUserSkillById(int skillId);  // 在任务执行期是否允许使用某个技能

    void addCoins(int coins);    // 增加时间段内的金币消耗
    void addOneCatchFishById(int fishId);      // 捕获鱼1只
    bool isSuccess();       // 是否完成任务
    
    MermaidTaskConfigInfo getMermaidTaskConfigInfo();
    MermaidTaskOnlineInfo getMermaidTaskOnlineInfo();
    
private:
    MermaidTask();
    
    MermaidTaskConfigInfo mermaidTaskConfigInfo;
    MermaidTaskOnlineInfo mermaidTaskOnlineInfo;
};

