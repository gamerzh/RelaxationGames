#include "utill/Chinese.h"
std::string ChineseWord(const char* wordId)
{
	ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("config/ChineseWords.plist");
	 auto txt_map = txt_vec.at(0).asValueMap();
	 std::string ret = txt_map.at(wordId).asString();
	return ret;
}