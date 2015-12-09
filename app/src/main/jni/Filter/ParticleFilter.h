//
// Created by dongdokee on 2015-11-03.
//

#ifndef LOCPROJECT_PARTICLEFILTER_H
#define LOCPROJECT_PARTICLEFILTER_H

#include "Particle.h"
#include "boost/asio.hpp" // asio
#include "boost/thread.hpp"
#include "boost/function.hpp" // boost::function
#include "boost/bind.hpp" // boost:;bind
#include "../Pose/TfMatList.h"
#include "../util/Parameter.h"
#include "../UI/UIManager.h"
#include "boost/thread/recursive_mutex.hpp" // recursive mutex?
//#include "../Math/Random.h"

class ParticleFilter {
private:
    static TfMatList *tfMatList_ptr;
    static Parameter *parameter_ptr;
    static UIManager *uiManager_ptr;

    ParticleFilter() {}
    ParticleFilter(const ParticleFilter& other) {}


    ~ParticleFilter() {
        deinit();
        delete timer_;
        delete thread_;
    }

    // thread and timing related variables
    int timer_interval;
    boost::asio::deadline_timer* timer_;
    boost::thread* thread_;
    bool threadRunning_;
    bool isInit;


    //PoseGraph* graph_ptr;

    boost::recursive_mutex m_guard_particle;
    //boost::recursive_mutex m_guard_task;

    // Random Util
    //RandomUtil rand_util;

    // filter structures
    std::vector<ParticlePtr> particles;// particles?
    PosePtr pose_for_traj_ptr;

    boost::recursive_mutex m_guard_task;

    // position of ap
    double ap_x;
    double ap_y;
    double ap_z;

public:
    static ParticleFilter* getInstance()
    {
        static ParticleFilter filter;
        return &filter;
    }

    void init(int timer_hz);
    void deinit();
    static void start();
    void thread_callback();
    void periodic_task();

    // callback
    boost::function<void ()> callback_func;
    void initParticleCallback();
    void filteringCallback();

    // filter related methods
    // 1. initial particles
    void initParticles(double t);


    bool &threadRunning() { return threadRunning_; }
    boost::thread* &thread() { return thread_; }
};


#endif //LOCPROJECT_PARTICLEFILTER_H
