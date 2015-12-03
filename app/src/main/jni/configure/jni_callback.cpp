//
// Created by dongdokee on 2015-11-21.
//

#include "jni_config.h"
#include "init.h"
#include "jni_headers/com_example_dongdokee_locproject_UI_UIManager.h"
#include "jni_headers/com_example_dongdokee_locproject_Sensors_InertialThread.h"
#include "jni_headers/com_example_dongdokee_locproject_MainActivity.h"

#include "../util/extern.h"
#include "../Tracker/InertialTracker.h"

// 1. tracker thread start
// 2. cahcing, global variable initialization, ...
JNIEXPORT void JNICALL Java_com_example_dongdokee_locproject_MainActivity_init
(JNIEnv *env, jobject obj)
{
    init();
    threads_start();
}

JNIEXPORT void JNICALL Java_com_example_dongdokee_locproject_MainActivity_start_1navigation
(JNIEnv *env, jobject obj)
{
    InertialTracker::getInstance()->init_done_indicator() = true;
    LOGD("start navigation");
}

JNIEXPORT void JNICALL Java_com_example_dongdokee_locproject_MainActivity_test
(JNIEnv *env, jobject obj)
{
    sensorDataStoragePtr->test();
}

JNIEXPORT void JNICALL Java_com_example_dongdokee_locproject_UI_UIManager_init
(JNIEnv *env, jobject obj)
{
    ui_manager_obj = env->NewGlobalRef(obj);
}

JNIEXPORT void JNICALL Java_com_example_dongdokee_locproject_Sensors_InertialThread_inputAccel
(JNIEnv *env, jobject obj, jdouble t, jdouble x, jdouble y, jdouble z)
{
    sensorDataStoragePtr->push_accel(t, x, y, z);
}
JNIEXPORT void JNICALL Java_com_example_dongdokee_locproject_Sensors_InertialThread_inputGyro
(JNIEnv *env, jobject obj, jdouble t, jdouble x, jdouble y, jdouble z)
{
    sensorDataStoragePtr->push_gyro(t, x, y, z);
}
JNIEXPORT void JNICALL Java_com_example_dongdokee_locproject_Sensors_InertialThread_inputCompass
(JNIEnv *env, jobject obj, jdouble t, jdouble x, jdouble y, jdouble z)
{
    sensorDataStoragePtr->push_compass(t, x, y, z);
}
JNIEXPORT void JNICALL Java_com_example_dongdokee_locproject_Sensors_InertialThread_inputGravity
(JNIEnv *env, jobject obj, jdouble t, jdouble x, jdouble y, jdouble z)
{
    sensorDataStoragePtr->push_gravity(t, x, y, z);
}