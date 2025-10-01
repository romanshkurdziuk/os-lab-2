#ifndef LOGIC_H
#define LOGIC_H

using namespace std;

#include <vector>

const int MIN_MAX_THREED_SLEEP = 7;
const int AVERAGE_THREED_SLEEP = 12;

struct MinMaxResult
{
    int min;
    int max;
};

struct AvarageResult
{
    double avarage;
};

MinMaxResult FunctionfindMinMax(const vector<int> &vec);
AvarageResult FunctionfindAvarage(const vector<int> &vec);

#endif // LOGIC_H