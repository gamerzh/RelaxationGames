#include "RanklistPanel.h"
#include "RanklistManager.h"
#include "RanklistCell.h"
bool RanklistPanel::init()
{
	if (!Sprite::initWithFile("rankListBg.png"))
	{
		return false;
	}
	// Create the list view ex
	ListView* listView = ListView::create();
	// set list view ex direction
	listView->setDirection(ui::ScrollView::Direction::VERTICAL);
	listView->setTouchEnabled(true);
	listView->setItemsMargin(-5);
	listView->setBounceEnabled(true);
	listView->setContentSize(Size(188,205));
	listView->setPosition(Vec2(10,47));
	listView->setAnchorPoint(Point::ZERO);
	listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(RanklistPanel::selectedItemEvent, this));
	addChild(listView);

	auto items = RanklistManager::getInstance()->getCoinRankListData();
	for (int i = 0; i < items.size();i++)
	{
		auto cell = RanklistCell::create(items.at(i), i + 1);
		Layout* custom_item = Layout::create();
		cell->setPosition(0,0);
		cell->setAnchorPoint(Point::ZERO);
		custom_item->addChild(cell);
		custom_item->setContentSize(cell->getContentSize());

		listView->pushBackCustomItem(custom_item);
	}
	return true;
}

void RanklistPanel::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
	{
		ListView* listView = static_cast<ListView*>(pSender);
		CC_UNUSED_PARAM(listView);
		CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
		break;
	}
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
	{
		ListView* listView = static_cast<ListView*>(pSender);
		CC_UNUSED_PARAM(listView);
		CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
		break;
	}
	default:
		break;
	}
}