#include <iostream>
#include <vector>
#include <windows.h>
#include <optional>


using namespace std;

struct dataStruct
{
    vector<int>* vec;
    int maxValue;
    int minValue;
    double averageValue;
};

struct MinMax
{
    int min;
    int max;
};

struct Avarage
{
    double avarage;
};

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


DWORD WINAPI findMinMax (LPVOID lpParameter)
{
    dataStruct* data = (dataStruct*)(lpParameter);
    MinMax minMax = FunctionfindMinMax(*data->vec);
    data->minValue = minMax.min;
    data->maxValue = minMax.max;
    return 0;
}

Avarage FunctionfindAvarage(const vector<int> &vec)
{
    if (vec.empty())
    {
        return;
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

DWORD WINAPI findAvarage (LPVOID lpParameter)
{
    dataStruct* data = (dataStruct*)(lpParameter);
    Avarage avarage = FunctionfindAvarage(*data->vec);
    data->averageValue = avarage.avarage;
    return 0;
}

optional<vector <int>> initializeArrayFromInput()
{
    cout << "Enter size of array: ";
    int size;
    cin >>size;
    if (size <= 0)
    {
        cout << "ERROR: Array size must be positive... " <<endl;
        return nullopt;
    }
    vector<int> vec(size);
    cout << "Enter " << size << " array elements" << endl;
    for (int i = 0; i < size; ++i)
    {
        cout << "[" << i << "] ";
        cin >> vec[i];
    }

    for (int i = 0; i < size; ++i)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    return vec;
}

void CalculateResult()
{
    dataStruct data;
    auto optionalArray = initializeArrayFromInput();
    if (!optionalArray)
    {
        cout << "ERROR: Array initialization failed..." << endl;
        return;
    }
    vector<int> vec = *optionalArray;
    data.vec = &vec;
    int size = data.vec->size();

    HANDLE hMinMaxThread = CreateThread(NULL, 0, findMinMax, &data, 0, NULL);
    HANDLE hAvarageThread = CreateThread(NULL, 0, findAvarage, &data, 0, NULL);

    WaitForSingleObject(hMinMaxThread, INFINITE);
    cout << "DEBUG: MinMax thread has finished waiting." << endl;
    WaitForSingleObject(hAvarageThread, INFINITE);
    cout << "DEBUG: Average thread has finished waiting." << endl;
    cout << "ALL threads finished... " << endl;
    
    CloseHandle(hMinMaxThread);
    CloseHandle(hAvarageThread);

    cout << "Result from threeds:" <<endl;
    cout << "Min element: " << data.minValue << endl;
    cout << "Max element: " << data.maxValue << endl;
    cout << "Average value: " << data.averageValue << endl;

    int minIndex = -1;
    int maxIndex = -1;
    for (int i = 0; i < size; ++i)
    {
        if(data.vec->at(i) == data.minValue && minIndex == -1)
        {
            minIndex = i;
        }
        if(data.vec->at(i) == data.maxValue && maxIndex == -1)
        {
            maxIndex = i;
        }
    }
    if (maxIndex != -1 && minIndex != -1)
    {
        data.vec->at(minIndex) = static_cast<int>(data.averageValue);
        data.vec->at(maxIndex) = static_cast<int>(data.averageValue);
    }

    for (int val : *data.vec)
    {
        cout << val << " ";
    }
    cout << endl;

}
   





using namespace std;
int main()
{   
    CalculateResult();
    return 0;
}