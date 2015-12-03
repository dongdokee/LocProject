//
// Created by dongdokee on 2015-11-21.
//

#include "init.h"
#include "../util/extern.h"
#include "../util/Parameter.h"
#include "../Tracker/InertialTracker.h"
#include "../Pose/PoseList.h"
#include "../Math/Random.h"


SensorDataStorage *sensorDataStoragePtr = nullptr;
//bool app_state = false;
//boost::recursive_mutex m_guard_appstate;

void init() {
    sensorDataStoragePtr = SensorDataStorage::getInstance();
    Random::init();
    Parameter::getInstance()->loadDefault();
}

void threads_start() {
    InertialTracker::start();
    //InertialTracker::getInstance()->start();
}

/*void app_state_handler() {
    InertialTracker::getInstance()->app_state_handler();
}*/