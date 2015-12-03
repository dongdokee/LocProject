//
// Created by dongdokee on 2015-12-01.
//

#ifndef LOCPROJECT_TFMATLIST_H
#define LOCPROJECT_TFMATLIST_H

#include "boost/shared_ptr.hpp"
#include "boost/thread/recursive_mutex.hpp" // recursive mutex?


#include "TfMat.h"
#include <list>
#include <vector>
typedef std::list<TfMatPtr> TfMatListType;

class TfMatList {
private:
    boost::recursive_mutex m_guard_imu;
    boost::recursive_mutex m_guard_visual;

    TfMatListType imu_list;
    TfMatListType visual_list;

    TIMESTAMP_T last_rotate_tftime;

    TfMatList();

public:
    static TfMatList* getInstance();


    void push_imu_pose(TfMat mat);
    void push_visual_pose(TfMat mat);

    std::vector<TfMatPtr> pop_imu_tfmat();

    std::vector<TfMatPtr> pop_visual_tfmat();
/*    TfMatPtr get_last_imu_pose() {
        return imu_list.back();
    }
    TfMatPtr get_last_visual_pose() {
        return visual_list.back();
    }*/
};

#endif //LOCPROJECT_TFMATLIST_H
