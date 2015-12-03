//
// Created by dongdokee on 2015-11-18.
//

#include "Pose.h"
#include "boost/make_shared.hpp"

Pose::Pose() : time_(0), matrix_(4, 4), prev_rot_t_(0) {
    matrix_.assign(IdentityMatrix(4));
}
Pose::Pose(TIMESTAMP_T t, Matrix &rot, Vector &tvec, TIMESTAMP_T prev_rot_time) : time_(t), matrix_(4, 4), prev_rot_t_(prev_rot_time) {
    subrange(matrix_, 0, 2, 0, 2) = rot;
    matrix_(0, 3) = tvec(0);
    matrix_(1, 3) = tvec(1);
    matrix_(2, 3) = tvec(2);
    matrix_(3, 3) = 1;
    matrix_(3, 0) = 0;
    matrix_(3, 1) = 0;
    matrix_(3, 2) = 0;
}
// imu to world rotation matrix!
Pose::Pose(TIMESTAMP_T t, Matrix &rot, COORDINATE_T world_x, COORDINATE_T world_y, COORDINATE_T world_z, TIMESTAMP_T prev_rot_time) : time_(t), matrix_(4, 4), prev_rot_t_(prev_rot_time) {
    subrange(matrix_, 0, 2, 0, 2) = rot;
    matrix_(0, 3) = world_x;
    matrix_(1, 3) = world_y;
    matrix_(2, 3) = world_z;
    matrix_(3, 3) = 1;
    matrix_(3, 0) = 0;
    matrix_(3, 1) = 0;
    matrix_(3, 2) = 0;
}

Pose::Pose(const Pose& pose_obj) {
    time_ = pose_obj.time_const();
    matrix_ = pose_obj.matrix_const();
    prev_rot_t_ = pose_obj.prev_rot_t_const();
}
//void Pose::decompose_world_coordinate(COORDINATE_T &x, COORDINATE_T &y, COORDINATE_T &z) {
//    x = matrix_(0, 3);
//    y = matrix_(1, 3);
//    z = matrix_(2, 3);
//}
Matrix Pose::getRotation() {
    return subrange(matrix_, 0, 2, 0, 2);
}
void Pose::applyTF(TfMat &tfmat) {
    prod(matrix_, tfmat.rel_pose(), matrix_); // matrix = matrix * rel_pose
}



PosePtr Pose::make(TIMESTAMP_T t, Matrix& rot, Vector& tvec, TIMESTAMP_T prev_rot_time) {
    return boost::make_shared<Pose>(t, rot, tvec, prev_rot_time);
}
PosePtr Pose::make(TIMESTAMP_T t, Matrix& rot, COORDINATE_T world_x, COORDINATE_T world_y, COORDINATE_T world_z, TIMESTAMP_T prev_rot_time) {
    return boost::make_shared<Pose>(t, rot,world_x, world_y, world_z, prev_rot_time);
}

PosePtr Pose::make(Pose& pose_obj) {
    return boost::make_shared<Pose>(pose_obj);
}