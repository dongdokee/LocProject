//
// Created by dongdokee on 2015-10-26.
//

#ifndef LOCPROJECT_INERTIALTRACKER_H
#define LOCPROJECT_INERTIALTRACKER_H

#include "Tracker.h"
#include "../DR/StepDetector.h"
#include "../UI/UIManager.h"
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "../Pose/TfMatList.h"


class InertialTracker : public Tracker {
private:
    static InertialTracker *instance;
    static UIManager* uiManager_ptr;
    static Parameter *parameter_ptr;
    static TfMatList *tfmat_list_ptr;
    //static PoseList *pose_list_ptr;

    StepDetector stepDetector;
    int step_num_;

    boost::function<void (IMUDataPtr)> imu_callback_func;
    bool init_done_self_;
    bool init_done_indicator_;

    TIMESTAMP_T last_gyro_time_;

    InertialTracker();
public:
    static InertialTracker* getInstance();
    static void start();

    //virtual void start();
    virtual void thread_callback();
    virtual void periodic_task();

    // callback?
    void step_event_handler();

    void init_pose_list();


    //void sensor_callback();
    void init_callback(IMUDataPtr& imu_ptr);
    void track_callback(IMUDataPtr& imu_ptr);

    // interfaces
    bool &init_done_self() { return init_done_self_; }
    bool &init_done_indicator() { return init_done_indicator_; }
    TIMESTAMP_T &last_gyro_time() { return last_gyro_time_; }
};

#endif //LOCPROJECT_INERTIALTRACKER_H
