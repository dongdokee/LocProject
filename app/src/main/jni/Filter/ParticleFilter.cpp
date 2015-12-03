//
// Created by dongdokee on 2015-11-03.
//

#include "ParticleFilter.h"
#include "../util/log.h"
#include "../Math/Random.h"
//#include "../Visualizer/draw_callback.h"
//#include "../callback/jni_stuff.h"

TfMatList *ParticleFilter::tfMatList_ptr = TfMatList::getInstance();
Parameter *ParticleFilter::parameter_ptr = Parameter::getInstance();

void ParticleFilter::init(int timer_hz) {
    threadRunning = false;
    isInit = false;

    // set timer interval
    timer_interval = (int)(1000 / (double)timer_hz);
    callback_func = boost::bind(&ParticleFilter::initParticleCallback, this);
}
void ParticleFilter::deinit() {
    threadRunning = false;
    isInit = false;
}
void ParticleFilter::start() {
    thread = new boost::thread(boost::bind(&ParticleFilter::thread_callback, this));
}

void ParticleFilter::thread_callback() {
    LOGD("ParticleFilter thread started");
    threadRunning = true;
    boost::asio::io_service io;

    timer_ = new boost::asio::deadline_timer(io);
    // set interval
    timer_->expires_from_now(boost::posix_time::milliseconds(timer_interval));
    timer_->async_wait(boost::bind(&ParticleFilter::periodic_task, this));

    // run timer
    io.run();
    LOGD("ParticleFilter thread killed");
}
void ParticleFilter::periodic_task() {
    if (threadRunning) {
        LOGD("ParticleFilter thread task performed");
        timer_->expires_from_now(boost::posix_time::milliseconds(timer_interval));
        timer_->async_wait(boost::bind(&ParticleFilter::periodic_task, this));
    }

    callback_func();

    //boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_particle);
    // perform particle filtering
    // 1. transit particles

    // 2. weight particles

    // 3. (resampling?)

    // 4. draw in UI
    // callback to map in JAVA
}

void ParticleFilter::initParticleCallback()
{
    initParticles(0.0);
    bool init_done = true;
    if (init_done) {
        isInit = true;
        callback_func = boost::bind(&ParticleFilter::filteringCallback, this);

        ap_x = 0.0;
        ap_y = 0.0;
        ap_z = parameter_ptr->default_height();
        LOGD("ParticleFilter initialization done");
    }
}
void ParticleFilter::filteringCallback()
{
    LOGD("ParticleFilter performing drawing ");

    // 1. transit particles


    // 2. weight particles

    // 3. resample particle?


    draw();
}

void ParticleFilter::initParticles(double t) {
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_particle);

    double map_width = parameter_ptr->map_width();
    double map_height = parameter_ptr->map_height();
    COORDINATE_T default_height = parameter_ptr->default_height();
    int num_particles = parameter_ptr->num_particles();

    std::vector<double> xs = Random::drawUniform(-map_width/2, map_width/2, num_particles);
    std::vector<double> ys = Random::drawUniform(-map_height/2, map_height/2, num_particles);
    for (int i= 0 ; i< num_particles ; i++)
    {
        ParticlePtr new_ptr = boost::make_shared<Particle>();

        //z = DEFAULT_HEIGHT;

        double rss = 0;
        double step_length = 0;

        //LOGD("%lf %lf", xs[i], ys[i]);

        new_ptr->init_particle(t, xs[i], ys[i], default_height, rss, step_length, -1, 0);

        particles.push_back( new_ptr ); // (double t, double x, double y, double z, double rss, double step_length_, double visual_scale_, double weight_)
    }
}
void ParticleFilter::transitParticles() {
    for (int i = 0 ; i < particles.size() ; i++)
    {
        particles[i]->transit();
    }
}
void ParticleFilter::weightParticles() {
    for (int i = 0 ; i < particles.size() ; i++)
    {
        particles[i]->measure_weight();
    }
}
void ParticleFilter::resampleParticles() {

}

void ParticleFilter::draw()
{
    //draw_PF(particles, ap_x, ap_y);
}