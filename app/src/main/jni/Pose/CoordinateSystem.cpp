//
// Created by dongdokee on 2015-11-18.
//

#include "CoordinateSystem.h"

Matrix CoordinateSystem::getRotFromCompass(CompassData& compassData, GravityData& gravityData) {
    Vector compass_vector(3);
    compass_vector(0) = compassData.x();
    compass_vector(1) = compassData.y();
    compass_vector(2) = compassData.z();
    Vector gravity_vector(3);
    gravity_vector(0) = gravityData.x();
    gravity_vector(1) = gravityData.y();
    gravity_vector(2) = gravityData.z();

    Vector East(3);
    cross_prod(compass_vector, gravity_vector, East); // East = cross(compass_vector, gravity_vector)
    double normEast = norm_2(East);

    if (normEast < 0)
        return IdentityMatrix(3);

    East /= normEast; // normalization
    gravity_vector /= norm_2(gravity_vector);

    Vector North(3);
    cross_prod(gravity_vector, East, North); // North = cross(gravity_vector, East)

    Matrix rotmat(3, 3);
    row(rotmat, 0) = East;
    row(rotmat, 1) = North;
    row(rotmat, 2) = gravity_vector;

    return Matrix(rotmat);
}
