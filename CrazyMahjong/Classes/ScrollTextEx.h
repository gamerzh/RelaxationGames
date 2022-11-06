#pragma once
#include "cocos2d.h"

USING_NS_CC;
class ScrollTextEx : public cocos2d::Node {
public:
	
	CREATE_FUNC(ScrollTextEx);
	CC_CONSTRUCTOR_ACCESS:
	ScrollTextEx();
	virtual ~ScrollTextEx();
	virtual bool init();
	virtual bool initWithDatas(cocos2d::Sprite* pMask,
		cocos2d::Label* pMoveChild);
	bool initClipper(cocos2d::Sprite* pMask, cocos2d::Label* pMoveChild);
	void update(float delta);
	void setpMaskString(std::string string);
	long getCurrentTime();
public:
	 void setScrollStrs(std::vector<std::string> strs);
	 void setScrollStr(std::string str);
	 void setAutoScroll(bool isScroll, bool byWidth = false);
private:
	cocos2d::Label* _mLable;
	cocos2d::Sprite* pMask;
	cocos2d::Vector<Node*> _mNodes;
	bool _autoScroll;



	std::list<std::string> m_strs;
};
