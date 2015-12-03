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
//#include "../Math/Random.h"

class ParticleFilter {
private:
    static TfMatList *tfMatList_ptr;
    static Parameter *parameter_ptr;
    ParticleFilter() {}
    ParticleFilter(const ParticleFilter& other) {}


    ~ParticleFilter() {
        deinit();
        delete timer_;
        delete thread;
    }

    // thread and timing related variables
    int timer_interval;
    boost::asio::deadline_timer* timer_;
    boost::thread* thread;
    bool threadRunning;
    bool isInit;


    //PoseGraph* graph_ptr;

    boost::recursive_mutex m_guard_particle;

    // Random Util
    //RandomUtil rand_util;

    // filter structures
    std::vector<ParticlePtr> particles;// particles?
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
    void start();
    void thread_callback();
    void periodic_task();

    // callback
    boost::function<void ()> callback_func;
    void initParticleCallback();
    void filteringCallback();

    // filter related methods
    // 1. initial particles
    void initParticles(double t);
    // 2. transit particles
    void transitParticles();
    // 3. weight particles
    void weightParticles();
    // 4. resampling aprticles
    void resampleParticles();


    // draw map (send command to UI JAVA)
    void draw();
};


#endif //LOCPROJECT_PARTICLEFILTER_H
