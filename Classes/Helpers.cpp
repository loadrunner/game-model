#include "Helpers.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <AudioToolbox/AudioServices.h>
#endif

namespace helpers {

void Vibrator::vibrate(int time)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "vibrate", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, time);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
#endif
}
void Vibrator::cancelVibrate()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "cancelVibrate", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void URL::open(char* url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openUrl", "(Ljava/lang/String;)V"))
	{
		jstring arg1 = t.env->NewStringUTF(url);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, arg1);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(arg1);
	}
#endif
}

const std::string Locale::getCountry()
{
	std::string country("USA");
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCurrentCountry", "()Ljava/lang/String;"))
	{
		jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		country = cocos2d::JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
	}
#endif
	
	return country;
}

}; // namespace helpers {

