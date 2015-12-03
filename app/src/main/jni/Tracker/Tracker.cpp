//
// Created by dongdokee on 2015-10-26.
//

#include "Tracker.h"

Tracker::Tracker() : mStorage_(SensorDataStorage::getInstance()), timer_interval_(9999999), timer_(nullptr), thread_(nullptr), threadRunning_(false), isInit_(false) { }

Tracker::~Tracker() {
    deinit();
    if (!timer_)
        delete timer_;
    if (!thread_)
        delete thread_;
}

void Tracker::init(int timer_hz) {
    threadRunning_ = false;
    timer_interval_ = (int)(1000 / (double)timer_hz); // in milliseconds
    isInit_ = true;
}
void Tracker::deinit() {
    threadRunning_ = false;
    timer_interval_ = 9999999;
    isInit_ = false;
}


