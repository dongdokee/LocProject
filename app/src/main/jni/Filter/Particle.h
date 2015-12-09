//
// Created by dongdokee on 2015-11-03.
//

#ifndef LOCPROJECT_PARTICLE_H
#define LOCPROJECT_PARTICLE_H

#include "boost/shared_ptr.hpp" // shared-ptr
#include "boost/make_shared.hpp" // make shared
#include <vector>
//#include "../DataStructures/Pose.h"
#include "../util/types.h"
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
//#include "../DataStructures/PoseGraph.h"
#include "../Pose/Pose.h"
#include "../Pose/TfMatList.h"

class ParticleTrace : boost::tuple<TIMESTAMP_T , COORDINATE_T , COORDINATE_T , RSSDATA_T > // t, x, y, rss
{
private:
public:
    ParticleTrace(TIMESTAMP_T t, COORDINATE_T x, COORDINATE_T y, RSSDATA_T rss);
    void get_data(TIMESTAMP_T &t, COORDINATE_T &x, COORDINATE_T &y, RSSDATA_T &rss);
    TIMESTAMP_T t();
    COORDINATE_T x();
    COORDINATE_T y();
    RSSDATA_T rss();
    void set_data(TIMESTAMP_T t_val, COORDINATE_T x_val, COORDINATE_T y_val, RSSDATA_T rss_val);
};

class Particle {
private:
    static TfMatList *tfMatList_ptr;
    // member variables
    // 1. state variables
    TIMESTAMP_T t_;

    PosePtr pose_ptr; // contains x, y, z, and R ?    ( imu => world transformations )

    COORDINATE_T step_length_;
    double visual_scale;

    TIMESTAMP_T last_updated_t;
    double weight;

    std::vector<ParticleTrace> trace_;
    std::vector<COORDINATE_T> x_traj_;
    std::vector<COORDINATE_T> y_traj_;


public:
    // constructors
    Particle() ;
    Particle(const Particle& other);
    ~Particle();



    // pose_graph node number
    //vertex_descr_type node_num;

    // interface functions
    COORDINATE_T x() { return pose_ptr->x(); }
    COORDINATE_T y() { return pose_ptr->y(); }
    COORDINATE_T z() { return pose_ptr->z(); }
    COORDINATE_T &step_length() { return step_length_; }
    std::vector<ParticleTrace> &trace() { return trace_; }

    std::vector<COORDINATE_T> &x_traj() { return x_traj_; }
    std::vector<COORDINATE_T> &y_traj() { return y_traj_; }

    void init_particle(TIMESTAMP_T t, COORDINATE_T x_val, COORDINATE_T y_val, COORDINATE_T z_val, RSSDATA_T rss, COORDINATE_T step_length_, double visual_scale_, double weight_);

    // transit
    void transit(TfMat& tf, bool is_step);
    void measure_weight();
    void confirm(TIMESTAMP_T t, COORDINATE_T x, COORDINATE_T y, RSSDATA_T rss );

};

typedef boost::shared_ptr<Particle> ParticlePtr;


#endif //LOCPROJECT_PARTICLE_H
