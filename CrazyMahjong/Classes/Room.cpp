#include "Room.h"
#include "PxPayMannger.h"
#include "User.h"
#include "NameMannger.h"
Room* Room::instance = nullptr;

Room::Room()
{
	roomScore[0] = 100;	// 低分
	roomScore[1] = 500;
	roomScore[2] = 1000;
	roomScore[3] = 1000;

	roomMinScore[0] = 2000;
	roomMinScore[1] = 300000;
	roomMinScore[2] = 1000000;
	roomMinScore[3] = 2000;
}
void Room::init()
{
	map_dirToHead.clear();


	coins[0] = 0;
	coins[1] = 0;
	coins[2] = 0;
	coins[3] = 0;

	
	for (int i = 0; i < 4; i++)
	{
		map_dirToTimes[i] = 1;
	}

	playerNames.clear();
	playerNames.push_back(User::getInstance()->getMyName());
	playerNames.push_back(NameMannger::getName());
	playerNames.push_back(NameMannger::getName());
	playerNames.push_back(NameMannger::getName());
}
void Room::destory()
{
	
	CC_SAFE_DELETE(instance);
	instance = nullptr;
}
int Room::getRoomScore()
{
	if (roomID != ROOM_QINGYISE)
	{
		return roomScore[roomID];
	}
	else
	{
		auto user = User::getInstance();
		int myCoin = user->getMyCoins();
		int room = 0;
		if (300000 > myCoin)
		{
			room = 0;
		}
		else if (300000 <= myCoin && myCoin < 1000000)
		{
			room = 1;
		}
		else if (1000000 <= myCoin)
		{
			room = 2;
		}
		return roomScore[room];
	}
}
// 根据硬币数，更新房间号
//int Room::updateRoomScore()
//{
//	auto user = User::getInstance();
//	int myCoin = user->getMyCoins();
//	if (1000 >myCoin)
//	{
//		user->setMyCoins(1000);
//		isGainAlms = true;
//		roomID = ROOM_1;
//	}
//	else if (1000 <= myCoin && myCoin <8000)
//	{
//		roomID = ROOM_1;
//	}
//	else if (8000 <= myCoin && 16000 >= myCoin)
//	{
//		roomID = ROOM_2;
//	}
//	else if (16000 <= myCoin && 40000 >= myCoin)
//	{
//		roomID = ROOM_3;
//	}
//	else if (40000 <= myCoin)
//	{
//		roomID = ROOM_4;
//	}
//	return roomScore[roomID];
//}
std::string Room::getName(int dir)
{
	return playerNames.at(dir);
}



int Room::getRoomMinScore(int roomid)
{
	return roomMinScore[roomid];
}
int Room::getRoomNextScore()
{
	int id = roomID + 1;
	if (id>3)
	{
		id = 3;
	}
	return roomMinScore[id];
}
// 给电脑增加硬币
int Room::addFreeCoins()
{
	for (int index = 1; index < 4; index++)
	{
		/*if (1000 > coins[index])
		{*/
		coins[index] += getRoomScore()*(30 + rand() % 50) + getRoomMinScore(getRoomType());
	/*	}*/
	}
	return 0;
}

int Room::getCoins(int id)
{
	if (id==0)
	{
		return User::getInstance()->getMyCoins();
	}
	return coins[id];
}

void Room::setRoomTimes(int dir,int newTimes)
{
	map_dirToTimes[dir] = newTimes;
}

int Room::getRoomTimes(int dir)
{
	return map_dirToTimes[dir];
}

void Room::updateCoins(int id, int newCoins)
{
	if (id==0)
	{
		auto user = User::getInstance();
		user->addCoin(newCoins);
		return;
	}
	coins[id] += newCoins;
}

int Room::getPlayerHead(int dir)
{
	if (map_dirToHead.size() == 0)
	{
		map_dirToHead[0] = User::getInstance()->getroleNowIndex();
		for (int i = 1; i < 4;i++)
		{
			map_dirToHead[i] = rand() % 12 + 1;
		}
	}
	return map_dirToHead[dir];

}

bool Room::isVip(int dir)
{
	if (dir == 0)
	{
		auto user = User::getInstance();
		return user->getisVip();
	}
	else
	{
		return rand() % 2;
	}
}