//
// Created by dongdokee on 2015-11-20.
//

#include "UIManager.h"
#include "../configure/jni_config.h"


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

void UIManager::update_specific_particle(double ap_x, double ap_y, double[] xs, double[] ys) {
    블라블라

    j_vm->AttachCurrentThread(&g_env, 0);

    jdoubleArray xArray = g_env->NewDoubleArray(개수);
    jdoubleArray yArray = g_env->NewDoubleArray(개수);

    어레이 변환 ㄱㄱ xs -> 어레이

    g_env->CallVoidMethod(ui_manager_obj, ui_one_particle_method, (jdouble)ap_x, (jdouble)ap_y, 어레이 변환xs, 어레이변환 ㅌs);
    j_vm->DetachCurrentThread();

    블라블라;
}