//
// Created by dongdokee on 2015-11-03.
//

#include "Particle.h"

TfMatList *Particle::tfMatList_ptr = TfMatList::getInstance();

ParticleTrace::ParticleTrace(TIMESTAMP_T t, COORDINATE_T x, COORDINATE_T y, RSSDATA_T rss) : boost::tuple<TIMESTAMP_T , COORDINATE_T , COORDINATE_T , RSSDATA_T>(t, x, y, rss)
{

}
void ParticleTrace::get_data(TIMESTAMP_T &t, COORDINATE_T &x, COORDINATE_T &y, RSSDATA_T &rss)
{
    t = (*this).get<0>();
    x = (*this).get<1>();
    y = (*this).get<2>();
    rss = (*this).get<3>();
}
TIMESTAMP_T ParticleTrace::t()
{
    return (*this).get<0>();
}
COORDINATE_T ParticleTrace::x()
{
    return (*this).get<1>();
}
COORDINATE_T ParticleTrace::y()
{
    return (*this).get<2>();
}
RSSDATA_T ParticleTrace::rss()
{
    return (*this).get<3>();
}
void ParticleTrace::set_data(TIMESTAMP_T t_val, COORDINATE_T x_val, COORDINATE_T y_val, RSSDATA_T rss_val)
{
    (*this).get<0>() = t_val;
    (*this).get<1>() = x_val;
    (*this).get<2>() = y_val;
    (*this).get<3>() = rss_val;
}



Particle::Particle() {}
Particle::Particle(const Particle& other) {}
Particle::~Particle() {}

void Particle::init_particle(TIMESTAMP_T t, COORDINATE_T x_val, COORDINATE_T y_val, COORDINATE_T z_val, RSSDATA_T rss, COORDINATE_T step_length_, double visual_scale_, double weight_)
{
    Matrix R(3, 3);
    R(0, 0) = 1;
    R(0, 1) = 0;
    R(0, 2) = 0;
    R(1, 0) = 0;
    R(1, 1) = 0;
    R(1, 2) = -1;
    R(2, 0) = 0;
    R(2, 1) = 1;
    R(2, 2) = 0;

    pose_ptr = boost::make_shared<Pose>(t, R, x_val, y_val, z_val, 0);

    // push trace
    confirm(t, x_val, y_val, rss);
    //last_updated_t = t;

    this->step_length_ = step_length_;
    visual_scale = visual_scale_;

    weight = weight_;
}

// transit
void Particle::transit(TfMat& tf, bool is_step)
{
    if (is_step)
        tf.setStepMatrix(step_length_);
    pose_ptr->applyTF(tf);
}

void Particle::measure_weight()
{
    //// to be implemented
}

void Particle::confirm(TIMESTAMP_T t, COORDINATE_T x, COORDINATE_T y, RSSDATA_T rss )
{
    trace_.push_back( ParticleTrace(t, x, y, rss) );
    x_traj_.push_back(x);
    y_traj_.push_back(y);
    last_updated_t = t;
}