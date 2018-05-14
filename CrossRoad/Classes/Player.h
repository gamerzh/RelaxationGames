#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Block.h"

USING_NS_CC;
using namespace std;
#define PLAYER_JUMP_OFFSET 17//ÿ����ǰ��Ծx����ƫ����17
#define  PLAYER_OFFSET_Y  0 //�����һ����Ԫ�����ƫ����

//�����,֧�ֶ���Ƥ��������
class Player : public cocos2d::Sprite {
public:
	CREATE_FUNC(Player);
	virtual bool init();
	//��Ҳ���
	bool playerJumpForward(vector<Block*> blocks,int mapIndex);
	bool playerJumpBackwards(vector<Block*> blocks, int mapIndex);
	bool playerJumpLeft(vector<Block*> blocks, int mapIndex);
	bool playerJumpRight(vector<Block*> blocks, int mapIndex);
	void playPlayerJiYa();
	void playPlayerJiYaLeft();
	void playPlayerJiYaRight();
	void playPlayerJiYaBack();
	Point getPlayerPoint();
	Rect getPlayerCheckRect();
	void setSpeedX(float speed);//���һ��X�����ϵ��ٶ�
	float getSpeedX();
	void playerGoDie();
private:
	float speedX = 0;
	void playPlayerTiaoYue();
	void playPlayerTiaoYueLeft();
	void playPlayerTiaoYueRight();
	void playPlayerTiaoYueBack();
	void update(float dt);
	Node* hero;

};