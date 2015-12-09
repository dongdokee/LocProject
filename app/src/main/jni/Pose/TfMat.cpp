//
// Created by dongdokee on 2015-11-18.
//

#include "TfMat.h"
#include "boost/make_shared.hpp"
#include "boost/shared_ptr.hpp"


TfMat::TfMat() : rel_pose_(4, 4), isStep(false), time_(0) {
    rel_pose_.assign(IdentityMatrix(4));
}

TfMat::TfMat(bool isStep_, TIMESTAMP_T time_val) : rel_pose_(4, 4), isStep(isStep_), time_(time_val) {
    rel_pose_.assign(IdentityMatrix(4));
}

TfMat::TfMat(Matrix &rel_pose_mat, TIMESTAMP_T time_val) : rel_pose_(4, 4), isStep(false), time_(time_val) {
    rel_pose_.assign(rel_pose_mat);
}
TfMat::TfMat(Matrix &rot, Vector &trans, TIMESTAMP_T time_val) : rel_pose_(4, 4), isStep(false), time_(time_val) {
    subrange(rel_pose_, 0, 3, 0, 3) = rot;
    rel_pose_(0, 3) = trans(0);
    rel_pose_(1, 3) = trans(1);
    rel_pose_(2, 3) = trans(2);
    rel_pose_(3, 3) = 1;
    rel_pose_(3, 0) = 0;
    rel_pose_(3, 1) = 0;
    rel_pose_(3, 2) = 0;
}
TfMat::TfMat(Matrix &rot, COORDINATE_T x, COORDINATE_T y, COORDINATE_T z, TIMESTAMP_T time_val) : rel_pose_(4, 4), isStep(false), time_(time_val) {
    subrange(rel_pose_, 0, 3, 0, 3) = rot;
    rel_pose_(0, 3) = x;
    rel_pose_(1, 3) = y;
    rel_pose_(2, 3) = z;
    rel_pose_(3, 3) = 1;
    rel_pose_(3, 0) = 0;
    rel_pose_(3, 1) = 0;
    rel_pose_(3, 2) = 0;
    //LOGD("TFMAT CONSTRUCTOR %lf/  %lf %lf %lf %lf / %lf %lf %lf %lf / %lf %lf %lf %lf / %lf %lf %lf %lf", time_val, rel_pose_(0, 0), rel_pose_(0, 1), rel_pose_(0, 2), rel_pose_(0, 3), rel_pose_(1, 0), rel_pose_(1, 1), rel_pose_(1, 2), rel_pose_(1, 3), rel_pose_(2, 0), rel_pose_(2, 1), rel_pose_(2, 2), rel_pose_(2, 3), rel_pose_(3, 0), rel_pose_(3, 1), rel_pose_(3, 2), rel_pose_(3, 3));
}

TfMat::TfMat(const TfMat &obj) {
    rel_pose_ = obj.rel_pose_const();
    time_ = obj.time_const();
    isStep = obj.getIsStep_const();
}

TfMat TfMat::integrateGyro(TIMESTAMP_T prev_t, GyroData &gyroData) {
    TIMESTAMP_T cur_t = gyroData.time();
    TIMESTAMP_T dT = (cur_t - prev_t);


    Vector gyro(3);
    gyro(0) = gyroData.x();
    gyro(1) = gyroData.y();
    gyro(2) = gyroData.z();

    double omegaMagnitude = norm_2(gyro);

    if (omegaMagnitude > 0.001)
    {
        gyro /= omegaMagnitude; // normalization
    }

    double thetaOverTwo = omegaMagnitude * dT / 2.0;
    double sinThetaOverTwo = sin(thetaOverTwo);
    double cosThetaOverTwo = cos(thetaOverTwo);

    Vector deltaRotateVector(4);
    deltaRotateVector(0) = sinThetaOverTwo * gyro(0);
    deltaRotateVector(1) = sinThetaOverTwo * gyro(1);
    deltaRotateVector(2) = sinThetaOverTwo * gyro(2);
    deltaRotateVector(3) = cosThetaOverTwo;

    Matrix R = getRotationMatrixFromVector(deltaRotateVector);

    //LOGD("GYRO INTEG time:%lf data:%lf@%lf@%lf / %lf %lf %lf / %lf %lf %lf / %lf %lf %lf", gyroData.time(), gyroData.x(), gyroData.y(), gyroData.z(), R(0, 0), R(0, 1), R(0, 2), R(1, 0), R(1, 1), R(1, 2), R(2, 0), R(2, 1), R(2, 2));

    return TfMat(R, (COORDINATE_T)0, (COORDINATE_T)0, (COORDINATE_T)0, gyroData.time());
}


Matrix TfMat::getRotationMatrixFromVector(Vector rotationVector)
{
    double q0 = rotationVector(3);
    double q1 = rotationVector(0);
    double q2 = rotationVector(1);
    double q3 = rotationVector(2);

    double sq_q1 = 2 * q1 * q1;
    double sq_q2 = 2 * q2 * q2;
    double sq_q3 = 2 * q3 * q3;
    double q1_q2 = 2 * q1 * q2;
    double q3_q0 = 2 * q3 * q0;
    double q1_q3 = 2 * q1 * q3;
    double q2_q0 = 2 * q2 * q0;
    double q2_q3 = 2 * q2 * q3;
    double q1_q0 = 2 * q1 * q0;

    Matrix R(3, 3);
    R(0,0) = 1 - sq_q2 - sq_q3;
    R(0,1) = q1_q2 - q3_q0;
    R(0,2) = q1_q3 + q2_q0;

    R(1,0) = q1_q2 + q3_q0;
    R(1,1) = 1 - sq_q1 - sq_q3;
    R(1,2) = q2_q3 - q1_q0;

    R(2,0) = q1_q3 - q2_q0;
    R(2,1) = q2_q3 + q1_q0;
    R(2,2) = 1 - sq_q1 - sq_q2;

    return R;
}

void TfMat::setStepMatrix(COORDINATE_T step_length) {
    rel_pose_.assign(IdentityMatrix(4));
    rel_pose_(2, 3) = -step_length; // ? or step_length
}

TfMat TfMat::stepMat(TIMESTAMP_T time_val) {
    return TfMat(true, time_val);
}

TfMatPtr TfMat::make() {
    return boost::make_shared<TfMat>();
}
TfMatPtr TfMat::make(bool isStep_, TIMESTAMP_T time_val) {
    return boost::make_shared<TfMat>(isStep_, time_val);
}
TfMatPtr TfMat::make(Matrix& rel_pose_mat, TIMESTAMP_T time_val) {
    return boost::make_shared<TfMat>(rel_pose_mat, time_val);
}
TfMatPtr TfMat::make(Matrix& rot, Vector& trans, TIMESTAMP_T time_val) {
    return boost::make_shared<TfMat>(rot, trans, time_val);
}
TfMatPtr TfMat::make(Matrix& rot, COORDINATE_T x, COORDINATE_T y, COORDINATE_T z, TIMESTAMP_T time_val) {
    return boost::make_shared<TfMat>(rot, x, y, z, time_val);
}
TfMatPtr TfMat::make(TfMat &obj) {
    return boost::make_shared<TfMat>(obj);
}

void TfMat::logging() {
    LOGD("TfMat %lf / %lf %lf %lf %lf / %lf %lf %lf %lf / %lf %lf %lf %lf / %lf %lf %lf %lf", time_,  rel_pose_(0, 0), rel_pose_(0, 1), rel_pose_(0, 2), rel_pose_(0, 3), rel_pose_(1, 0), rel_pose_(1, 1), rel_pose_(1, 2), rel_pose_(1, 3), rel_pose_(2, 0), rel_pose_(2, 1), rel_pose_(2, 2), rel_pose_(2, 3), rel_pose_(3, 0), rel_pose_(3, 1), rel_pose_(3, 2), rel_pose_(3, 3));
}