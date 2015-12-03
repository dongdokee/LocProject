//
// Created by dongdokee on 2015-10-29.
//

#include "StepDetector.h"

StepDetector::StepDetector() : parameter_ptr(Parameter::getInstance()) {
    reset();
}

void StepDetector::reset() {
    Aref_ = 9.81;
    Adir_ = true;
    prev_time_ = 0;
}

bool StepDetector::pushAndDetect(IMUData &accelData) {
    TIMESTAMP_T t = accelData.time();
    IMUDATA_T magnitude = sqrt(accelData.x() * accelData.x() + accelData.y() * accelData.y() + accelData.z() * accelData.z());


    if (!Adir_ && magnitude > Aref_)
    {
        Aref_ = magnitude;
        prev_time_ = t;
    }
    else if (!Adir_ && Aref_ - magnitude >= parameter_ptr->step_delta_mag_thresh())
    {
        Adir_ = !Adir_;
        Aref_ = magnitude;
    }
    else if(Adir_ && magnitude < Aref_)
    {
        Aref_ = magnitude;
    }
    else if(Adir_ && magnitude - Aref_ >= parameter_ptr->step_delta_mag_thresh())
    {
        if (t - prev_time_ >= parameter_ptr->step_delta_t_thresh()) {
            Adir_ = !Adir_;
            Aref_ = magnitude;

            prev_time_ = t;
            return true;
        }
    }
    return false;

}

