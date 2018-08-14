#pragma once
#include "cocos2d.h"
#include "Brick.h"
#include "Hero.h"
#include "Pillar.h"

#define BRICK_HEIGHT  240
#define BRICK_ANIM_NUM 120
#define BRICK_START_ZORDER  5000
#define BRICK_INIT_NUMBER 10 //��ʼ���Ľڵ�����
#define BALL_STAY_POS_Y 880 //С��ͣ����Y������
#define ZHU_ZI_POS_Y 1150//���ӵ�Y������
#define SOUND_MENU_TAG 1000
#define PAUSE_MENU_TAG 1001
#define PAS_NODE_NUM 4
#define EVERY_FRAME_DISTANCE 16//ÿ��ˢ���ƶ�����

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void addTouchListener();
	void resumeGame();
	void showGameOver();
	void updateHeroSkin();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event  *event) override;
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event  *event) override;
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event  *event) override;
private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	std::vector<Brick*> brickVector;//ש��
	std::vector<Brick*> passVector;
	cocos2d::Vec2 preTouchPosition;
	Hero* hero = nullptr;
	Pillar* pillar = nullptr;
	float offset_y = 0;
	float path_record = 0;
	float mysteryTime = 20;
	float invincibleTime = 5;
	int create_brick_num = 0;
	int passCount = 0;
	float pauseTime = 0;
	bool allowCheck = true;
	void addHeroToGame();
	void showPlusScore(int plus);
	void addBrick(int num = 1);
	void recycleBrick();
	void update(float dt);
};