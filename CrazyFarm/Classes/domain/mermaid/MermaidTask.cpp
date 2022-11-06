#include "domain/mermaid/MermaidTask.h"

MermaidTask::MermaidTask(){
	mermaidTaskConfigInfo.start_wait_time =420; //[420]
    mermaidTaskConfigInfo.continue_time = 300;///正式时间300
    
    mermaidTaskOnlineInfo.coins = 0;
    
    MermaidTaskItem mermaidTaskItem1;
    mermaidTaskItem1.fishId =1 + rand()%10;
    mermaidTaskItem1.goal_num = 2;
    mermaidTaskItem1.current_num = 0;
    mermaidTaskOnlineInfo.mermaidTaskItems.push_back(mermaidTaskItem1);
    
    MermaidTaskItem mermaidTaskItem2;
    mermaidTaskItem2.fishId =30 + rand()%7;
    mermaidTaskItem2.goal_num = 1;
    mermaidTaskItem2.current_num = 0;
    mermaidTaskOnlineInfo.mermaidTaskItems.push_back(mermaidTaskItem2);
    
    MermaidTaskItem mermaidTaskItem3;
    mermaidTaskItem3.fishId =40 + rand()%4;
    
    mermaidTaskItem3.goal_num = 1;
    mermaidTaskItem3.current_num = 0;
    mermaidTaskOnlineInfo.mermaidTaskItems.push_back(mermaidTaskItem3);
}

void MermaidTask::addCoins(int coins) {
    if(coins > 0) {
        mermaidTaskOnlineInfo.coins += coins;
    }
}

void MermaidTask::addOneCatchFishById(int fishId) {
    for(int i=0; i<mermaidTaskOnlineInfo.mermaidTaskItems.size();i++) {
        if( fishId == mermaidTaskOnlineInfo.mermaidTaskItems.at(i).fishId ) {
			if (mermaidTaskOnlineInfo.mermaidTaskItems.at(i).current_num==mermaidTaskOnlineInfo.mermaidTaskItems.at(i).goal_num)
			{
				return;
			}
            mermaidTaskOnlineInfo.mermaidTaskItems.at(i).current_num += 1;
			return;
        }
    }
}

bool MermaidTask::isSuccess() {
    for(int i=0; i<mermaidTaskOnlineInfo.mermaidTaskItems.size();i++) {
        if( mermaidTaskOnlineInfo.mermaidTaskItems.at(i).current_num <
                mermaidTaskOnlineInfo.mermaidTaskItems.at(i).goal_num ) {
            return false;
        }
    }
    return true;
}

MermaidTaskConfigInfo MermaidTask::getMermaidTaskConfigInfo() {
    return mermaidTaskConfigInfo;
}

MermaidTaskOnlineInfo MermaidTask::getMermaidTaskOnlineInfo() {
    return mermaidTaskOnlineInfo;
}

bool MermaidTask::isAllowUserSkillById(int skillId) {
    if(skillId == 1 || skillId == 4) {  // 冰冻和核弹不能使用
        return false;
    }
    return true;
}

MermaidTask* MermaidTask::getNewMermaidTask(){
    return new MermaidTask();
}

