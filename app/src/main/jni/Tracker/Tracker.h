//
// Created by dongdokee on 2015-10-26.
//

#ifndef LOCPROJECT_TRACKER_H
#define LOCPROJECT_TRACKER_H

#include "../DataStructures/SensorData.h"
//#include "boost/function.hpp" // boost::function
#include "boost/asio.hpp"
#include "boost/thread.hpp"
//#include "../Pose/PoseGraph.h"
#include "../DataStructures/SensorDataStorage.h"

// 1. Tracker is a thread
// 2. Thread generates relative motion (TfMat) conditionally

// Tracker is performed as this
// 1. sensor data is drawn from storage
// 2. calculate the TfMat
// 3. If there is a TfMat, register it (conditionally)
// 4. i s  i n i t

class Tracker {
private:
    int timer_interval_;
    boost::asio::deadline_timer* timer_;
    boost::thread* thread_;
    bool threadRunning_;
    bool isInit_;

    //boost::function<void ()> thread_callback_ptr;
    //boost::function<void ()> periodic_task_ptr;

    //PoseGraph* graph_ptr_;
    SensorDataStorage* mStorage_;
public:
    Tracker();
    ~Tracker();

    int &timer_interval() { return timer_interval_; }
    boost::asio::deadline_timer* &timer() { return timer_; }
    boost::thread* &thread() { return thread_; }
    bool &threadRunning() { return threadRunning_; }
    bool &isInit() { return isInit_; }
    //PoseGraph* &graph_ptr() { return graph_ptr_; }
    SensorDataStorage* &mStorage() { return mStorage_; }


    void init(int timer_hz); // Tracker is performed in frequency of timer_hz
    void deinit();
    //virtual void start() = 0;
    //virtual void thread_callback() = 0;
    //virtual void periodic_task() = 0;
};


#endif //LOCPROJECT_TRACKER_H
