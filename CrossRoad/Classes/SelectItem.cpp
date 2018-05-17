#include "SelectItem.h"
#include "UserData.h"

SelectItem* SelectItem::create(int type) {
	auto ret = new SelectItem();
	if (ret && ret->init(type)) {
		ret->autorelease();
		return ret;
	}
	else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool SelectItem::init(int type) {
	if (!Node::init()) {
		return false;
	}

	this->type = type;
	auto win = Director::getInstance()->getWinSize();

	auto box = Sprite::create("skin_box.png");
	box->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	box->setPosition(win.width/20, 0);
	addChild(box);

	auto name = Label::createWithSystemFont("Super Man", "arial", 40);
	name->setColor(Color3B(0,0,0));
	name->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	name->setPosition(win.width*0.26, 80);
	addChild(name);

	auto hint = Label::createWithSystemFont("I'll destory the world", "arial", 20);
	hint->setColor(Color3B(0, 0, 0));
	hint->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	hint->setPosition(win.width *0.26, 10);
	addChild(hint);

	image = MenuItemImage::create("btn_kong.png", "btn_kong.png", CC_CALLBACK_0(SelectItem::useModle, this));
	image->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	auto boxMenu = Menu::create(image, NULL);
	boxMenu->setPosition(win.width*0.58,50);
	addChild(boxMenu);

	std::vector<std::string> modlist = UserData::getInstance()->getPlayerMod();
	for (auto var : modlist)
	{
		if (this->type == atoi(var.c_str())) {
			playerHasMod = ItemStatus::have;
		}
	}

	if (playerHasMod > 0) {
		//玩家已经拥有此皮肤,显示为装备或装备中
		if (atoi(UserData::getInstance()->getCurrentMod().c_str()) == this->type) {
			//装备中
			playerHasMod = ItemStatus::use;
			changeBtnTexture(playerHasMod);
		}
		else
		{
			//装备
			playerHasMod = ItemStatus::have;
			changeBtnTexture(playerHasMod);
		}
	}
	else {
		//显示金额
		auto gol = Label::createWithSystemFont(String::createWithFormat("%d G", getPriceByType(this->type))->_string,"arial",30);
		gol->setTag(1026);
		gol->setAnchorPoint(Point::ANCHOR_MIDDLE);
		gol->setPosition(win.width*0.67, 75);
		addChild(gol);
	}

	scheduleUpdate();

	return  true;
}

int SelectItem::getPriceByType(int type){
	if (type == 0) {
		return 10;
	}
	else {
		return 15;
	}
}


void SelectItem::useModle() {
	if (playerHasMod == ItemStatus::did_not_have) {
		//购买皮肤,购买后直接使用
		auto goldNumber = UserData::getInstance()->getPlayerGoldNum();
		if (goldNumber  >= getPriceByType(this->type)) {
			UserData::getInstance()->setPlayerGoldNum(goldNumber - getPriceByType(this->type));
			playerHasMod = ItemStatus::use;
			auto curr = String::createWithFormat("%d", this->type)->_string;
			UserData::getInstance()->addPlayerMod(curr);
			UserData::getInstance()->setCurrentMod(curr);
			if (NULL != getChildByTag(1026)) {
				getChildByTag(1026)->setVisible(false);
			}
		}
		else {
			//TODO 弹出购买金币的计费点
		}
	}
	else if (playerHasMod == ItemStatus::have) {
		//装备当前皮肤
		playerHasMod = ItemStatus::use;
		auto curr = String::createWithFormat("%d", this->type)->_string;
		UserData::getInstance()->setCurrentMod(curr);
	}
}

void SelectItem::changeBtnTexture(ItemStatus status) {
	 if (status == ItemStatus::use) {
		 playerHasMod = ItemStatus::use;
		 image->setNormalImage(Sprite::create("btn_zhong.png"));
		 image->setSelectedImage(Sprite::create("btn_zhong.png"));
	}
	else if(status == ItemStatus::have)
	{
		playerHasMod = ItemStatus::have;
		image->setNormalImage(Sprite::create("btn_yong.png"));
		image->setSelectedImage(Sprite::create("btn_yong.png"));
	}

}

void SelectItem::update(float dt) {

	std::vector<std::string> modlist = UserData::getInstance()->getPlayerMod();
	for (auto var : modlist)
	{
		if (this->type == atoi(var.c_str())) {
			if (atoi(UserData::getInstance()->getCurrentMod().c_str()) == this->type) {
				changeBtnTexture(ItemStatus::use);
			}
			else {
				changeBtnTexture(ItemStatus::have);
			}
		}
	}
}