#include "MahjongEvent.h"
#define CC_RETURNF_IF(cond) do{ if(cond) {return false;} } while(0)
#define CC_RETURNNULL_IF(cond) do{ if(cond) {return nullptr;} } while(0)

void addMahjongListener(FLOW_NAME flowName, const std::function<void(EventCustom*)>& callback)
{
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(String::createWithFormat("%d", flowName)->_string, callback);
}

void removeMahjongListener(FLOW_NAME flowName)
{
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(String::createWithFormat("%d", flowName)->_string);
}

void dispatchMahjongEvent(FLOW_NAME flowName, void *optionalUserData)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(String::createWithFormat("%d", flowName)->_string, optionalUserData);
}

PLAYER playerPlusPlus(PLAYER & player)
{
	int t = player;
	player = (PLAYER)(++t % 4);
	return player;
}

bool addToTextureCache(std::string path, std::string name, int num)
{
	if (0 >= num)
	{
		return false; 
	}

	for (int index = 0; index < num; ++index)
	{
		Image* image = nullptr;
		image = new (std::nothrow) Image();

		std::string keyStr = name + (0 == num ? "" : String::createWithFormat("_%d", index)->_string);
		std::string pathStr = path + keyStr + ".png";

		CC_RETURNF_IF(nullptr == image);
	
		CC_RETURNF_IF(!image->initWithImageFile(pathStr));
		CCLOG("-------- Import Image %s", keyStr.c_str());

		CC_RETURNF_IF(nullptr == Director::getInstance()->getTextureCache()->addImage(image, keyStr));
	}
	return true;
}

bool addToTextureCache(std::string path, std::string name)
{
	Image* image = nullptr;
	image = new (std::nothrow) Image();

	std::string keyStr = name;
	std::string pathStr = path + name + ".png";

	CC_RETURNF_IF(nullptr == image);

	CC_RETURNF_IF(!image->initWithImageFile(pathStr));
	CCLOG("-------- Import Image %s", keyStr.c_str());

	CC_RETURNF_IF(nullptr == Director::getInstance()->getTextureCache()->addImage(image, keyStr));	return true;
}

Animate* createAnimateFromTextureCache(std::string name, int num, float totalTime)
{
	if (1 >= num)
	{
		return nullptr;
	}
	float delayTime = totalTime / num;
	Animation* animation = Animation::create();
	TextureCache* texCache = Director::getInstance()->getTextureCache();
	for (int index = 0; index < num; ++index)
	{
		std::string keyStr = name + String::createWithFormat("_%d", index)->_string;
		Texture2D* tex = texCache->getTextureForKey(keyStr);
		CC_RETURNNULL_IF(!tex);

		Rect rect = Rect::ZERO;
		rect.size = tex->getContentSize();
		animation->addSpriteFrameWithTexture(tex, rect);
	}
	animation->setDelayPerUnit(delayTime);

	Animate* animate = Animate::create(animation);
	animate->retain();

	return animate;
}

Texture2D* getTexFromeCache(std::string key)
{
	return Director::getInstance()->getTextureCache()->getTextureForKey(key);
}
Sprite* addAnimWithAnimate(Node & nodeParent, Animate* & animate, std::string path, std::string name, int num, float time)
{
	Sprite* animSpr = Sprite::create();
	nodeParent.addChild(animSpr);
	CC_RETURNNULL_IF(!addToTextureCache(path, name, num));
	animate = createAnimateFromTextureCache(name, num, time);
	return animSpr;
}

Sprite* addAnimNoAnimte(Node & nodeParent, std::string path, std::string name)
{
	CC_RETURNNULL_IF(!addToTextureCache(path, name));
	Sprite* animSpr = Sprite::createWithTexture(getTexFromeCache(name));
	nodeParent.addChild(animSpr);
	return animSpr;	
}