//
// Created by dongdokee on 2015-10-26.
//
#include "../util/log.h"
#include "InertialTracker.h"
//#include "../Pose/TfMatList.h"
//#include "../Pose/PoseList.h"

InertialTracker *InertialTracker::instance = nullptr;
UIManager* InertialTracker::uiManager_ptr = UIManager::getInstance();
Parameter* InertialTracker::parameter_ptr = Parameter::getInstance();
TfMatList* InertialTracker::tfmat_list_ptr = TfMatList::getInstance();
//PoseList* InertialTracker::pose_list_ptr = PoseList::getInstance();

InertialTracker* InertialTracker::getInstance() {
    if (instance == nullptr)
        instance = new InertialTracker();

    return instance;
}

InertialTracker::InertialTracker() : step_num_(0), last_gyro_time_(0) {
    init_done_self_ = false;
    init_done_indicator_ = false;
    last_gyro_time_ = 0;
    imu_callback_func = boost::bind(&InertialTracker::init_callback, this, _1); // init callback to initialization callback
}

void InertialTracker::start() {
    InertialTracker *iTracker = InertialTracker::getInstance();
    if (!iTracker->threadRunning()) {
        iTracker->init(parameter_ptr->inertial_tracker_freq());
        iTracker->thread() = new boost::thread(boost::bind(&InertialTracker::thread_callback, iTracker));
    }
}


void InertialTracker::thread_callback() {
    LOGD("inertial tracker thread started interval : %d", timer_interval());
    threadRunning() = true;
    boost::asio::io_service io;

    timer() = new boost::asio::deadline_timer(io);
    // set interval
    timer()->expires_from_now(boost::posix_time::milliseconds(timer_interval()));
    timer()->async_wait(boost::bind(&InertialTracker::periodic_task, this));

    // run timer
    io.run();
}

void InertialTracker::periodic_task() {
    // post synchronization (lock mutex for conditional variable)
    if (threadRunning()) {
        LOGD("inertialTracker thread task performed");
        timer()->expires_from_now(boost::posix_time::milliseconds(timer_interval()));
        timer()->async_wait(boost::bind(&InertialTracker::periodic_task, this));
    }
    LOGD("inertial tracker periodic task performed");

    LOGD("before popping? ");
    std::vector<IMUDataPtr> imus = mStorage()->pop_imu();
    LOGD("imu size : %d", imus.size());
    for (int i = 0 ; i < imus.size() ; i++) {
        imu_callback_func(imus[i]);
    }
}

void InertialTracker::step_event_handler() {
    step_num_++;
    // register pose graph

    // update UI
    LOGD("step detected");
    uiManager_ptr->update_step(step_num_);
}

void InertialTracker::init_pose_list() {
    // generate initial pose and push it to POSE LIST

    //Pose initial_pose = 블라블라블라블라블라븗라 블라 브랒임너ㅣㅏ;랑니;러ㅣㅏ;ㅇㄴ머리ㅏ;ㅇㄴ머라;ㅣㄴㅇ머ㅏ링너마ㅣ;

    //pose_list_ptr->push_imu_pose(initial_pose, true);
}

void InertialTracker::init_callback(IMUDataPtr& imu_ptr) {
    // perform initialization task
    last_gyro_time_ = imu_ptr->time();
    init_done_self_ = true;
    init_pose_list();
    LOGD("self init done");


    // if initialization is done ( this is indicated by outter indicate )
    if (init_done_indicator_ && init_done_self_) {
        imu_callback_func = boost::bind(&InertialTracker::track_callback, this, _1); // init callback to initialization callback
    }
}
void InertialTracker::track_callback(IMUDataPtr& imu_ptr) {
    //LOGD("pointer : %p", imu_ptr.get());
    //LOGD("track callback id %d t %lf", imu_ptr->id(), imu_ptr->time());
    bool isDetect;
    switch(imu_ptr->type()) {
        case ACCEL_TYPE:
            isDetect = stepDetector.pushAndDetect(*imu_ptr);
            if(isDetect) {
                //step_event_handler(
                tfmat_list_ptr->push_imu_pose( TfMat::stepMat( imu_ptr->time() ) );
            }
            break;
        case GYRO_TYPE: {
            // to be implemented ... ... ... ... .... ....
            GyroData *gyro_ptr = static_cast<GyroData *>(imu_ptr.get());
            tfmat_list_ptr->push_imu_pose(TfMat::integrateGyro(last_gyro_time_, *gyro_ptr));
            break;
        }
        default:
            break;
    }
}

/*
void InertialTracker::init(int timer_hz)
{
    // intialize step detector
    //stepDetector.init();

    threadRunning = false;

    isInit = false;
    initial_compass_number = 0;
    initial_compass_data.x = 0;
    initial_compass_data.y = 0;
    initial_compass_data.z = 0;
    initial_compass_data.grav_set = true;
    initial_compass_data.grav_x = 0;
    initial_compass_data.grav_y = 0;
    initial_compass_data.grav_z = 0;
    callback_func = boost::bind(&InertialTracker::initPoseGraphCallback, this, _1);

    // set timer interval
    timer_interval = (int)(1000 / (double)timer_hz);

    inertial_ready = false;
}

void InertialTracker::deinit()
{
    // kill thread?
    threadRunning = false;
    initial_compass_number = 0;
    isInit = false;
}

void InertialTracker::start() {
    // run thread with thread_callback function
    thread = new boost::thread(boost::bind(&InertialTracker::thread_callback, this));
}

// thread callback
void InertialTracker::thread_callback()
{
    LOGD("inertialTracker thread started");
    threadRunning = true;
    boost::asio::io_service io;

    timer_ = new boost::asio::deadline_timer(io);
    // set interval
    timer_->expires_from_now(boost::posix_time::milliseconds(timer_interval));
    timer_->async_wait(boost::bind(&InertialTracker::periodic_task, this));

    // run timer
    io.run();
    LOGD("inertialTracker thread killed");
}

// loop task
void InertialTracker::periodic_task() {
    // post synchronization (lock mutex for conditional variable)
    boost::unique_lock<boost::mutex> lock(inertial_done_mutex);

    if (threadRunning) {
        LOGD("inertialTracker thread task performed");
        timer_->expires_from_now(boost::posix_time::milliseconds(timer_interval));
        timer_->async_wait(boost::bind(&InertialTracker::periodic_task, this));
    }

    // perform action
    std::vector<SensorDataPtr> result = SensorDataStorage::getInstance()->pop_inertial();
    LOGD("inertial storage popped");

    // match compass and gravity first (with some threshold + averaging)ㅖ
    std::vector<SensorDataPtr> remaining_array;
    std::vector<SensorDataPtr> gravity_array;
    for (int i= 0 ; i < result.size() ; i++)
    {
        LOGD("FUCK POINTER ::: %p", result[i].get());
        if (result[i]->type == GRAVITY)
            gravity_array.push_back(result[i]);
        else
            remaining_array.push_back(result[i]);
    }
    LOGD("AAAAAAAAAAAAAAAAAA");
    LOGD("gravity array size %d", gravity_array.size());
    std::vector<SensorDataPtr>::iterator iter = gravity_array.begin();
    for (int i= 0 ; i < remaining_array.size() ; i++)
    {
        if (remaining_array[i]->type == COMPASS)
        {
            double x, y, z;
            // attach magnet by windowed averagin
            calculateGravity(remaining_array[i], gravity_array, iter, x, y, z);
        }
    }
    LOGD("BBBBBBBBBBBBBBBBBBB");
    // task something with imu data
    // 1. step detection with accelerometer
    // 2. gyroscope integration
    // 3. magnetometer
    for (int i=0 ; i < remaining_array.size() ; i++) {
        callback_func(remaining_array[i]);
    }
    LOGD("CCCCCCCCCCCCCCCCCCC");
    // post synchronization
    inertial_ready = true;
    inertial_done_cond.notify_all();
    LOGD("EEEEEEEEEEEEEEEEE");
}

void InertialTracker::initPoseGraphCallback(SensorDataPtr ptr)
{
    // 1. change step initial node continuously if accel data met ( no action, just time update )
    // 2. change gyro initial node continuously if gyro data met ( no action, just time update )
    // 3. change absolute (samples until ~)
    LOGD("initPoseGraphCallback POINTER :::::::: %p", ptr.get());
    switch ( ptr->type )
    {
        case COMPASS:
        {
            LOGD("COMPASS IN");
            CompassData* compass = static_cast<CompassData*>( ptr.get() );
            if (compass->grav_set)
            {
                initial_compass_number++;
                initial_compass_data.x += compass->x;
                initial_compass_data.y += compass->y;
                initial_compass_data.z += compass->z;
                initial_compass_data.grav_x += compass->grav_x;
                initial_compass_data.grav_y += compass->grav_y;
                initial_compass_data.grav_z += compass->grav_z;
            }
            break;
        }
        default:
            LOGD("OTHER IN");
            break;
    }

    bool init_done = false;
    // if condition met, init_done is set
    if (initial_compass_number >= COMPASS_INIT_NUMBER) {
        init_done = true;
        initial_compass_data.x /= initial_compass_number;
        initial_compass_data.y /= initial_compass_number;
        initial_compass_data.z /= initial_compass_number;

        initial_compass_data.grav_x /= initial_compass_number;
        initial_compass_data.grav_y /= initial_compass_number;
        initial_compass_data.grav_z /= initial_compass_number;

        Matrix initial_orientation = getAbsoluteDir(initial_compass_data);
        // change the initial node of pose grpah


        // set initial pose (set abs_orient) and push it
        pose_set.push_back( boost::make_shared<Pose>(initial_orientation, 1.0, ptr->t ) );

        // Particle init
        ParticleFilter::getInstance()->initParticles( ptr->t );
    }
    LOGD("initial compass number : %d", initial_compass_number);

    if (init_done) {
        isInit = true;
        LOGD("inertial tracker init done");
        // notify to all listener?
        callback_func = boost::bind(&InertialTracker::trackCallback, this, _1);
    }
}
*/
/*
void InertialTracker::trackCallback(SensorDataPtr ptr)
{
    LOGD("trackCallback POINTER :::::::: %p", ptr.get());

    double t = ptr->t;
    switch (ptr->type) {
        case ACCEL: {
            AccelData *accel = static_cast<AccelData *>( ptr.get());
            bool step_detected = stepDetector.pushAndDetect(*accel);
            if (step_detected)
            {
                // pose_set[0]: PosePtr
                // add step event as a edge ? with rotation matrix? ...
                graph_ptr->register_step(ptr->t, *pose_set[0]);
                // reset poset_set[0] to [ I, 0; 0, 1]
                //
                pose_set[0]->resetIntegrate( ptr->t );
                LOGD("step detected");
            }

                //graph_ptr->add_step(t);
            break;
        }
        case GYRO: {
            //TfMat rotmat();
            GyroData *gyro = static_cast<GyroData *>( ptr.get());

            // for all pose in the pose_set,,, integrate the gyroscope and apply it
            for (int i = 0; i < pose_set.size() ; i++)
            {
                TfMat gyro_tf = gyroIntegrator.integrate( *pose_set[i], *gyro);
                pose_set[i]->applyTF(gyro_tf, true);
            }
            LOGD("gyro integrated");
            break;
        }
        default:
            break;
    }
}

void InertialTracker::calculateGravity(SensorDataPtr compass_ptr, std::vector<SensorDataPtr> gravity_array, std::vector<SensorDataPtr>::iterator& iter, double& x, double& y, double& z)
{
    LOGD("GRAVITY POINTER ::: %p", compass_ptr.get());
    double t = compass_ptr->t;
    LOGD("QQQQQQQQQQQQQQQQQQQQQ");
    CompassData* compass = static_cast<CompassData*>( compass_ptr.get() );
    LOGD("WWWWWWWWWWWWWWWWWWWWWWW");
    std::vector<SensorDataPtr>::iterator first;
    std::vector<SensorDataPtr>::iterator last_next;
    FindGravityFirst gFirst;
    FindGravityLastNext gLastNext;

    double lower_bound = t - COMPASS_SEARCH_DELTAT;
    double upper_bound = t + COMPASS_SEARCH_DELTAT;
    gFirst.compass_t_lower = lower_bound;
    gFirst.compass_t_upper = upper_bound;
    gLastNext.compass_t_upper = upper_bound;

    LOGD("EEEEEEEEEEEEEEEEEEEEEEEEEEEE");

    std::vector<SensorDataPtr>::iterator iterator = iter;
    first = find_if(iterator, gravity_array.end(), gFirst);
    LOGD("RRRRRRRRRRRRRRRRRRRRRRRRRR");

    last_next = find_if(first, gravity_array.end(), gLastNext);
    LOGD("TTTTTTTTTTTTTTTTTTTTTTTTTT");
    iter = last_next;


    if (first == gravity_array.end())
    {
        LOGD("NO EXIST");
        // not found ==> skip this compass
        iter = last_next;
        compass->grav_set = false;
    }
    else
    {
        LOGD("EXIST");
        // found ==> update iter and

        // averaging ( from first to last_next )
        double x_accum = 0;
        double y_accum = 0;
        double z_accum = 0;
        int n = 0;
        for (iter = first ; iter != last_next ; iter++, n++)
        {
            // type conversion to GravitySensor
            // read x, y, z and add it to x, y, z
            GravityData* data = static_cast<GravityData*>( (*iter).get() );
            x_accum += data->x;
            y_accum += data->y;
            z_accum += data->z;
        }
        x = x_accum / n;
        y = y_accum / n;
        z = z_accum / n;
        compass->set_gravity(x, y, z);
    }
}*/