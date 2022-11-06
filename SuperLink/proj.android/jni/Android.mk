LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
					hellocpp/payproxy.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameData.cpp  \
                   ../../Classes/GameGuiLayer.cpp  \
                   ../../Classes/GameLayer.cpp  \
                   ../../Classes/GamePauseLayer.cpp  \
                   ../../Classes/GameResultLayer.cpp  \
                   ../../Classes/GameResultScene.cpp  \
                   ../../Classes/LobbyScene.cpp  \
				   ../../Classes/Audio.cpp  \
				   ../../Classes/Cell.cpp  \
				   ../../Classes/GamePauseScene.cpp  \
					 ../../Classes/Matrix.cpp  \
					  ../../Classes/SignInLayer.cpp  \
					   ../../Classes/CallAndroidMethod.cpp  \
					   ../../Classes/MenuScenePayHandler.cpp  \
                   ../../Classes/GameScene.cpp

                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
