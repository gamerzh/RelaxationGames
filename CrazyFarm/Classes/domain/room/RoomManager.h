#ifndef _ROOMMANAGER_H_
#define _ROOMMANAGER_H_
#include "cocos2d.h"
#include "domain/room/RoomPlayer.h"

using namespace cocos2d;

class RoomManager{
public:
	static RoomManager* getInstance();
    
    std::vector<RoomPlayer> initRoomConfig(int roomMinTurrentLevel);
    std::vector<RoomPlayer> updateRoomConfig();

private:
	RoomManager();
	void init();
	static RoomManager* _instance;

    /**
     * task
     */
    void working();
    
    std::vector<RoomPlayer> roomPlayers;
    int userPosition = 0;
    int minTurrentLevel = 1;
    
    int getInitMaxTurrentLevelByMinTurrentLevel(int roomMinLevel);
    
    int getInitCoinsByMinTurrentLevel(int maxLevel);
    int getInitDiamondsByMinTurrentLevel(int maxLevel);
    int getInitPlayerLevelByMinTurrentLevel(int maxLevel);
    
    
    
};

#endif
