//
// Created by dongdokee on 2015-10-28.
//

#ifndef LOCPROJECT_LOG_H
#define LOCPROJECT_LOG_H

#include <android/log.h>

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "liblocproj", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "liblocproj", __VA_ARGS__)



#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "liblocproj", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "liblocproj", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "liblocproj", __VA_ARGS__)


#endif //LOCPROJECT_LOG_H
