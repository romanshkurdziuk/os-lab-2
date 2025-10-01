#ifndef CORE_H
#define CORE_H

using namespace std;

#include <vector>

struct CalculationResult 
{
    int finalMinValue;
    int finalMaxValue;
    double finalAverageValue;
    vector<int> finalArray;
};

CalculationResult processArrayWithThreads(const vector<int>& inputArray);

#endif // CORE_H