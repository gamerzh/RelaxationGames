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
	//int updateRoomScore();	// �������ǽ�ң����µ׷�
	int addFreeCoins();			// �ĸ���ҽ�Ҳ������������������ӽ��

	int getRoomScoreByMyCoin(); // �õ���ǰ�ҵķ���ƥ��ĵ׷�
	int getRoomScore();			// �õ���ǰ���ڷ���׷�
	int getRoomMinScore(int roomid);		//�õ�������ͽ������
	int getRoomNextScore();		//�õ�������ͽ������
	
	int getCoins(int id);			// �õ�ĳ����ҵ�Ӳ��
	std::string getName(int dir);			// �õ�ĳ����ҵ�����
	
	void setRoomTimes(int dir, int newTimes);	// ������ұ���
	int getRoomTimes(int dir);			// �õ���ұ���

	int getPlayerHead(int dir);  //��ȡ���ͷ��
	bool isVip(int dir); ///��ȡ�Ƿ�VIP
	void setRoomType(ROOM _roomID){ roomID = _roomID; };       //���ó�����OR�м���OR�߼���
	ROOM getRoomType(){ return roomID; };
	// updateCoins(0, -1000) ����ң������ݣ����٣���������Ӳ��
	void updateCoins(int id, int newCoins);	// ����ĳ����ҵ�Ӳ��


	bool isGainAlms = false;
private:
	static Room* instance;
	int roomScore[4];			// �ĸ�����ĵ׷�
	int roomMinScore[4];			// �ĸ�����ĵ׷�
	int coins[4];			// 
	ROOM roomID = ROOM_NULL;// ��ǰ�����


	std::vector<std::string> playerNames;
	std::map<int, int>  map_dirToTimes;
	std::map<int, int>  map_dirToHead;
	int times;						// ����
};

#endif