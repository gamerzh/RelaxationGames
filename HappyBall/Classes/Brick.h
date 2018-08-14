#pragma once
#include "cocos2d.h"
#include "GeometryTools.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define AREA_OFFSET_FRAME 4 //�����ж���ʱ����ʼ�����ƫ����,�յ��ȥƫ����

struct AreaFrameRange
{
	int startFrame;
	int endFrame;
};



class Brick : public cocos2d::Sprite {
public:
	static Brick* create(int frame = 0,int level = 0);
	virtual bool init(int frame = 0, int level = 0);
	void setFrameIndex(int current);
	int getFrameIndex();
	void updateBrickShape(int level);
	void createSafeShape();
	void removeDangousArea();
	void setBrickColor(cocos2d::Color3B col);
	void brickOpacity(float op);
	std::vector<AreaFrameRange> getOutAnglesByFrameIndex();//��ȡ����������֡
	std::vector<AreaFrameRange> getDangousAnglesByFrameIndex();//��ȡΣ�������֡
	bool isCheck = false;
	bool isAbandon = false;
	float brickopacity = 255;
private:
	cocos2d::Node* part1 = nullptr;
	cocos2d::Node* part2_a = nullptr;
	cocos2d::Node* part2_b = nullptr;
	cocos2d::Node* part3_a = nullptr;
	cocos2d::Node* part3_b = nullptr;
	cocos2d::Node* part4_a = nullptr;
	cocos2d::Node* part4_b = nullptr;
	cocos2d::Node* part5_a = nullptr;
	cocos2d::Node* part5_b = nullptr;
	cocos2d::Node* part6_a = nullptr;
	cocos2d::Node* part6_b = nullptr;
	cocos2d::Node* part7_a = nullptr;
	cocos2d::Node* part7_b = nullptr;
	cocos2d::Node* part8_a = nullptr;
	cocos2d::Node* part8_b = nullptr;

	std::vector<AreaFrameRange> outList;
	std::vector<AreaFrameRange> danList;
	std::vector<int> outArea;
	std::vector<int> danArea;
	cocostudio::timeline::ActionTimeline* heroTimeLine;
	AreaFrameRange getFrameByModuleId(int index);
	int randomAreaModule(std::vector<int>& origin);
	void controlModule(int id,int type);
	void loadBrickFile();
	void createOutAnglesFrame();
	void createDanAnglesFrame();
	void update(float dt);
	void brickDebug();
};