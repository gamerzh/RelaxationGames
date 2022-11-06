#ifndef __ROOM_H__
#define __ROOM_H__
#include "cocos2d.h"

USING_NS_CC;

enum ROOM
{	
	ROOM_NULL = -1,
	ROOM_CHUJI = 0,
	ROOM_ZHONGJI = 1,
	ROOM_GAOJI = 2,
	ROOM_QINGYISE = 3,
};

class Room
{

public:
	Room();
	static Room* getInstance()
	{
		if (nullptr == instance)
		{
			instance = new Room;
		}
		return instance;
	}
	void init();
	void destory();
	//int updateRoomScore();	// 根据主角金币，更新底分
	int addFreeCoins();			// 四个玩家金币不够１０００，　增加金币

	int getRoomScoreByMyCoin(); // 得到当前我的分数匹配的底分
	int getRoomScore();			// 得到当前所在房间底分
	int getRoomMinScore(int roomid);		//得到房间最低进入分数
	int getRoomNextScore();		//得到房间最低进入分数
	
	int getCoins(int id);			// 得到某个玩家的硬币
	std::string getName(int dir);			// 得到某个玩家的姓名
	
	void setRoomTimes(int dir, int newTimes);	// 设置玩家倍数
	int getRoomTimes(int dir);			// 得到玩家倍数

	int getPlayerHead(int dir);  //获取玩家头像
	bool isVip(int dir); ///获取是否VIP
	void setRoomType(ROOM _roomID){ roomID = _roomID; };       //设置初级房OR中级房OR高级房
	ROOM getRoomType(){ return roomID; };
	// updateCoins(0, -1000) 给玩家１的数据，减少１０００个硬币
	void updateCoins(int id, int newCoins);	// 更新某个玩家的硬币


	bool isGainAlms = false;
private:
	static Room* instance;
	int roomScore[4];			// 四个房间的底分
	int roomMinScore[4];			// 四个房间的底分
	int coins[4];			// 
	ROOM roomID = ROOM_NULL;// 当前房间号


	std::vector<std::string> playerNames;
	std::map<int, int>  map_dirToTimes;
	std::map<int, int>  map_dirToHead;
	int times;						// 倍数
};

#endif