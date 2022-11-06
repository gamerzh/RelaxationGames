#include "NewbieMannger.h"


NewbieMannger* NewbieMannger::_instance = NULL;

NewbieMannger::NewbieMannger(){

}


NewbieMannger* NewbieMannger::getInstance(){
	if (_instance == NULL){
		_instance = new NewbieMannger();
	}
	return _instance;
}
void NewbieMannger::resetInfo()
{
	setisGetFirstReward(0);
	setisOverTeachMode(0);
	setNBShootCounts(0);
	setisTeachUpgradeTurrent(0);
}