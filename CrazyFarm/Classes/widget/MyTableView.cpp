#include "MyTableView.h"

MyTableView* MyTableView::create(TableViewDataSource* dataSource, CCSize size)
{
	MyTableView * tableView = new MyTableView;
	tableView->initWithViewSize(size, nullptr);
	tableView->autorelease();
	tableView->setDataSource(dataSource);
	tableView->_updateCellPositions();
	tableView->_updateContentSize();
	return tableView;
}



void MyTableView::onTouchEnded(Touch *pTouch, Event *pEvent){
	mLastEnd = pTouch->getLocation();
	TableView::onTouchEnded(pTouch, pEvent);
}