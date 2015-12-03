//
// Created by dongdokee on 2015-11-18.
//

#ifndef LOCPROJECT_COORDINATESYSTEM_H
#define LOCPROJECT_COORDINATESYSTEM_H

#include "../DataStructures/SensorData.h"
#include "../Math/LinearAlgebra.h"



// define relationship among  IMU    CAMERA     WORLD
class CoordinateSystem {
private:
public:
    static Matrix getRotFromCompass(CompassData& compassData, GravityData& gravityData);
};


#endif //LOCPROJECT_COORDINATESYSTEM_H
