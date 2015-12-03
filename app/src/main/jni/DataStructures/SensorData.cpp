//
// Created by dongdokee on 2015-10-26.
//

#include "SensorData.h"
#include "boost/make_shared.hpp" // make shared

/*ID_T AccelData::id_count = 0;
ID_T GyroData::id_count = 0;
ID_T CompassData::id_count = 0;
ID_T GravityData::id_count = 0;
ID_T FrameData::id_count = 0;
ID_T RSSData::id_count = 0;*/
ID_T SensorData::id_count = 0;



SensorData::SensorData() : id_(id_count++), time_(0) {}
SensorData::SensorData(TIMESTAMP_T t) : id_(id_count++), time_(t) {}
SensorData::SensorData(ID_T id_val, TIMESTAMP_T t) : id_(id_val), time_(t) {}
SensorData::~SensorData() {
    LOGD("id %d removed", id());
}

IMUData::IMUData() : SensorData(), x_(0), y_(0), z_(0) { }
IMUData::IMUData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) : SensorData(t), x_(x_val), y_(y_val), z_(z_val) { }
IMUData::IMUData(IMU_TYPE type_val, TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) : type_(type_val), SensorData(t), x_(x_val), y_(y_val), z_(z_val) {}

AccelData::AccelData() : IMUData() { }
AccelData::AccelData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) : IMUData(ACCEL_TYPE, t, x_val, y_val, z_val) {}

GyroData::GyroData() : IMUData() { }
GyroData::GyroData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) : IMUData(GYRO_TYPE, t, x_val, y_val, z_val) { }

CompassData::CompassData() : IMUData() { }
CompassData::CompassData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) : IMUData(COMPASS_TYPE, t, x_val, y_val, z_val) { }

GravityData::GravityData() : IMUData() { }
GravityData::GravityData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) : IMUData(GRAVITY_TYPE, t, x_val, y_val, z_val) { }

AccelDataPtr AccelData::make(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) {
    return boost::make_shared<AccelData>(t, x_val, y_val, z_val);
}

GyroDataPtr GyroData::make(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) {
    return boost::make_shared<GyroData>(t, x_val, y_val, z_val);
}

CompassDataPtr CompassData::make(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) {
    return boost::make_shared<CompassData>(t, x_val, y_val, z_val);
}

GravityDataPtr GravityData::make(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val) {
    return boost::make_shared<GravityData>(t, x_val, y_val, z_val);
}