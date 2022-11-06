#include "ScrollText.h"
#include "domain/marquee/MarqueeManager.h"


USING_NS_CC;
#define IF_RETURN(cont,p) if ((cont)){return (p);}
#define IF_RETURN_FALSE(cont) IF_RETURN(cont,false)
bool ScrollText::init() {
	bool ret = true;
	if (Node::init()) {
		pMask = Sprite::create("hot_marquee_bg1.png");
		marInfo = "";
		ishowDialog = false;
		auto vec = MarqueeManager::getInstance()->getContents();
		std::string str1;
		for (auto var:vec)
		{
			str1 += "            " + var;
		}
		_mLable = Label::create(str1.c_str() , "Arial-BoldMT", 16);
		_mLable->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_mLable->setColor(Color3B::YELLOW);
		IF_RETURN_FALSE(!initClipper(pMask, _mLable));
		setAutoScroll(true);
		scheduleUpdate();
		return ret;
	}
	return ret;
}

void ScrollText::setpMaskString(std::string string) {
	_mLable = Label::create(string, "Arial-BoldMT", 16);
}

bool ScrollText::initClipper(cocos2d::Sprite* pMask,
		cocos2d::Label* pMoveChild) {
	auto clipper = ClippingNode::create();
	IF_RETURN_FALSE(!clipper);
	IF_RETURN_FALSE(!pMask);
	setContentSize(Size(pMask->getContentSize().width,pMask->getContentSize().height));
	IF_RETURN_FALSE(!pMask->getTexture());
	auto _clipperStencil = Sprite::createWithTexture(pMask->getTexture());
	IF_RETURN_FALSE(!_clipperStencil);
	_clipperStencil->retain();
	clipper->setAlphaThreshold(0.1f);
	clipper->setStencil(_clipperStencil);
	clipper->addChild(pMask);
	clipper->addChild(pMoveChild, 1);
	addChild(clipper);

	for (auto child : _mNodes) {
		IF_RETURN_FALSE(!child);
		clipper->addChild(child);
	}
	this->setContentSize(pMask->getContentSize());
	return true;
}

ScrollText::ScrollText() :
_autoScroll(false) {
}

ScrollText::~ScrollText() {
	//	CC_SAFE_RELEASE(_mLable);
}


void ScrollText::update(float delta) {
	if (!_mLable) {
		return;
	}
	float currentX = _mLable->getPositionX();
	float contentX = getContentSize().width * (-1.0f);
	float lableX = _mLable->getContentSize().width * (-1.0f);
	if (_autoScroll) {
		if (_mLable->getPositionX() >= (lableX + contentX / 2+ 60))
			_mLable->setPositionX(_mLable->getPositionX() - 0.25f);
		else {
			_mLable->setPositionX(-contentX / 2 );
		}

	} else {
		_mLable->setPositionX(contentX / 2);
	}
}

void ScrollText::setAutoScroll(bool isScroll, bool byWidth/*=false*/) {
	if (!byWidth) {
		_autoScroll = isScroll;
	} else {
		_autoScroll =
				_mLable->getContentSize().width > getContentSize().width ?
						true : false;
	}
}
bool ScrollText::initWithDatas(cocos2d::Sprite* pMask,
		cocos2d::Label* pMoveChild) {
	bool ret = false;
	if (Node::init()) {
		IF_RETURN_FALSE(!pMask);
		_mLable = pMoveChild;
		_mLable->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		initClipper(pMask, _mLable);
		scheduleUpdate();
		return true;
	}
	return ret;
}


long ScrollText::getCurrentTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

