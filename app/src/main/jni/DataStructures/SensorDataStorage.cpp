//
// Created by dongdokee on 2015-10-27.
//

#include "SensorDataStorage.h"
#include "boost/thread.hpp" // lock guard?

SensorDataStorage::SensorDataStorage()  { }
SensorDataStorage::SensorDataStorage(const SensorDataStorage &other)  {
    /*accel_array = other.get_accel();
    gyro_array = other.get_gyro();
    compass_array = other.get_compass();
    gravity_array = other.get_gravity();*/
}
SensorDataStorage::~SensorDataStorage() {
    resetInstance();
}

SensorDataStorage* SensorDataStorage::getInstance() {
    static SensorDataStorage stor;
    return &stor;
}

// clear all
void SensorDataStorage::resetInstance() {
    /*{
        boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_accel);
        accel_array.clear();
    }
    {
        boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_gyro);
        gyro_array.clear();
    }
    {
        boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_compass);
        compass_array.clear();
    }
    {
        boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_gravity);
        gravity_array.clear();
    }
    {
        boost::lock_guard<boost::recursive_mutex> lock_frame(m_guard_frame);
        frame_array.clear();
    }
    {
        boost::lock_guard<boost::recursive_mutex> lock_rss(m_guard_rss);
        rss_array.clear();
    }*/
}

void SensorDataStorage::push_accel(TIMESTAMP_T t, IMUDATA_T x, IMUDATA_T y, IMUDATA_T z) {
    //boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_accel);
    //accel_array.push_back(AccelData::make(t, x, y, z));
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_imu);
    imu_array.push(AccelData::make(t, x, y, z));

}

void SensorDataStorage::push_gyro(TIMESTAMP_T t, IMUDATA_T x, IMUDATA_T y, IMUDATA_T z) {
    //boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_gyro);
    //gyro_array.push_back(GyroData::make(t, x, y, z));
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_imu);
    imu_array.push(GyroData::make(t, x, y, z));
}

void SensorDataStorage::push_compass(TIMESTAMP_T t, IMUDATA_T x, IMUDATA_T y, IMUDATA_T z) {
    //boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_compass);
    //compass_array.push_back(CompassData::make(t, x, y, z));
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_imu);
    imu_array.push(GravityData::make(t, x, y, z));
}

void SensorDataStorage::push_gravity(TIMESTAMP_T t, IMUDATA_T x, IMUDATA_T y, IMUDATA_T z) {
    //boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_gravity);
    //gravity_array.push_back(GravityData::make(t, x, y, z));
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_imu);
    imu_array.push(CompassData::make(t, x, y, z));
}

std::vector<IMUDataPtr> SensorDataStorage::pop_imu() {
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_imu);
    std::vector<IMUDataPtr> result;
    while (!imu_array.empty()) {
        result.push_back( imu_array.top() );
        imu_array.pop();
    }
    return result;
}

void SensorDataStorage::test()
{
    std::vector<IMUDataPtr> ptrs = pop_imu();
    char *type;
    for (int i = 0 ; i < ptrs.size() ; i++)
    {
        switch(ptrs[i]->type()) {
            case ACCEL_TYPE:
                type = "ACCEL";
                break;
            case GYRO_TYPE:
                type = "GYRO";
                break;
            case COMPASS_TYPE:
                type = "COMPASS";
                break;
            case GRAVITY_TYPE:
                type = "GRAVITY";
                break;
            default:
                type = "UNKNOWN";
                break;
        }
        LOGD("%s data id : %d t : %lf x : %lf y : %lf z : %lf", type, ptrs[i]->id(), ptrs[i]->time(), ptrs[i]->x(), ptrs[i]->y(), ptrs[i]->z());
    }
    /*for(int i = 0 ; i < accel_array.size() ; i++)
    {
        LOGD("ACCEL DATA id : %d t : %lf x : %lf y : %lf z : %lf", accel_array[i]->id(), accel_array[i]->time(), accel_array[i]->x(), accel_array[i]->y(), accel_array[i]->z());
    }*/
}