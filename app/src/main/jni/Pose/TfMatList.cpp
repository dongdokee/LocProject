//
// Created by dongdokee on 2015-12-01.
//

#include "TfMatList.h"
#include "boost/thread.hpp" // lock guard?

TfMatList::TfMatList() { }

TfMatList* TfMatList::getInstance()
{
    static TfMatList list;
    return &list;
}

void TfMatList::push_imu_pose(TfMat mat) {
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_imu);
    //LOGD("TFMATLIST");
    //mat.logging();   // LOGLOGLOGLKGSJLG

    imu_list.push_back(TfMat::make(mat));

    if (!mat.getIsStep())
        last_rotate_tftime = mat.time();
}

void TfMatList::push_visual_pose(TfMat mat) {
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_visual);
    visual_list.push_back(TfMat::make(mat));
}

std::vector<TfMatPtr> TfMatList::pop_imu_tfmat() {
    boost::lock_guard<boost::recursive_mutex> lock_imu(m_guard_imu);
    std::vector<TfMatPtr> result;

    for ( TfMatListType::const_iterator ci = imu_list.begin() ; ci != imu_list.end() ; ++ci)
        result.push_back(*ci);

    imu_list.clear();

    return result;
}

std::vector<TfMatPtr> TfMatList::pop_visual_tfmat() {

}