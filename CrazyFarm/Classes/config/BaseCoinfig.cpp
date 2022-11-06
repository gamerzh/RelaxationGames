#include "BaseCoinfig.h"
BaseCoinfig* BaseCoinfig::_instance = NULL;

BaseCoinfig::BaseCoinfig(){
}

BaseCoinfig* BaseCoinfig::getInstance(){
	if (_instance == NULL){
		_instance = new BaseCoinfig();
	}
	return _instance;
}

bool BaseCoinfig::loadConfigFromServe()
{
	
	return true;
}