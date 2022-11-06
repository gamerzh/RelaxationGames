#include "RoleShow.h"
#include "AnimationUtil.h"


RoleShow*RoleShow::create(int index)
{
	RoleShow*cell = new (std::nothrow)RoleShow();
	if (cell&&cell->init(index))
	{
		cell->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(cell);
		cell == nullptr;
	}
	return cell;
}





bool RoleShow::init(int index)
{
	if (!Sprite::init())
	{
		return false;
	}
	auto str = String::createWithFormat("role_%d.png", index);
	setTexture(str->getCString());
	auto sssize = getContentSize();
	auto site = Sprite::create("role_site.png");
	site->setPosition(sssize.width / 2, 0);
	addChild(site, -2);

	auto light = Sprite::create();
	light->setPosition(sssize.width / 2, sssize.height / 2);
	addChild(light, 0,"light");
	light->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("ani_huaguang")));

	light->setVisible(false);

	return true;
}
void RoleShow::hideLight()
{
	getChildByName("light")->setVisible(false);
}
void RoleShow::showLight()
{
	getChildByName("light")->setVisible(true);
}