//
// Created by dongdokee on 2015-10-26.
//

#ifndef LOCPROJECT_SENSORDATA_H
#define LOCPROJECT_SENSORDATA_H

#include "boost/shared_ptr.hpp"
#include "../util/types.h"

#include "../util/log.h"
//#include "boost/tuple/tuple.hpp"
//#include "boost/tuple/tuple_io.hpp"
//using namespace boost;

class IMUData;
class AccelData;
class GyroData;
class CompassData;
class GravityData;
class FrameData;
class RSSData;

typedef boost::shared_ptr<IMUData> IMUDataPtr;
typedef boost::shared_ptr<AccelData> AccelDataPtr;
typedef boost::shared_ptr<GyroData> GyroDataPtr;
typedef boost::shared_ptr<CompassData> CompassDataPtr;
typedef boost::shared_ptr<GravityData> GravityDataPtr;
typedef boost::shared_ptr<FrameData> FrameDataPtr;
typedef boost::shared_ptr<RSSData> RSSDataPtr;


class SensorData {
private:
    ID_T id_;
    TIMESTAMP_T time_;
    static int id_count;
public:
    SensorData();
    SensorData(TIMESTAMP_T t);
    SensorData(ID_T id_val, TIMESTAMP_T t);
    ~SensorData();
    TIMESTAMP_T& time() { return time_; }
    ID_T& id() { return id_; }
};

class IMUData : public SensorData {
private:
    IMU_TYPE type_;
    IMUDATA_T x_;
    IMUDATA_T y_;
    IMUDATA_T z_;
public:
    IMUData();
    IMUData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
    IMUData(IMU_TYPE type_val, TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
    IMU_TYPE &type() { return type_; }
    IMUDATA_T& x() { return x_; }
    IMUDATA_T& y() { return y_; }
    IMUDATA_T& z() { return z_; }
};

class  AccelData : public IMUData {
public:
    AccelData();
    AccelData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
    static AccelDataPtr make(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
};

class GyroData : public IMUData {
public:
    GyroData();
    GyroData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
    static GyroDataPtr make(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
};

class CompassData : public IMUData {
public:
    CompassData();
    CompassData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
    static CompassDataPtr make(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
};

class GravityData : public IMUData {
public:
    GravityData();
    GravityData(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
    static GravityDataPtr make(TIMESTAMP_T t, IMUDATA_T x_val, IMUDATA_T y_val, IMUDATA_T z_val);
};

class RSSData : public SensorData {
private:
    RSSDATA_T rss_;
public:
    static int id_count;
    RSSDATA_T& rss() { return rss_; }
};

class FrameData : public SensorData {
private:
    // image structure
public:
    static int id_count;
};








/*
class SensorData {
public:
    SensorData() : type(NONE) {}
    SensorData(enum SENSOR_TYPE type_) : type(type_), t(0) {}
    SensorData(enum SENSOR_TYPE type_, double t_) : type(type_), t(t_) {}
    ~SensorData() {
        LOGD("SensorData destructed");
    }
    enum SENSOR_TYPE type;

    double t; // time stamp

    double get_timestamp() { return t; }
    //virtual boost::tuple
    virtual void print() {}
};

class AccelData : public SensorData {
public:
    AccelData() : SensorData(ACCEL), x(0), y(0), z(0) {}
    AccelData(double t_, double x_, double y_, double z_) : SensorData(ACCEL, t_), x(x_), y(y_), z(z_) {}

    double x;
    double y;
    double z;

    virtual void print() {
        LOGD("accel %lf %lf %lf %lf", t, x, y, z);
    }
};

class GyroData : public SensorData {
public:
    GyroData() : SensorData(GYRO), x(0), y(0), z(0) {}
    GyroData(double t_, double x_, double y_, double z_) : SensorData(GYRO, t_), x(x_), y(y_), z(z_) {}

    double x;
    double y;
    double z;

    virtual void print() {
        LOGD("gyro %lf %lf %lf %lf", t, x, y, z);
    }
};

class CompassData : public SensorData {
public:
    CompassData() : SensorData(COMPASS), x(0), y(0), z(0) {}
    CompassData(double t_, double x_, double y_, double z_) : SensorData(COMPASS, t_), x(x_), y(y_), z(z_), grav_x(0), grav_y(0), grav_z(0), grav_set(false) {}
    CompassData(double t_, double x_, double y_, double z_, double grav_x_, double grav_y_, double grav_z_) : SensorData(COMPASS, t_), x(x_), y(y_), z(z_), grav_x(grav_x_), grav_y(grav_y_), grav_z(grav_z_), grav_set(true) {}

    double x;
    double y;
    double z;

    bool grav_set;
    double grav_x;
    double grav_y;
    double grav_z;

    virtual void print() {
        LOGD("compass %lf %lf %lf %lf", t, x, y, z);
    }

    void set_gravity(double x, double y, double z)
    {
        grav_x = x;
        grav_y = y;
        grav_z = z;
    }
};

class GravityData : public SensorData {
public:
    GravityData() : SensorData(GRAVITY), x(0), y(0), z(0) {}
    GravityData(double t_, double x_, double y_, double z_) : SensorData(GRAVITY, t_), x(x_), y(y_), z(z_) {}

    double x;
    double y;
    double z;

    virtual void print() {
        LOGD("gravity %lf %lf %lf %lf", t, x, y, z);
    }
};

class FrameData : public SensorData {
public:
    FrameData() : SensorData(FRAME) {}

    // some type of image defining
};

class RSSData : public SensorData {
public:
    RSSData() : SensorData(RSS), rss(0) {}
    RSSData(double t_, double rss_) : SensorData(RSS, t_), rss(rss_) {}

    double rss;
};

typedef shared_ptr<SensorData> SensorDataPtr; */

#endif //LOCPROJECT_SENSORDATA_H
