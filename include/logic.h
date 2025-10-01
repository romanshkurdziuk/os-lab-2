#ifndef LOGIC_H
#define LOGIC_H

#include <vector>

const int MIN_MAX_THREED_SLEEP = 7;
const int AVERAGE_THREED_SLEEP = 12;

struct MinMax
{
    int min;
    int max;
};

struct Avarage
{
    double avarage;
};

MinMax FunctionfindMinMax(const std::vector<int> &vec);
Avarage FunctionfindAvarage(const std::vector<int> &vec);

#endif // LOGIC_H