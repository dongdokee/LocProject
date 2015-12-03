//
// Created by dongdokee on 2015-10-27.
//

#ifndef LOCPROJECT_SENSORDATASTORAGE_H
#define LOCPROJECT_SENSORDATASTORAGE_H

#include <vector> // std::vector
//#include "boost/heap/priority_queue.hpp" // heap?
#include "boost/shared_ptr.hpp" // shared_ptr ?
#include "boost/thread/recursive_mutex.hpp" // recursive mutex?
#include "boost/make_shared.hpp" // make shared
#include "SensorData.h"
#include "../util/log.h"
//#include "boost/heap/fibonacci_heap.hpp"
#include "boost/heap/priority_queue.hpp"
//#include "boost/functional.hpp" // boost::binary_function

//using namespace std;
//using namespace boost::heap;
//using namespace boost;

struct temporal_compare_imu {
    bool operator()(const IMUDataPtr& p1, const IMUDataPtr& p2) const {
        return p1->time() > p2->time();
    }
};


class SensorDataStorage {
private:
    SensorDataStorage();
    SensorDataStorage(const SensorDataStorage& other);
    ~SensorDataStorage();

    // locks
    /*boost::recursive_mutex m_guard_accel;
    boost::recursive_mutex m_guard_gyro;
    boost::recursive_mutex m_guard_compass;
    boost::recursive_mutex m_guard_gravity;
    boost::recursive_mutex m_guard_frame;
    boost::recursive_mutex m_guard_rss;*/

    boost::recursive_mutex m_guard_imu;
    boost::recursive_mutex m_guard_frame;
    boost::recursive_mutex m_guard_rss;

    // data storage
    /*std::vector<AccelDataPtr> accel_array;
    std::vector<GyroDataPtr> gyro_array;
    std::vector<CompassDataPtr > compass_array;
    std::vector<GravityDataPtr > gravity_array;
    std::vector<FrameDataPtr> frame_array;
    std::vector<RSSDataPtr> rss_array;*/

    boost::heap::priority_queue<IMUDataPtr, boost::heap::compare<temporal_compare_imu> > imu_array;
    std::vector<FrameDataPtr> frame_array;
    std::vector<RSSDataPtr> rss_array;


public:
    static SensorDataStorage* getInstance();
    void resetInstance();

    void push_accel(TIMESTAMP_T t, IMUDATA_T x, IMUDATA_T y, IMUDATA_T z);
    void push_gyro(TIMESTAMP_T t, IMUDATA_T x, IMUDATA_T y, IMUDATA_T z);
    void push_compass(TIMESTAMP_T t, IMUDATA_T x, IMUDATA_T y, IMUDATA_T z);
    void push_gravity(TIMESTAMP_T t, IMUDATA_T x, IMUDATA_T y, IMUDATA_T z);

    std::vector<IMUDataPtr> pop_imu();

    /* debug */
    void test();
};


#endif //LOCPROJECT_SENSORDATASTORAGE_H
