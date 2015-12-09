//
// Created by dongdokee on 2015-11-20.
//

#include "Parameter.h"

Parameter::Parameter() {
    isLoad = false;
}

Parameter* Parameter::getInstance() {
    static Parameter parameter;
    return &parameter;
}

void Parameter::loadDefault()
{
    step_delta_t_thresh_ = 0.33;
    step_delta_mag_thresh_ = 2.3;
    num_particles_ = 1000;
    default_height_ = 1.0;
    map_width_ = 30;
    map_height_ = 20;

    inertial_tracker_freq_ = 30;
    memory_manager_freq_ = 5; // 5 second ?
    stale_thresh_ = 10.0; // 10 seconds

    step_length_mean_ = 0.6;
    step_length_sigma_ = 0.02;

    particle_filter_freq_ = 10;

    isLoad = true;


}