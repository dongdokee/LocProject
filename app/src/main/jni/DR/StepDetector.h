//
// Created by dongdokee on 2015-10-29.
//

#ifndef LOCPROJECT_STEPDETECTOR_H
#define LOCPROJECT_STEPDETECTOR_H

#include "../util/Parameter.h"
#include "../DataStructures/SensorData.h"

class StepDetector {
private:
    Parameter *parameter_ptr;

    double Aref_;
    bool Adir_;
    double prev_time_;

public:
    StepDetector();

    /* inteface */
    double &Aref() { return Aref_; }
    bool &Adir() { return Adir_; }
    double &prev_time() { return prev_time_; }

    void reset();
    bool pushAndDetect(IMUData& accelData);

};


/*
class StepDetector {
private:
    double Aref;
    bool Adir;
    double prev_time;

public:
    StepDetector() : Aref(9.81), Adir(true), prev_time(0) {}
    StepDetector(double Aref_, bool Adir_, double prev_time_) : Aref(Aref_), Adir(Adir_), prev_time(prev_time_) {}

    void reset();

    bool pushAndDetect(AccelData& accelData);
};*/


#endif //LOCPROJECT_STEPDETECTOR_H
