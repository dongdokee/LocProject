//
// Created by dongdokee on 2015-10-26.
//

#include "VisualTracker.h"

void VisualTracker::init(int timer_hz)
{
    threadRunning = false;

    isInit = false;

    // set timer interval
    timer_interval = (int)(1000 / (double)timer_hz);

    visual_ready = false;
}
void VisualTracker::deinit()
{
    threadRunning = false;
    isInit = false;
}
void VisualTracker::start() {
    // run thread with thread_callback function
    thread = new boost::thread(boost::bind(&VisualTracker::thread_callback, this));
}
void VisualTracker::thread_callback()
{
    LOGD("visualTracker thread started");
    threadRunning = true;
    boost::asio::io_service io;

    timer_ = new boost::asio::deadline_timer(io);
    // set interval
    timer_->expires_from_now(boost::posix_time::milliseconds(timer_interval));
    timer_->async_wait(boost::bind(&VisualTracker::periodic_task, this));

    // run timer
    io.run();
    LOGD("visualTracker thread killed");
}
void VisualTracker::periodic_task()
{
    // pre synchronization (lock mutex for conditional variable)
    boost::unique_lock<boost::mutex> lock(visual_done_mutex);

    // post synchronization
    visual_ready = true;
    visual_done_cond.notify_all();
}