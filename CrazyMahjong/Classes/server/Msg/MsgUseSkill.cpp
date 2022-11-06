#include "MsgUseSkill.h"

void Msg_UseSkill::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}

	 errorcode = doc["errorcode"].GetInt();
	if (errorcode == 0)
	{
		use_type = doc["use_type"].GetInt();
		if (use_type==0)
		{
			num = doc["price"].GetInt();
		}
		else if (use_type == 1)
		{
			price = doc["price"].GetInt();
		}
		itemid = doc["item_id"].GetInt();
	}
	else
	{
		errormsg = doc["errormsg"].GetString();
	}


}