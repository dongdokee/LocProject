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
    ParticleTrace(TIMESTAMP_T t, COORDINATE_T x, COORDINATE_T y, RSSDATA_T rss) : boost::tuple<TIMESTAMP_T , COORDINATE_T , COORDINATE_T , RSSDATA_T>(t, x, y, rss) {}
    void get_data(TIMESTAMP_T &t, COORDINATE_T &x, COORDINATE_T &y, RSSDATA_T &rss)
    {
        t = (*this).get<0>();
        x = (*this).get<1>();
        y = (*this).get<2>();
        rss = (*this).get<3>();
    }
    TIMESTAMP_T t()
    {
        return (*this).get<0>();
    }
    COORDINATE_T x()
    {
        return (*this).get<1>();
    }
    COORDINATE_T y()
    {
        return (*this).get<2>();
    }
    RSSDATA_T rss()
    {
        return (*this).get<3>();
    }
    void set_data(TIMESTAMP_T t_val, COORDINATE_T x_val, COORDINATE_T y_val, RSSDATA_T rss_val)
    {
        (*this).get<0>() = t_val;
        (*this).get<1>() = x_val;
        (*this).get<2>() = y_val;
        (*this).get<3>() = rss_val;
    }
};

class Particle {
private:
    static TfMatList *tfMatList_ptr;
    // member variables
    // 1. state variables
    TIMESTAMP_T t_;
    //COORDINATE_T *x_ptr;
    //COORDINATE_T *y_ptr;
    //COORDINATE_T *z_ptr; // height?

    PosePtr pose_ptr; // contains x, y, z, and R ?    ( imu => world transformations )

    COORDINATE_T step_length;
    double visual_scale;

    TIMESTAMP_T last_updated_t;
    double weight;

    std::vector<ParticleTrace> trace;


public:
    // constructors
    Particle() {
    }
    Particle(const Particle& other) {}
    ~Particle() {}



    // pose_graph node number
    //vertex_descr_type node_num;

    // interface functions
    COORDINATE_T x() { return pose_ptr->x(); }
    COORDINATE_T y() { return pose_ptr->y(); }
    COORDINATE_T z() { return pose_ptr->z(); }

    void init_particle(TIMESTAMP_T t, COORDINATE_T x_val, COORDINATE_T y_val, COORDINATE_T z_val, double rss, COORDINATE_T step_length_, double visual_scale_, double weight_)
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

        //Vector trans(3);
        //trans(0) = x_val;
        //trans(1) = y_val;
        //trans(2) = z_val;

        //this->x = x;
        //this->y = y;
        //this->z = z;
        //pose_ptr = boost::make_shared<Pose>(R, trans, Matrix(3, 3));
        pose_ptr = boost::make_shared<Pose>(t, R, x_val, y_val, z_val, 0);
        //TIMESTAMP_T t, Matrix& rot, COORDINATE_T world_x, COORDINATE_T world_y, COORDINATE_T world_z, TIMESTAMP_T prev_rot_time

        // push trace
        trace.push_back( ParticleTrace(t, x_val, y_val, rss) );
        last_updated_t = t;

        step_length = step_length_;
        visual_scale = visual_scale_;

        weight = weight_;
        //node_num = PoseGraph::getInstance()->get_init_node();
    }

    // functions related to pose

    //void get_position(double &x, double &y, double &z)
    //{
//        pose_ptr->decompose(x, y, z);
//    }

    // transit
    void transit()
    {
        std::vector<TfMatPtr> tfmat_array = tfMatList_ptr->pop_imu_tfmat();

        for (int i = 0 ; i < tfmat_array.size() ; i++)
        {
            TfMatPtr tfmat_ptr = tfmat_array[i];

            if (tfmat_ptr->getIsStep())
                tfmat_ptr->setStepMatrix(step_length);

            // apply it to pose
            pose_ptr->applyTF(*tfmat_ptr);
        }
    }

    void measure_weight()
    {
        //// to be implemented
    }

};

typedef boost::shared_ptr<Particle> ParticlePtr;


#endif //LOCPROJECT_PARTICLE_H
