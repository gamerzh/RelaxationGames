#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "lobby/viplayer/VipCell.h"
#include "widget/BaseLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;



class VIPView :public TableViewDelegate
	, public TableViewDataSource
{
public:
	virtual void scrollViewDidScroll(ScrollView* view) {}
	virtual void scrollViewDidZoom(ScrollView* view){}
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t  idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
private:


};














class VIPLayer : public BaseLayer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	CREATE_FUNC(VIPLayer);

private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void chankanCallBack(Ref*);
	VIPView* tableviewDelegate;
};
