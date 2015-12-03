//
// Created by dongdokee on 2015-10-26.
//

#ifndef LOCPROJECT_VISUALTRACKER_H
#define LOCPROJECT_VISUALTRACKER_H

#include "Tracker.h"

class VisualTracker : public Tracker{
private:
    VisualTracker() : graph_ptr(PoseGraph::getInstance()) {}
    VisualTracker(const VisualTracker& other) : graph_ptr(PoseGraph::getInstance()) {}
    ~VisualTracker() {
        deinit();
        delete timer_;
        delete thread;
    }

    int timer_interval;
    boost::asio::deadline_timer* timer_;
    boost::thread* thread;
    bool threadRunning;
    bool isInit;


    PoseGraph* graph_ptr;

public:
    static VisualTracker* getInstance()
    {
        static VisualTracker tracker;
        return &tracker;
    }

    // synchronization (condition variable for reducer)
    boost::condition_variable visual_done_cond;
    boost::mutex visual_done_mutex;
    bool visual_ready;

    void init(int timer_hz);
    void deinit();
    void start();
    void thread_callback();
    void periodic_task();

};


#endif //LOCPROJECT_VISUALTRACKER_H
