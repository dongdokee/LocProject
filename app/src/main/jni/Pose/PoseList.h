//
// Created by dongdokee on 2015-11-26.
//

#ifndef LOCPROJECT_POSELIST_H
#define LOCPROJECT_POSELIST_H

#include "boost/shared_ptr.hpp"

//#include "boost/intrusive/list.hpp"
#include "../Pose/Pose.h"
#include <list>

typedef std::list<PosePtr> PoseListType;

class PoseList {
private:
    boost::recursive_mutex m_guard_imu;
    boost::recursive_mutex m_guard_visual;

    PoseListType imu_list;
    PoseListType visual_list;

    PosePtr last_rotate_pose_imu;

    PoseList() {}

public:
    static PoseList* getInstance()
    {
        static PoseList list;
        return &list;
    }


    void push_imu_pose(Pose& pose, bool isRot) {
        boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_imu);
        imu_list.push_back(Pose::make(pose));
        if (isRot)
            last_rotate_pose_imu = imu_list.back();
    }
    void push_visual_pose(Pose& pose) {
        boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_visual);
        visual_list.push_back(Pose::make(pose));
    }

    PosePtr get_last_imu_pose() {
        return imu_list.back();
    }
    PosePtr get_last_visual_pose() {
        return visual_list.back();
    }
};


#endif //LOCPROJECT_POSELIST_H
