//
// Created by dongdokee on 2015-11-18.
//

#ifndef LOCPROJECT_TFMAT_H
#define LOCPROJECT_TFMAT_H

#include "../util/types.h"
#include "../Math/LinearAlgebra.h"
#include "../DataStructures/SensorData.h"

class TfMat;
typedef boost::shared_ptr<TfMat> TfMatPtr;


// SE(3) transformation matrix
class TfMat {
private:
    Matrix rel_pose_;

    TIMESTAMP_T time_;
    bool isStep;

    static Matrix getRotationMatrixFromVector(Vector rotationVector);
public:
    TfMat();
    TfMat(bool isStep_, TIMESTAMP_T time_val = 0);
    TfMat(Matrix& rel_pose_mat, TIMESTAMP_T time_val = 0);
    TfMat(Matrix& rot, Vector& trans, TIMESTAMP_T time_val = 0);
    TfMat(Matrix& rot, COORDINATE_T x, COORDINATE_T y, COORDINATE_T z, TIMESTAMP_T time_val = 0);
    TfMat(const TfMat& obj);

    Matrix& rel_pose() { return rel_pose_; }
    TIMESTAMP_T &time() { return time_; }
    bool &getIsStep() { return isStep; }

    Matrix rel_pose_const() const { return rel_pose_; }
    TIMESTAMP_T time_const() const { return time_; }
    bool getIsStep_const() const { return isStep; }

    void setStepMatrix(COORDINATE_T step_length);

    static TfMat integrateGyro(TIMESTAMP_T prev_t, GyroData& gyroData);
    static TfMat stepMat(TIMESTAMP_T time_val);

    static TfMatPtr make();
    static TfMatPtr make(bool isStep_, TIMESTAMP_T time_val = 0);
    static TfMatPtr make(Matrix& rel_pose_mat, TIMESTAMP_T time_val = 0);
    static TfMatPtr make(Matrix& rot, Vector& trans, TIMESTAMP_T time_val = 0);
    static TfMatPtr make(Matrix& rot, COORDINATE_T x, COORDINATE_T y, COORDINATE_T z, TIMESTAMP_T time_val = 0);
    static TfMatPtr make(TfMat& obj);

    void logging();

};


#endif //LOCPROJECT_TFMAT_H
