//
// Created by dongdokee on 2015-11-03.
//

#include "ParticleFilter.h"
#include "../util/log.h"
#include "../Math/Random.h"
#include "boost/thread.hpp" // lock guard?
//#include "../Visualizer/draw_callback.h"
//#include "../callback/jni_stuff.h"

TfMatList *ParticleFilter::tfMatList_ptr = TfMatList::getInstance();
Parameter *ParticleFilter::parameter_ptr = Parameter::getInstance();
UIManager *ParticleFilter::uiManager_ptr = UIManager::getInstance();

void ParticleFilter::init(int timer_hz) {
    threadRunning_ = false;
    isInit = false;

    // set timer interval
    timer_interval = (int)(1000 / (double)timer_hz);
    callback_func = boost::bind(&ParticleFilter::initParticleCallback, this);
}
void ParticleFilter::deinit() {
    threadRunning_ = false;
    isInit = false;
}
void ParticleFilter::start() {
    ParticleFilter *filter = ParticleFilter::getInstance();
    if (!filter->threadRunning()) {
        filter->init(parameter_ptr->particle_filter_freq());
        filter->thread() = new boost::thread(boost::bind(&ParticleFilter::thread_callback, filter));
    }
}

void ParticleFilter::thread_callback() {
    LOGD("ParticleFilter thread started");
    threadRunning_ = true;
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
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_task);

    if (threadRunning_) {
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

        pose_for_traj_ptr = Pose::make();
        LOGD("ParticleFilter initialization done");
    }
}
void ParticleFilter::filteringCallback()
{
    LOGD("ParticleFilter performing drawing ");
    bool willViewUpdate = false;
    bool willConfirm = false;

    // for each tf
    std::vector<TfMatPtr> tfmat_array = tfMatList_ptr->pop_imu_tfmat();
    for (int i = 0 ; i < tfmat_array.size() ; i++) {
        TfMatPtr tfmat_ptr = tfmat_array[i];
        if (tfmat_ptr->getIsStep()) {
            willViewUpdate = true;
            willConfirm = true;
        } else {
            willViewUpdate = false;
            willConfirm = false;
        }

        std::vector<COORDINATE_T> all_x;
        std::vector<COORDINATE_T> all_y;

        for (int j = 0 ; j < particles.size() ; j++)
        {
            //1. transit particle
            particles[j]->transit(*tfmat_ptr, willConfirm);

            if (willConfirm)
                particles[j]->confirm(tfmat_ptr->time(), particles[j]->x(), particles[j]->y(), 0);

            if (willViewUpdate)
            {
                all_x.push_back(particles[j]->x());
                all_y.push_back(particles[j]->y());
            }

        }

        // measure weights

        // update views
        double *x, *y;
        int num_elem;
        //std::vector<COORDINATE_T> x_vector, y_vector;
        pose_for_traj_ptr->applyTF(*tfmat_ptr);

        //tfmat_ptr->logging();  // LOGDDDDDDDDDDDDDDDDDDDDDDDDDD
        if (willViewUpdate) {
            // update all view
            num_elem = all_x.size();
            x = &all_x.front();
            y = &all_y.front();

            uiManager_ptr->update_all(x, y, num_elem);


            // update best view
            ParticlePtr best_particle_ptr = particles[0];
//        ParticlePtr best_particle_ptr = ParticlePtr(); // something
            num_elem = best_particle_ptr->trace().size();
            x = &best_particle_ptr->x_traj().front();
            y = &best_particle_ptr->y_traj().front();
            uiManager_ptr->update_best(x, y, num_elem);

            // update trajectory

            uiManager_ptr->update_trajectory(pose_for_traj_ptr->x(), pose_for_traj_ptr->y());
        }


        if (willConfirm)
        {
            // resampling
        }
    }
}

void ParticleFilter::initParticles(double t) {
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_particle);

    double map_width = parameter_ptr->map_width();
    double map_height = parameter_ptr->map_height();
    COORDINATE_T default_height = parameter_ptr->default_height();
    int num_particles = parameter_ptr->num_particles();

    std::vector<double> xs = Random::drawUniform(-map_width/2, map_width/2, num_particles);
    std::vector<double> ys = Random::drawUniform(-map_height/2, map_height/2, num_particles);

    double step_length_mu = parameter_ptr->step_length_mean();
    double step_length_sigma = parameter_ptr->step_length_sigma();

    std::vector<double> step_lengths = Random::drawNormal(step_length_mu, step_length_sigma, num_particles);
    for (int i= 0 ; i< num_particles ; i++)
    {
        ParticlePtr new_ptr = boost::make_shared<Particle>();

        //z = DEFAULT_HEIGHT;

        double rss = 0;
        double step_length = step_lengths[i];

        //LOGD("%lf %lf", xs[i], ys[i]);

        new_ptr->init_particle(t, xs[i], ys[i], default_height, rss, step_length, -1, 0);

        particles.push_back( new_ptr ); // (double t, double x, double y, double z, double rss, double step_length_, double visual_scale_, double weight_)
    }
}

