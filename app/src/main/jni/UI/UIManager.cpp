//
// Created by dongdokee on 2015-11-20.
//

#include "UIManager.h"
#include "../configure/jni_config.h"
#include "../util/log.h"


UIManager *UIManager::getInstance() {
    static UIManager uiManager;
    return &uiManager;
}

void UIManager::update_step(int step_num) {
    // call functin
    j_vm->AttachCurrentThread(&g_env, 0);
    g_env->CallVoidMethod(ui_manager_obj, ui_step_method, step_num);
    j_vm->DetachCurrentThread();
}

void UIManager::update_trajectory(double x, double y) {
    j_vm->AttachCurrentThread(&g_env, 0);
    g_env->CallVoidMethod(ui_manager_obj, ui_trajectory_method, (jdouble)x, (jdouble)y);
    j_vm->DetachCurrentThread();
}
void UIManager::update_best(double x[], double y[], int num_elem) {
    j_vm->AttachCurrentThread(&g_env, 0);
    jdoubleArray x_array = g_env->NewDoubleArray(num_elem);
    jdoubleArray y_array = g_env->NewDoubleArray(num_elem);
    g_env->SetDoubleArrayRegion( x_array, 0, num_elem, x);
    g_env->SetDoubleArrayRegion( y_array, 0, num_elem, y);
    g_env->CallVoidMethod(ui_manager_obj, ui_best_particle_method, x_array, y_array);
    j_vm->DetachCurrentThread();
}
void UIManager::update_all(double x[], double y[], int num_elem) {
    j_vm->AttachCurrentThread(&g_env, 0);
    jdoubleArray x_array = g_env->NewDoubleArray(num_elem);
    jdoubleArray y_array = g_env->NewDoubleArray(num_elem);
    g_env->SetDoubleArrayRegion( x_array, 0, num_elem, x);
    g_env->SetDoubleArrayRegion( y_array, 0, num_elem, y);
    g_env->CallVoidMethod(ui_manager_obj, ui_all_particle_method, x_array, y_array);
    j_vm->DetachCurrentThread();
}

