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
    void update_trajectory(double x, double y);
    void update_best(double x[], double y[], int num_elem);
    void update_all(double x[], double y[], int num_elem);

};


#endif //LOCPROJECT_UIMANAGER_H
