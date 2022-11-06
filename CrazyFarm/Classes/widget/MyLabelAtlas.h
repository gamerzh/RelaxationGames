#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MyLabelAtlas : public LabelAtlas
{
public:
	static MyLabelAtlas* create(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap,float MaxWidth);
private:
	bool init(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap, float MaxWidth);
	void update(float delta);
	float _maxWidth;
};


