//
// Created by dongdokee on 2015-11-21.
//

#ifndef LOCPROJECT_JNI_CONFIG_H
#define LOCPROJECT_JNI_CONFIG_H

#include <jni.h>

extern JavaVM *j_vm;
extern JNIEnv* g_env;
extern jclass ui_manager_clazz;
extern jmethodID ui_step_method;
extern jmethodID ui_one_particle_method;
extern jobject ui_manager_obj;

#endif //LOCPROJECT_JNI_CONFIG_H
