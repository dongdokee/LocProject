//
// Created by dongdokee on 2015-11-18.
//

#include "Random.h"

boost::minstd_rand Random::intgen;

void Random::init()
{
    intgen.seed(static_cast<unsigned int>(std::time(0)));
}
std::vector<double> Random::drawUniform(double min, double max, int num)
{
    boost::uniform_real<double> gen(min, max);
    std::vector<double> result;
    for (int i = 0 ;i < num ; i++)
    {
        result.push_back(gen(intgen));
    }
    return result;
}

std::vector<double> Random::drawNormal(double mu, double sigma, int num)
{
    boost::normal_distribution<double> gen(mu, sigma);
    std::vector<double> result;
    for (int i = 0 ; i< num ; i++)
    {
        result.push_back(gen(intgen));
    }
    return result;
}

void Random::test()
{
    init();
    LOGD("uniform test [0,1]");
    std::vector<double> uniform = drawUniform(0, 1, 7);
    LOGD("%lf %lf %lf %lf %lf %lf %lf", uniform[0], uniform[1], uniform[2], uniform[3], uniform[4], uniform[5], uniform[6]);
    LOGD("uniform test mu:0, sigma = 5");
    std::vector<double> normal = drawNormal(0, 5, 7);
    LOGD("%lf %lf %lf %lf %lf %lf %lf", normal[0], normal[1], normal[2], normal[3], normal[4], normal[5], normal[6]);
}