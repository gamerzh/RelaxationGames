#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Block.h"

USING_NS_CC;
using namespace std;
#define PLAYER_JUMP_OFFSET 17//每次向前跳跃x方向偏移量17
#define  PLAYER_OFFSET_Y  0 //玩家在一个单元格里的偏移量

//玩家类,支持多种皮肤和特性
class Player : public cocos2d::Sprite {
public:
	CREATE_FUNC(Player);
	virtual bool init();
	//玩家操作
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
	void setSpeedX(float speed);//获得一个X方向上的速度
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