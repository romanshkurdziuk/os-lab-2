#include "logic.h"
#include <windows.h>
using namespace std;


MinMax FunctionfindMinMax(const vector<int> &vec)
{
    if (vec.empty())
    {
        return {0, 0};
    }
    int size = vec.size();
    MinMax result = {vec[0], vec[0]};
    for (int i = 0; i < size; ++i)
    {
        if (vec[i] < result.min)
        {
            result.min = vec[i];
        }
        Sleep(MIN_MAX_THREED_SLEEP);
        if (vec[i] > result.max)
        {
            result.max = vec[i];
        }
        Sleep(MIN_MAX_THREED_SLEEP);
    }
    return result;
}


Avarage FunctionfindAvarage(const vector<int> &vec)
{
    if (vec.empty())
    {
        return{0.0};
    }
    int size = vec.size();
    double sum = 0;
    for (int i = 0; i < size; ++i)
    {
        sum += vec[i];
        Sleep(AVERAGE_THREED_SLEEP);
    }
    Avarage result = {sum / size};
    return result;
}
