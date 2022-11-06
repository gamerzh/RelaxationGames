#include "RolePanel.h"
#include "MahjongAnim.h"
#include "HallScene.h"
#include "PxPayMannger.h"
#include "User.h"
#include "ToolTipMannger.h"
RolePanel::RolePanel()
{
	rolePos[5] = Vec2(155, 265);
	rolePos[6] = Vec2(340, 230);
	rolePos[7] = Vec2(525, 265);
	for (int i = 1; i < 5;i++)
	{
		rolePos[i] = rolePos[5] - Vec2(185 * (5 - i), 0);
	}
	for (int i = 8; i < 13;i++)
	{
		rolePos[i] = rolePos[7] + Vec2(195 * (i - 7), 0);
	}
}

bool RolePanel::init()
{
	if (!Node::init())
	{
		return false;
	}
	left = Node::create();
	left->setPosition(-1000, 0);
	addChild(left);

	right = Node::create();
	right->setPosition(1000, 0);
	addChild(right);
	_curindex = User::getInstance()->getroleNowIndex();
	createCommonUI();
	createList();
	createRoleChoose();
	createHeadChoose();
	updateRoleShow(_curindex);
	

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(RolePanel::onTouchBegin,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
	return true;
}
void RolePanel::hide()
{
	left->runAction(MoveBy::create(0.1f, Vec2(-1000, 0)));
	right->runAction(MoveBy::create(0.1f, Vec2(1000, 0)));
}
void RolePanel::show()
{
	left->runAction(MoveBy::create(0.1f, Vec2(1000, 0)));
	right->runAction(MoveBy::create(0.1f, Vec2(-1000, 0)));
}
void RolePanel::createList()
{
	RoleListNode*begin;
	for (int i = 1; i <= 12;i++)
	{
		RoleListNode* role = new RoleListNode();
		role->spRole = RoleShow::create(i);

		
		auto str = String::createWithFormat("head_%d.png", i);
		role->spHead = Sprite::create(str->getCString());
		

		role->_index = i;
		role->_posIndex = i;
		if (roleNode == nullptr)
		{
			roleNode = role;
			begin = role;
		}
		else
		{
			roleNode->_late = role;
			roleNode = role;
		}
	}
	roleNode->_late = begin;
	roleNode = begin;
}

void RolePanel::createRoleChoose()
{
	auto clipper = ClippingNode::create();
	auto begin = roleNode;
	for (int i = 0; i < 12;i++)
	{
		begin->spRole->setPosition(rolePos[begin->_posIndex]);
		clipper->addChild(begin->spRole);
		begin = begin->_late;
		
	}


	auto s = Director::getInstance()->getWinSize();


	auto shape = DrawNode::create();
	static Color4F green(0, 1, 0, 1);
	shape->drawSolidRect(Vec2(80, 24), Vec2(595, 410), green);

	clipper->setInverted(false);
	clipper->setStencil(shape);
	clipper->setAnchorPoint(Vec2(0,0));
	clipper->setPosition(0,0);
	left->addChild(clipper);
}
//6是中间项
void RolePanel::updateRoleShow(int curindex)
{
	int diffPosindex;
	auto ptr = roleNode;
	while (ptr->_posIndex!=6)
	{
		ptr = ptr->_late;
	}
	diffPosindex = ptr->_index - curindex;
	for (int i = 0; i < 12;i++)
	{
		int tempindex = ptr->_posIndex + diffPosindex;
		getIndexBy1_12(tempindex);
		ptr->_posIndex = tempindex;
		ptr->spRole->runAction(MoveTo::create(0.1f, rolePos[ptr->_posIndex]));

		if (ptr->_index == curindex)
		{
			ptr->spHead->getChildByName("light")->setVisible(true);
			ptr->spRole->setScale(1.0);
			ptr->spRole->showLight();
			//设置名字 和 按键
			auto path = String::createWithFormat("name_%d.png", ptr->_index);
			((Sprite*)(left->getChildByName("name")))->setTexture(path->getCString());
			bool isAvailable = User::getInstance()->isAvailableRole(_curindex);
			auto bt = (Button*)(left->getChildByName("Btn_BuyRole"));
			if (isAvailable)
			{
				bt->loadTextureNormal("Btn_ChooseRole_1.png");
				bt->loadTexturePressed("Btn_ChooseRole_2.png");
				left->getChildByName("coin")->setVisible(false);
				left->getChildByName("coinprice")->setVisible(false);
			}
			else
			{
				bt->loadTextureNormal("Btn_BuyRole_1.png");
				bt->loadTexturePressed("Btn_BuyRole_2.png");
				left->getChildByName("coin")->setVisible(true);
				left->getChildByName("coinprice")->setVisible(true);
				((LabelAtlas*)(left->getChildByName("coinprice")))->setString(Value(getPrice(_curindex)).asString());
			}

		}
		else
		{
			ptr->spHead->getChildByName("light")->setVisible(false);
			ptr->spRole->setScale(0.7);
			ptr->spRole->hideLight();
		}
		ptr = ptr->_late;
	}

}

void RolePanel::createHeadChoose()
{
	auto frame = Sprite::create("headChooseFrame.png");
	frame->setPosition(693, 250);
	frame->setName("headframe");
	right->addChild(frame);
	auto iter = roleNode;
	for (int i = 1; i <= 12;i++)
	{
		auto pos = Vec2((iter->_index - 1) % 3*(68), (iter->_index -1) / 3*(-68))+Vec2(13,293);
		iter->spHead->setPosition(pos);
		iter->spHead->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		frame->addChild(iter->spHead);
		auto light = Sprite::create("headLight.png");
		light->setPosition(iter->spHead->getContentSize() / 2);
		iter->spHead->addChild(light, -1,"light");
		light->setVisible(false);
		iter = iter->_late;
	}
}
void RolePanel::createCommonUI()
{
	auto nameframe = Sprite::create("role_nameFrame.png");
	nameframe->setPosition(340, 415);
	left->addChild(nameframe,2);

	auto name = Sprite::create();
	name->setPosition(340, 415);
	name->setName("name");
	left->addChild(name,2);

	
	auto bt = Button::create("Btn_BuyRole_1.png","Btn_BuyRole_2.png");
	bt->addTouchEventListener(this, toucheventselector(RolePanel::BtnCallback));
	bt->setPosition(Vec2(340, 45));
	bt->setName("Btn_BuyRole");
	left->addChild(bt,2);

	auto btleft = Button::create("Btn_last_1.png", "Btn_last_2.png");
	btleft->addTouchEventListener(this, toucheventselector(RolePanel::BtnCallback));
	btleft->setPosition(Vec2(205, 78));
	left->addChild(btleft);
	btleft->setName("btleft");

	auto btRight = Button::create("Btn_next_1.png", "Btn_next_2.png");
	btRight->addTouchEventListener(this, toucheventselector(RolePanel::BtnCallback));
	btRight->setPosition(Vec2(499, 78));
	left->addChild(btRight);
	btRight->setName("btRight");


	auto back = Button::create("Btn_back_1.png", "Btn_back_2.png");
	back->addTouchEventListener(this, toucheventselector(RolePanel::BtnCallback));
	back->setPosition(Vec2(54, 47));
	left->addChild(back);
	back->setName("back");

	auto coin = Sprite::create("coin.png");
	coin->setPosition(302,93);
	left->addChild(coin,1,"coin");
	auto label = LabelAtlas::create("8000", "fnt_roleprice.png", 13, 22, '0');
	label->setPosition(coin->getPosition()+Vec2(coin->getContentSize().width/2,0));
	label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	left->addChild(label, 1, "coinprice");

}


void RolePanel::BtnCallback(Ref*psend, TouchEventType type)
{
	auto bt = (Button*)psend;
	auto btName = bt->getName();
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
		if (btName == "Btn_BuyRole")
		{
			if (User::getInstance()->isAvailableRole(_curindex))
			{
				User::getInstance()->setroleNowIndex(_curindex);
			}
			else
			{
				auto price = getPrice(_curindex);
				if (User::getInstance()->getMyCoins() >= price)
				{
					User::getInstance()->addCoin(-price);
					User::getInstance()->setAvailableRole(_curindex);
					User::getInstance()->setroleNowIndex(_curindex);
					updateRoleShow(_curindex);
				}
				else
				{
					ToolTipMannger::showDioag(this->getParent(),ToolTipMannger::TipType::Tip_LackingCoinOther);
				}
			}
			
		}
		if (btName == "btleft")
		{
			getIndexBy1_12(--_curindex);
			updateRoleShow(_curindex);
		}
		if (btName == "btRight")
		{
			getIndexBy1_12(++_curindex);
			updateRoleShow(_curindex);
		
		}
		if (btName == "back")
		{
			hide();
			auto node = (HallScene*)getParent();
			node->show();
		}

	}
}

void RolePanel::getIndexBy1_12(int &index)
{
	if (index <= 0)
	{
		index += 12;
	}
	if (index > 12)
	{
		index -= 12;
	}
}

bool RolePanel::onTouchBegin(Touch*touch, Event*event)
{
	auto heads = right->getChildByName("headframe");
	auto localPos = heads->convertTouchToNodeSpace(touch);
	auto iter = roleNode;
	for (int i = 0; i < 12;i++)
	{
		if (iter->spHead->getBoundingBox().containsPoint(localPos))
		{
			_curindex = iter->_index;
			updateRoleShow(_curindex);
			return true;
		}
		else
		{
			iter = iter->_late;
		}
	}
	return true;
}
int RolePanel::getPrice(int index)
{
	if (index==1)
	{
		return 0;
	}
	else if (index>=2&&index<=5)
	{
		return 380000;
	}
	else if (index >= 6 && index <= 8)
	{
		return 680000;
	}
	else if (index >=9 && index <= 12)
	{
		return 880000;
	}
}