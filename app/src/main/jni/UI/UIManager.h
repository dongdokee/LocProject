//
// Created by dongdokee on 2015-11-20.
//

#ifndef LOCPROJECT_UIMANAGER_H
#define LOCPROJECT_UIMANAGER_H

// also singleton?
class UIManager {
private:
    UIManager() {}
public:
    static UIManager *getInstance();

    void update_step(int step_num);
    void update_specific_particle(double ap_x, double ap_y, double[] xs, double[] ys);
};


#endif //LOCPROJECT_UIMANAGER_H
