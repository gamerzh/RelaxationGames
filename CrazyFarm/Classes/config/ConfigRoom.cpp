#include "config/ConfigRoom.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
ConfigRoom* ConfigRoom::_instance = NULL;

ConfigRoom::ConfigRoom(){
}

ConfigRoom* ConfigRoom::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigRoom();
	}
	return _instance;
}

bool ConfigRoom::LoadConfig() {
    bool bRet = false;
    while (!bRet) {
        
        	std::string filename;	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			if (ISDEBUGCONFIG)
			{	
				filename += JniFunUtill::getInstance()->getSDcardpath();
				filename += "/CrazyFarm/";
			}
	#endif
		filename += "config/config_room.json";
     
        rapidjson::Document doc;
        if (!FileUtils::getInstance()->isFileExist(filename))
        {
            break;
        }
        
        std::string data = FileUtils::getInstance()->getStringFromFile(filename);
        doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
        if (doc.HasParseError())
        {
            log("ConfigRoom get json data err!");
            break;
        }
        rapidjson::Value& itemList = doc["item_list"];
        if (!itemList.IsArray())
        {
            log("ConfigRoom The data is not json");
            break;
        }
        for (unsigned int i = 0; i < itemList.Size(); ++i) {
            
            const rapidjson::Value &val = itemList[i];
            Room room;
            room.room_id	= val["room_id"].GetInt();
            room.ui_id	= val["ui_id"].GetInt();
            room.unlock_turrent_level	= val["unlock_turrent_level"].GetInt();
            
			rooms.push_back(room);
        }
        
        return true;
    }
    return true;
}

std::vector<Room> ConfigRoom::getRooms() {
	return rooms;
}

Room ConfigRoom::getRoombyId(int nId) {
	for (auto room : rooms) {
		if (room.room_id == nId) {
			return room;
		}
	}
    return rooms.at(0);
}

Room ConfigRoom::getNextRoombyId(int nId) {
	for (int i = 0; i < rooms.size();i++)
	{
		if (rooms[i].room_id==nId)
		{
			if (i+1<rooms.size())
			{
				return rooms[i + 1];
			}
		}
		else
		{
			Room room;
			room.room_id = 1;
			return room;
		}
	}
	Room room;
	room.room_id = 1;
	return room;
}

int ConfigRoom::getPlayerCounts(int currentHour, int roomId) {
    if(roomId < 1 || roomId > 4) {
        roomId = 4;
    }
    int base = 0;
    if(currentHour <= 8) {
        base = -0.8;
    }else if(currentHour <= 18) {
        base = -0.4;
    }else if(currentHour <= 22) {
        base = 0;
    }else {
        base = -0.4;
    }
    if(roomId == 1) {
        if(room1Players == 0) {
            
            room1Players = int((1+base)*12000) + rand()%4000;
        }else {
            room1Players = room1Players - (room1Players/20) + rand()%(room1Players/10+1);
        }
        if(room1Players <= 0) {
            room1Players =  rand()%4000;
        }
        return  room1Players;
    }else if(roomId == 2) {
        if(room2Players == 0) {
            room2Players = int((1+base)*6000) + rand()%4000; //6000-10000
        }else {
            room2Players = room2Players -(room2Players/20) + rand()%(room2Players/10+1);
        }
        if(room2Players <= 0) {
            room2Players = rand()%3000;
        }
        return  room2Players;
    }else if(roomId == 3) {
        if(room3Players == 0) {
            room3Players = int((1+base)*4000) + rand()%4000; //4000-8000
        }else {
			room3Players = room3Players-(room3Players / 20) + rand() % (room3Players / 10 +1);
        }
        if(room3Players <= 0) {
            room3Players = rand()%1000;
        }
        return room3Players;
    }else if(roomId == 4) {
        if(room4Players == 0) {
            room4Players = int((1+base)*500) + rand()%1000; //500-1500
        }else {
			room4Players = room4Players-(room4Players / 20) + rand() % (room4Players / 10 + 1);
        }
        if(room4Players <= 0) {
            room4Players =  rand()%100;
        }
        return room4Players;
    }
    
    return 3757 + rand()%300;

}
