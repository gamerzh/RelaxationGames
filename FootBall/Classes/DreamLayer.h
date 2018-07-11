#pragma once
#include "cocos2d.h"

class DreamLayer : public cocos2d::Layer {
public:
	static DreamLayer* create(int dreamId);
	virtual bool init(int dreamId);
private:
	void loadContent(int id);
	void loadSecondContent(int id);//二次的界面
	std::string getFileNameById(int id);
	void closeView(Ref* ref);
	void doConfirmEvent(Ref* ref);
	void doSecondConfirmEvent(Ref* ref);
	void closeSecondView(Ref* ref);
};