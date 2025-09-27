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
        Sleep(7);
        if (vec[i] > result.max)
        {
            result.max = vec[i];
        }
        Sleep(7);
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
        Sleep(12);
    }
    Avarage result = {sum / size};
    return result;
}
