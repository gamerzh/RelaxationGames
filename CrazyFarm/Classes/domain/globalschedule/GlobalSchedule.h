#ifndef GLOBALSCHEDULE_H_  
#define GLOBALSCHEDULE_H_  
//#include "domain/game/GameManage.h"
#include "cocos2d.h"  
USING_NS_CC;  
   

class GlobalSchedule: public Node {  
    public:
		static GlobalSchedule* getInstance();
		float getGameTime();
		float getRoomTime();
		float getLogEventTime();
		virtual bool init();

    private:  
        GlobalSchedule();  
		
		void updataByMin(float dt); 
		
		void addGameTime(float dt);
		void addRoomTime(float dt);
		void addLogEventTime(float dt);


		const char*   SCHEDULE_GAMETIME = "SCHEDULE_GAMETIME";
		const char*   SCHEDULE_ROOMTIME = "SCHEDULE_ROOMTIME";
		const char*   SCHEDULE_LOGEVETTIME = "SCHEDULE_LOGEVETTIME";
        static GlobalSchedule* m_pSchedule;  
};  
   
#endif /* GLOBALSCHEDULE_H_ */