//
// Created by dongdokee on 2015-11-18.
//

#ifndef LOCPROJECT_POSE_H
#define LOCPROJECT_POSE_H

#include "../util/types.h"
#include "../Math/LinearAlgebra.h"
#include "TfMat.h"

// pose from IMU to world coordinate system
// SE4 matrix
// required ability
// 1. find world coordinate
// 2. apply transformation matrix

class Pose;

typedef boost::shared_ptr<Pose> PosePtr;


class Pose {
private:
    TIMESTAMP_T time_;
    Matrix matrix_;
    TIMESTAMP_T prev_rot_t_;
public:
    Pose();
    Pose(TIMESTAMP_T t, Matrix& rot, Vector& tvec, TIMESTAMP_T prev_rot_time);
    Pose(TIMESTAMP_T t, Matrix& rot, COORDINATE_T world_x, COORDINATE_T world_y, COORDINATE_T world_z, TIMESTAMP_T prev_rot_time);
    Pose(const Pose& pose_obj);
    TIMESTAMP_T &time() { return time_; }
    TIMESTAMP_T& prev_rot_t() { return prev_rot_t_; }
    Matrix& matrix() { return matrix_; }

    TIMESTAMP_T time_const() const { return time_; }
    TIMESTAMP_T prev_rot_t_const() const { return prev_rot_t_; }
    Matrix matrix_const() const { return matrix_; }
    //void decompose_world_coordinate(COORDINATE_T& x, COORDINATE_T& y, COORDINATE_T& z);
    Matrix getRotation();
    void applyTF(TfMat& tfmat);

    COORDINATE_T x() { return matrix_(0, 3); }
    COORDINATE_T y() { return matrix_(1, 3); }
    COORDINATE_T z() { return matrix_(2, 3); }

    static PosePtr make();
    static PosePtr make(TIMESTAMP_T t, Matrix& rot, Vector& tvec, TIMESTAMP_T prev_rot_time);
    static PosePtr make(TIMESTAMP_T t, Matrix& rot, COORDINATE_T world_x, COORDINATE_T world_y, COORDINATE_T world_z, TIMESTAMP_T prev_rot_time);
    static PosePtr make(Pose& pose_obj);
};


#endif //LOCPROJECT_POSE_H
