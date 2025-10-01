#include "core.h"
#include "logic.h" 
#include <windows.h>
#include <iostream>

struct ThreadData 
{
    const vector<int>* vec_ptr;
    int minValue;
    int maxValue;
    double averageValue;
};

DWORD WINAPI findMinMaxThread(LPVOID lpParameter) 
{
    ThreadData* data = (ThreadData*)lpParameter;
    MinMaxResult result = FunctionfindMinMax(*(data->vec_ptr)); 
    data->minValue = result.min;
    data->maxValue = result.max;
    cout << "MinMax thread finished." << endl;
    return 0;
}

DWORD WINAPI findAverageThread(LPVOID lpParameter) 
{
    ThreadData* data = (ThreadData*)lpParameter;
    AvarageResult result = FunctionfindAvarage(*(data->vec_ptr));
    data->averageValue = result.avarage;
    cout << "Average thread finished." << endl;
    return 0;
}

CalculationResult processArrayWithThreads(const vector<int>& inputArray) 
{
    ThreadData data;
    data.vec_ptr = &inputArray;

    HANDLE hMinMaxThread = CreateThread(NULL, 0, findMinMaxThread, &data, 0, NULL);
    HANDLE hAverageThread = CreateThread(NULL, 0, findAverageThread, &data, 0, NULL);
    
    HANDLE handles[] = { hMinMaxThread, hAverageThread };
    WaitForMultipleObjects(2, handles, TRUE, INFINITE);
    
    CloseHandle(hMinMaxThread);
    CloseHandle(hAverageThread);

    vector<int> modifiedArray = inputArray; 
    
    int minIndex = -1, maxIndex = -1;
    for (size_t i = 0; i < modifiedArray.size(); ++i) 
    {
        if (modifiedArray[i] == data.minValue && minIndex == -1) minIndex = i;
        if (modifiedArray[i] == data.maxValue && maxIndex == -1) maxIndex = i;
    }

    if (minIndex != -1) modifiedArray[minIndex] = static_cast<int>(data.averageValue);
    if (maxIndex != -1) modifiedArray[maxIndex] = static_cast<int>(data.averageValue);
    
    CalculationResult finalResult;
    finalResult.finalMinValue = data.minValue;
    finalResult.finalMaxValue = data.maxValue;
    finalResult.finalAverageValue = data.averageValue;
    finalResult.finalArray = modifiedArray;

    return finalResult;
}