#include "DreamCallback.h"
#include "MenuScenePayHandler.h"

DreamCallback* DreamCallback::m_instance = new DreamCallback();

DreamCallback* DreamCallback::getInstance()
{
    return m_instance;
}

void DreamCallback::jniCallBack(int code, int result) {
    //result 0失败 1成功
    log("DreamCallback jniCallBack ...");
    if(code == 1){
        if(result ==1){
            int a[2] = {8,4};
            int b[2] = {20,10};
            MenuScenePayHandler::getInstance()->dealEventSuccess(18, a , b, 2);
        }else{
            int a[1] = {8};
            int b[1] = {20};
            MenuScenePayHandler::getInstance()->dealEventSuccess(18, a , b, 1);
        }
    }else if(code == 2){
        if(result ==1){
            int a[1] = {1};
            int b[1] = {5};
            MenuScenePayHandler::getInstance()->dealEventSuccess(4, a , b, 1);
        }else{
            MenuScenePayHandler::getInstance()->dealEventFail(4);
        }
    }else if(code == 3){
        if(result ==1){
            int a[1] = {4};
            int b[1] = {10};
            MenuScenePayHandler::getInstance()->dealEventSuccess(8, a , b, 1);
        }
    }else if(code == 4){
        if(result ==1){
            int a[1] = {2};
            int b[1] = {10};
            MenuScenePayHandler::getInstance()->dealEventSuccess(9, a , b, 1);
        }
    }else if(code == 5){
        if(result ==1){
            int a[1] = {3};
            int b[1] = {10};
            MenuScenePayHandler::getInstance()->dealEventSuccess(10, a , b, 1);
        }
    }
}
