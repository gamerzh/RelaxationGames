#ifndef _SCROLLTEXT_H_
#define _SCROLLTEXT_H_
#include "cocos2d.h"

USING_NS_CC;
class ScrollText: public cocos2d::Node {
public:
	void setAutoScroll(bool isScroll, bool byWidth = false);
	CREATE_FUNC(ScrollText);
	CC_CONSTRUCTOR_ACCESS:
	ScrollText();
	virtual ~ScrollText();
	virtual bool init();
	virtual bool initWithDatas(cocos2d::Sprite* pMask,
		cocos2d::Label* pMoveChild);
	bool initClipper(cocos2d::Sprite* pMask, cocos2d::Label* pMoveChild);
	void update(float delta);
	void setpMaskString(std::string string);
	long getCurrentTime();

private:
	cocos2d::Label* _mLable;
	cocos2d::Sprite* pMask;
	cocos2d::Vector<Node*> _mNodes;
	bool _autoScroll;
	std::string marInfo;
	bool ishowDialog;
};
#endif
