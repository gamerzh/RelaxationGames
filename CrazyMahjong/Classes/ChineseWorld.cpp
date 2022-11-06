#include "ChineseWorld.h"
std::string ChineseWord(const char* wordId)
{
	ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("fonts/ChineseWords.plist");
	auto txt_map = txt_vec.at(0).asValueMap();
	for (auto iter = txt_map.begin(); iter != txt_map.end();iter++)
	{
		if (iter->first == wordId)
		{
			return iter->second.asString();
		}
	}
	return "";
}