//
// Created by dongdokee on 2015-11-21.
//

#include "jni_config.h"

JavaVM *j_vm;
JNIEnv* g_env = 0;
jclass ui_manager_clazz;
jmethodID ui_step_method = 0;
jmethodID ui_best_particle_method = 0;
jmethodID ui_all_particle_method = 0;
jmethodID ui_trajectory_method = 0;
jobject ui_manager_obj;

// 1. caching drawing map
/*void cache_drawmap(JNIEnv* env)
{
    // cache classid and methodid
    jclass clazz = env->FindClass("com/example/dongdokee/locproject/Map/Map");
    drawmap_clazz = (jclass)env->NewGlobalRef(clazz);
    jmethodID callback = env->GetMethodID(drawmap_clazz, "draw", "(DD[D[D)V");
    drawmap_method = callback;
}

void cache_stepview(JNIEnv* env)
{
    // cache classid and methodid
    jclass clazz = env->FindClass("com/example/dongdokee/locproject/MainActivity");
    stepview_clazz = (jclass)env->NewGlobalRef(clazz);
    jmethodID callback = env->GetMethodID(stepview_clazz, "update_stepcount", "()V");
    stepview_method = callback;
}*/
void cache_callbacks(JNIEnv* env) {
    jclass clazz = env->FindClass("com/example/dongdokee/locproject/UI/UIManager");
    ui_manager_clazz = (jclass)env->NewGlobalRef(clazz);
    ui_step_method = env->GetMethodID(ui_manager_clazz, "update_step", "(I)V");
    ui_best_particle_method = env->GetMethodID(ui_manager_clazz, "update_best_particle_view", "([D[D)V");
    ui_all_particle_method = env->GetMethodID(ui_manager_clazz, "update_all_particle_view", "([D[D)V");
    ui_trajectory_method = env->GetMethodID(ui_manager_clazz, "update_trajectory_view", "(DD)V");
}


jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    // 1. cache java machine
    j_vm = vm;
    // 2. set g_env
    if(vm->GetEnv((void**)&g_env, JNI_VERSION_1_4) != JNI_OK)
        goto Final;

    // 3. cache callback functions of JAVA
    cache_callbacks(g_env);

    Final:
    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM* vm, void* reserved)
{
    // uncacheing
    if (!g_env)
    {
        g_env->DeleteGlobalRef(ui_manager_clazz);
        g_env->DeleteGlobalRef(ui_manager_obj);
    }
}






