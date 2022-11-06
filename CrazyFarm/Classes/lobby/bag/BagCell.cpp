#include "BagCell.h"
#include "ShowBoxLayer.h"
#include "domain/user/User.h"
#include "ShowSkillLayer.h"
#include "ShowGiftLayer.h"
bool BagCell::init(){
	if (!Sprite::initWithFile("bagbox.png")){
		return false;
	}
	auto size = getContentSize();
	propSprite = Sprite::create();
	propSprite->setPosition(size / 2);
	addChild(propSprite);

	propNum = LabelAtlas::create("0", "bagPropNum.png", 18, 26, '0');
	propNum->setAnchorPoint(Point(1,0));
	propNum->setPosition(size.width*0.65+27, size.height*0.1);
	addChild(propNum);
	propNum->setVisible(false);
	
	txtji = Sprite::create("txtLevel.png");
	txtji->setAnchorPoint(Point(1,0));
	txtji->setPosition(size.width*0.65 + 27, size.height*0.1);
	addChild(txtji);
	txtji->setVisible(false);

	txt = Sprite::create("dianjigoumaitxt.png");
	txt->setPosition(size.width / 2, 21);
	txt->setVisible(false);
	addChild(txt);
	
	BagItem item;
	item.itemId = -1;
	setbagitem(item);
	return true;
}

void BagCell::setValue(BagItem item)
{
	if (item.itemId==-1)
	{
		propSprite->setVisible(false);
		propNum->setVisible(false);
		return;
	}
	setbagitem(item);
	auto spPath = String::createWithFormat("item_%d.png", item.itemId);
	propSprite->setTexture(spPath->getCString());
	switch (item.type)
	{
	case Prop_Skill:
		txtji->setVisible(false);
		if (item.num==0)
		{
			txt->setVisible(true);
			propNum->setVisible(false);

		}
		else
		{
			txt->setVisible(false);
			propNum->setVisible(true);
			propNum->setString(Value(item.num).asString().c_str());

		}
		break;
	case Prop_ItemBox:
		txtji->setVisible(false);
		txt->setVisible(false);
		propNum->setVisible(true);
		propNum->setString(Value(item.num).asString().c_str());

		break;
	case Prop_upgradeBox:
		txtji->setVisible(true);
		txt->setVisible(false);
		propNum->setVisible(true);
		propNum->setPositionX(65 + 6);
		propNum->setString(Value(User::getInstance()->getLevelData().levelId+1).asString().c_str());//ÏÔÊ¾¼¶Êý

		break;
	default:
		BagItem item;
		item.itemId = -1;
		setbagitem(item);
		break;
	}
	
}

void BagCell::IsBeToued()
{
	if (m_Item.itemId<0)
	{
		return;
	}
	Layer*layer;
	switch (m_Item.type)
	{
	case Prop_Skill:
		layer = ShowSkillLayer::create(m_Item.itemId);
		break;
	case Prop_ItemBox:
		layer = ShowBoxLayer::create(m_Item.itemId);
		break;
	case Prop_upgradeBox:
		layer = ShowGiftLayer::create();
		break;
	default:
		return;
		break;
	}
	
	layer->setPosition(0, 0);
	Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(layer);
}