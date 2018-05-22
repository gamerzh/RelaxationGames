#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Block.h"

USING_NS_CC;
using namespace std;
#define PLAYER_JUMP_OFFSET 17//每次向前跳跃x方向偏移量17
#define  PLAYER_OFFSET_Y  0 //玩家在一个单元格里的偏移量

enum PlayerMod
{
	mode_1,
	mode_2,
	mode_3,
	mode_4
};

//玩家类,支持多种皮肤和特性
class Player : public cocos2d::Sprite {
public:
	CREATE_FUNC(Player);
	virtual bool init();
	//玩家操作
	bool playerJumpForward(vector<Block*> blocks);
	bool playerJumpBackwards(vector<Block*> blocks);
	bool playerJumpLeft(vector<Block*> blocks);
	bool playerJumpRight(vector<Block*> blocks);
	void playPlayerJiYa();
	void playPlayerJiYaLeft();
	void playPlayerJiYaRight();
	void playPlayerJiYaBack();
	Point getPlayerPoint();
	Rect getPlayerCheckRect();
	void setSpeedX(float speed);//获得一个X方向上的速度
	float getSpeedX();
	void playerGoDie();
	void playerGoWater();
	void playerResurgence();
	CC_SYNTHESIZE(bool, playerOnWood, PlayerOnWood);
	CC_SYNTHESIZE(bool, resurgence, Resurgence);
private:
	float offset_path = 0;
	float speedX = 0;
	void playPlayerTiaoYue();
	void playPlayerTiaoYueLeft();
	void playPlayerTiaoYueRight();
	void playPlayerTiaoYueBack();
	void update(float dt);
	Node* hero;

};