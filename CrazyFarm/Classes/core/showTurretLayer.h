#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "core/showTurretCell.h"

USING_NS_CC;
USING_NS_CC_EXT;



class showTurretView :public TableViewDelegate
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
	CC_SYNTHESIZE(int, nViewTp, viewTp);
	CC_SYNTHESIZE(std::vector<int>, m_viewData,viewData);

};














class showTurretLayer : public cocos2d::Layer
{
public:
    virtual bool init(int type); //type:1 vipÅÚ  type:2 ±¶ÊýÅÚ

	static  showTurretLayer*create(int type);

private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void chankanCallBack(Ref*);
	showTurretView* tableviewDelegate;
	int m_type;
	CC_SYNTHESIZE(int, m_btType, btType);
};
