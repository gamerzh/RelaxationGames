#include "DreamCallback.h"

DreamCallback* DreamCallback::m_instance = new DreamCallback();

DreamCallback* DreamCallback::getInstance()
{
	return m_instance;
}

void DreamCallback::jniCallBack(int a, int b) {
	log("DreamCallback jniCallBack ...");
}