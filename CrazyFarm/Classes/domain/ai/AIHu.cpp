#include "domain/ai/AIHu.h"
#include "domain/ai/AIManager.h"
#include "bullet/BulletManage.h"
PlayerWork AIHu::nextStep(int currentCoins, Point currentPostion) {


	PlayerWork playerWork;

	playerWork.setTurrentLevel(this->getMaxTurrentLevel());

	if (!AIManager::getInstance()->allowAiFire()) {
		playerWork.setAngle((float)angle);
		playerWork.setFire(false);
		return playerWork;
	}

	if (FishManage::getInstance()->getAllFishInPoolCount() < 2|| FishManage::getInstance()->getAllFishInPoolCount() > 1111 || BulletManage::getInstance()->getBulletPoolSize() > 20) {
		playerWork.setAngle((float)angle);
		playerWork.setFire(false);
		return playerWork;
	}
    
	angle = 60 - rand() % 120;

	playerWork.setAngle((float)angle);
	playerWork.setFire(true);
	return playerWork;

    int fire = rand()%10;
    
    if(fire < 6) { // TODO : just test value
        angle = 60 - rand()%120;
        
        playerWork.setAngle((float)angle);
        if(fire < 3) {
            playerWork.setFire(true);
        }else {
            playerWork.setFire(false);
        }
        return playerWork;
    }else {
        playerWork.setFire(false);
        playerWork.setAngle(angle);
        return playerWork;
    }
    
    
    
}