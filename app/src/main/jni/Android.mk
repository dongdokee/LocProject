LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := locproj
#LOCAL_SRC_FILES := util/init.cpp \
#                    util/deinit.cpp \
#                    Visualizer/draw_callback.cpp \
#                    callback/callback.cpp \
#                    callback/jni_stuff.cpp \
#                    Filter/ParticleFilter.cpp \
#                    Filter/Particle.cpp \
#                    DataStructures/Pose.cpp \
#                    DataStructures/PoseGraph.cpp \
#                    DataStructures/SensorData.cpp \
#                    DataStructures/SensorDataStorage.cpp \
#                    Tracker/getAbsoluteDir.cpp \
#                    Tracker/GyroIntegrator.cpp \
#                    Tracker/StepDetector.cpp \
#                    Tracker/InertialTracker.cpp

LOCAL_SRC_FILES := DataStructures/SensorData.cpp \
                    DataStructures/SensorDataStorage.cpp \
                    configure/jni_callback.cpp \
                    configure/jni_config.cpp \
                    configure/init.cpp \
                    util/Parameter.cpp \
                    util/MemoryManager.cpp \
                    UI/UIManager.cpp \
                    Math/LinearAlgebra.cpp \
                    Math/Random.cpp \
                    Pose/TfMat.cpp \
                    Pose/Pose.cpp \
                    Pose/CoordinateSystem.cpp \
                    Pose/TfMatList.cpp \
                    Tracker/Tracker.cpp \
                    Tracker/InertialTracker.cpp \
                    DR/StepDetector.cpp \
                    Filter/Particle.cpp \
                    Filter/ParticleFilter.cpp






LOCAL_CFLAGS += -I$(LOCAL_PATH)/boost/include/boost-1_53
LOCAL_LDLIBS := -llog -L$(LOCAL_PATH)/boost/lib/ -lboost_system-gcc-mt-1_53 -lboost_thread_pthread-gcc-mt-1_53 -lboost_timer-gcc-mt-1_53
LOCAL_LDLIBS += C:/Android/android-ndk-r10d/sources/cxx-stl/gnu-libstdc++/4.6/libs/armeabi-v7a/libsupc++.a
LOCAL_LDLIBS += C:/Android/android-ndk-r10d/sources/cxx-stl/gnu-libstdc++/4.6/libs/armeabi-v7a/libgnustl_static.a


LOCAL_C_INCLUDES := C:/Android/android-ndk-r10d/sources/cxx-stl/gnu-libstdc++/4.6/include
LOCAL_C_INCLUDES += C:/Android/android-ndk-r10d/sources/cxx-stl/gnu-libstdc++/4.6/libs/armeabi-v7a/include


include $(BUILD_SHARED_LIBRARY)