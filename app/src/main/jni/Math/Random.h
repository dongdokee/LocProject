//
// Created by dongdokee on 2015-11-18.
//

#ifndef LOCPROJECT_RANDOM_H
#define LOCPROJECT_RANDOM_H

#include "boost/random/linear_congruential.hpp"
#include "boost/random/uniform_real.hpp"
#include "boost/random/normal_distribution.hpp"
#include <vector>
#include <ctime>
#include "../util/log.h"


class Random {
private:
    static boost::minstd_rand intgen; // engine
public:
    static void init();
    static std::vector<double> drawUniform(double min, double max, int num);
    static std::vector<double> drawNormal(double mu, double sigma, int num);
    static void test();

};


#endif //LOCPROJECT_RANDOM_H
