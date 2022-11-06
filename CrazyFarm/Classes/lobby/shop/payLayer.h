#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "payCell.h"
#include "widget/BaseLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

class payTableViewCell : public TableViewCell
{
public:
	CREATE_FUNC(payTableViewCell);
	virtual bool init();
	void setCoinValue(int idx);
	void setDiamondValue(int idx);
private:
	PayCell* cell0;
	PayCell* cell1;
	PayCell* cell2;
};


class payView :public TableViewDelegate
	, public TableViewDataSource
{
public:
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {}
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view){}
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t  idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);



private:
	CC_SYNTHESIZE(int, m_shopType, ShopType);////1金币2钻石
	CC_SYNTHESIZE(int, m_payeventPoint, EventPoint);//事件点


	//按键保护
	unsigned long lastTouchTime = 0;
	bool isAllowTouch = false;
public:
	void setLastTouchTiem();
	void TouchHelpUpdata();
	bool getIsAllowTouch(){ return isAllowTouch; };

};













class payLayer : public BaseLayer
{
public:
	//1 金币 2钻石
	static payLayer * createLayer(int payType);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void setEventPont(int eventPoitn){ tableviewDelegate->setEventPoint(eventPoitn); };
	payView* tableviewDelegate;
private:
	void update(float delta);
	
	virtual bool init(int payType);
	void closeButtonCallBack(Ref*psend);
	LabelTTF*ttf;

	void showVipCallback(Ref*psend);
};
