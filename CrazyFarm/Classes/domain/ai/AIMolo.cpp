#include "domain/ai/AIMolo.h"
#include "domain/ai/AIManager.h"

PlayerWork AIMolo::nextStep(int currentCoins, Point currentPostion) {
    PlayerWork playerWork;
//    int turrentLevel = rand()%this->getMaxTurrentLevel();
//    playerWork.setTurrentLevel(turrentLevel);
    
    if(! AIManager::getInstance()->allowAiFire()) {
        playerWork.setAngle((float)angle);
        playerWork.setFire(false);
        lastFire = false;
        return playerWork;
    }
	bool k = FishManage::getInstance()->getAllFishInPoolCount() < 5;
	bool k1 = FishManage::getInstance()->getAllFishInPoolCount() > 1111;
	bool k2 = BulletManage::getInstance()->getBulletPoolSize() > 20;
	if ( k||k1||k2 ) {
        playerWork.setAngle((float)angle);
        playerWork.setFire(false);
        lastFire = false;
        return playerWork;
    }
    
    if(count == 0) {
        nextCountReset = 60 + rand()%100;
        fireLevel = baseFireLevel + rand()%10;
    }
    
    if( count > nextCountReset && count < nextCountReset + 10 ) {
        playerWork.setAngle((float)angle);
        playerWork.setFire(false);
        lastFire = false;
        return playerWork;
    }
    
    if( count >  nextCountReset + 10 ) {
        count = 0;
    }
    
    playerWork.setTurrentLevel(this->getMaxTurrentLevel());
    
    int fire = rand()%100;
    
    int currentFireLevel = fireLevel;
    if(lastFire) {
        currentFireLevel = fireLevel+30;
    }
    
    if(fire < currentFireLevel) {
		angle = CC_RADIANS_TO_DEGREES(currentPostion.getAngle(FishManage::getInstance()->getBestRewardPostion()));
        playerWork.setAngle((float)angle);
        playerWork.setFire(true);
        lastFire = true;
        return playerWork;
    }else {
        playerWork.setFire(false);
        lastFire = false;
        
        int turn = rand()%100;
        if(turn < 20) {
            angle = 60 - rand()%120;
            playerWork.setAngle((float)angle);
        }else {
            playerWork.setAngle(angle);
        }
    }
    
    count++;
    return playerWork;
    
}