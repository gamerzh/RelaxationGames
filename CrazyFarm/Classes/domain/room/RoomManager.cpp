#include "domain/room/RoomManager.h"
#include "domain/ai/AIManager.h"

RoomManager* RoomManager::_instance = NULL;

RoomManager::RoomManager(){
    this->init();
}

void RoomManager::init(){
    // TODO
}

RoomManager* RoomManager::getInstance(){
    if(_instance == NULL){
        _instance = new RoomManager();
    }
    return _instance;
}

std::vector<RoomPlayer> RoomManager::initRoomConfig(int roomMinTurrentLevel) {
    minTurrentLevel = roomMinTurrentLevel;
    int userPosition = rand()%2;
    roomPlayers.clear();
    
    for(int i=0;i<4;i++) {
        if(i != userPosition) {
            RoomPlayer player ;
            player.setMaxTurretLevel(getInitMaxTurrentLevelByMinTurrentLevel(minTurrentLevel));
            
            player.setCoins(getInitCoinsByMinTurrentLevel(player.getMaxTurretLevel()));
            player.setDiamonds(getInitDiamondsByMinTurrentLevel(player.getMaxTurretLevel()));
            player.setLevel(getInitPlayerLevelByMinTurrentLevel(player.getMaxTurretLevel()));
            player.setPlayerState(RoomPlayer::PLAYERSTATE_NEW);
        
            AI* ai = AIManager::getInstance()->getAI( player.getMaxTurretLevel() );
            player.setAi(ai);
            
            player.setUserName("player_n_20120");   // TODO :
            

            roomPlayers.push_back(player);
        }
        
    }
    return roomPlayers;
}

int RoomManager::getInitMaxTurrentLevelByMinTurrentLevel(int roomMinLevel) {
    int random = rand()%100;
    if(roomMinLevel <= 1) {
        if(random < 60) {
            return 1 + rand()%10;
        }else if(random < 90){
            return 15 + (rand()%4)*5;
        }else {
            return 15 + (rand()%7)*5;
        }
    }else if(roomMinLevel <= 30) {
        if(random < 40){
            return 30 + (rand()%4)*5;
        }else if(random < 95){
            return 50 + (rand()%5)*10;
        }else {
            return 100 +(rand()%3)*50;
        }
    }else  if(roomMinLevel <= 100) {
        if(random < 95){
            return 100 +(rand()%9)*50;
        }else {
            return 500 +(rand()%3)*100;
        }
    }else {
        if(random < 98) {
            return 500 + (rand()%5)*100;
        }else {
            return 1000;
        }
        
    }
}

int RoomManager::getInitCoinsByMinTurrentLevel(int maxLevel) {
    if(maxLevel <= 30) {
        return 10000 + rand()%490000;   // [1W, 50W]
    }else if(maxLevel <= 300) {
        return 80000 + rand()%1420000;   //[8W, 150W]
    }else {
        return 500000 + rand()%9500000;   //[50w, 1000W]
    }
}

int RoomManager::getInitDiamondsByMinTurrentLevel(int maxLevel) {
    if(maxLevel <= 30) {
        return 2 + rand()%98;   //
    }else if(maxLevel <= 300) {
        return 50 + rand()%450;   //
    }else {
        return 50 + rand()%2500;   //
    }
}



int RoomManager::getInitPlayerLevelByMinTurrentLevel(int maxLevel) {
    if(maxLevel <= 30) {
        return 0 + rand()%20;
    }else if(maxLevel <= 300) {
        return 1 + rand()%40;
    }else {
        return 5 + rand()%100;
    }
}

std::vector<RoomPlayer> RoomManager::updateRoomConfig() {
    // TODO : wait impl player coming/outing room
//    int j = 0;
//    for(int i=0;i<4;i++) {
//        if(i != userPosition) {
//            int needUpdate = rand()%100;
//            if(roomPlayers.at(j).getPlayerState() == RoomPlayer::PLAYERSTATE_STANDUP) {
//                if(needUpdate < 40) {
//                    roomPlayers.at(j).setCoins(200);
//                    roomPlayers.at(j).setDiamonds(0);
//                    roomPlayers.at(j).setLevel(2);
//                    roomPlayers.at(j).setPlayerState(RoomPlayer::PLAYERSTATE_NEW);
//                    roomPlayers.at(j).setRoomPosition(i);
//                    roomPlayers.at(j).setMaxTurretLevel(i+1);
//                    roomPlayers.at(j).setUserName("player_u_40140");
//                }
//            }else {
//                if(needUpdate < 10) {
//                    roomPlayers.at(j).setCoins(200);
//                    roomPlayers.at(j).setDiamonds(0);
//                    roomPlayers.at(j).setLevel(2);
//                    roomPlayers.at(j).setPlayerState(RoomPlayer::PLAYERSTATE_STANDUP);
//                    roomPlayers.at(j).setRoomPosition(i);
//                    roomPlayers.at(j).setMaxTurretLevel(i+1);
//                    roomPlayers.at(j).setUserName("player_u_40140");
//                }else {
//                    roomPlayers.at(j).setPlayerState(RoomPlayer::PLAYERSTATE_KEEP);
//                }
//            }
//            j++;
//        }
//    }
    return roomPlayers;
}



