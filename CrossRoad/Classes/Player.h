#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Block.h"

USING_NS_CC;
using namespace std;
#define PLAYER_JUMP_OFFSET 17//每次向前跳跃x方向偏移量17

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
private:
	float speedX = 0;
	//void playPlayerHuiTan(std::function<void()> listener);
	void playPlayerTiaoYue();
	//void playPlayerHuiTanLeft(std::function<void()> listener);
	void playPlayerTiaoYueLeft();
	//void playPlayerHuiTanRight(std::function<void()> listener);
	void playPlayerTiaoYueRight();
	//void playPlayerHuiTanBack(std::function<void()> listener);
	void playPlayerTiaoYueBack();
	void update(float dt);
	Node* hero;
	bool intersectsRect(const Rect& rect1,const Rect& rect2);
};