#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
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