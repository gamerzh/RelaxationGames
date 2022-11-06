#include "domain/magnate/MagnateManager.h"

MagnateManager* MagnateManager::_instance = NULL;

MagnateManager::MagnateManager(){
    this->init();
}


void MagnateManager::init(){
    diamandConfig = ConfigMagnate::getInstance()->getDiamandMagnate();
    itemConfig = ConfigMagnate::getInstance()->getItemMagnate();
}

MagnateManager* MagnateManager::getInstance(){
    if(_instance == NULL){
        _instance = new MagnateManager();
    }
    return _instance;
}


MagnateEvent MagnateManager::getDiamandMagnateEvent(){
    MagnateEvent magnateEvent;
	magnateEvent.fireTimes =  diamandConfig.fire_time_from +
		rand() % (diamandConfig.fire_time_to - diamandConfig.fire_time_from);
    magnateEvent.itemId = 1002;
    magnateEvent.num = 1;
    return magnateEvent;
}

MagnateEvent MagnateManager::getItemMagnateEvent(){
    MagnateEvent magnateEvent;
    magnateEvent.fireTimes = itemConfig.fire_time_from +
    rand()%(itemConfig.fire_time_to - itemConfig.fire_time_from);
    int random = rand()%20;
    if(random < 6) {
        magnateEvent.itemId = 1003;
    }else if(random < 16) {
        magnateEvent.itemId = 1004;
    }else {
        magnateEvent.itemId = 1005;
    }
    magnateEvent.num = 1;
    return magnateEvent;
}