//
// Created by dongdokee on 2015-11-20.
//

#ifndef LOCPROJECT_PARAMETER_H
#define LOCPROJECT_PARAMETER_H

#include "types.h"

class Parameter {
private:
    Parameter();

    bool isLoad;

    /* parameters */
    TIMESTAMP_T step_delta_t_thresh_;
    IMUDATA_T step_delta_mag_thresh_;
    int num_particles_;
    COORDINATE_T default_height_;
    COORDINATE_T map_width_;
    COORDINATE_T map_height_;

    int inertial_tracker_freq_;
    int memory_manager_freq_;
    double stale_thresh_;

    COORDINATE_T step_length_mean_;
    COORDINATE_T step_length_sigma_;

    int particle_filter_freq_;
public:
    static Parameter* getInstance();
    void loadDefault();
    void loadFromFile()
    {
        // not implemented yet
        isLoad = true;
    }

    /* parameters interface */
    TIMESTAMP_T &step_delta_t_thresh() { return step_delta_t_thresh_; }
    IMUDATA_T &step_delta_mag_thresh() { return step_delta_mag_thresh_; }
    int &num_particles() { return num_particles_; }
    COORDINATE_T &default_height() { return default_height_; }
    COORDINATE_T &map_width() { return map_width_; }
    COORDINATE_T &map_height() { return map_height_; }

    int &inertial_tracker_freq() { return inertial_tracker_freq_; }
    int &memory_manager_freq() { return memory_manager_freq_; }
    double &stale_thresh() { return stale_thresh_; }

    COORDINATE_T &step_length_mean() { return step_length_mean_; }
    COORDINATE_T &step_length_sigma() { return step_length_sigma_; }

    int &particle_filter_freq() { return particle_filter_freq_; }
};


#endif //LOCPROJECT_PARAMETER_H
