#include "MyLabelAtlas.h"


MyLabelAtlas* MyLabelAtlas::create(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap, float MaxWidth)
{
	MyLabelAtlas* ret = new (std::nothrow) MyLabelAtlas();
	if (ret && ret->init(string, charMapFile, itemWidth, itemHeight, startCharMap, MaxWidth))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool MyLabelAtlas::init(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap, float MaxWidth)
{
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(charMapFile);
	initWithString(string, texture, itemWidth, itemHeight, startCharMap);
	_maxWidth = MaxWidth;
	scheduleUpdate();
	return true;
}

void MyLabelAtlas::update(float delta)
{
	auto nWidth = getContentSize().width;
	if (nWidth>=_maxWidth)
	{
		setScale(_maxWidth / nWidth);
	}
}


