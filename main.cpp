#include <iostream>
#include <vector>
#include <windows.h>


using namespace std;

struct dataStruct
{
    vector<int>* arr;
    int maxValue;
    int minValue;
    double averageValue;
};

DWORD WINAPI findMinMax (LPVOID lpParameter)
{
    dataStruct* data = (dataStruct*)(lpParameter);
    int size = data->arr->size();
    data->minValue = data->arr->at(0);
    data->maxValue = data->arr->at(0);
    for (int i = 1; i < size; ++i)
    {
        if (data->arr->at(i) < data->minValue)
        {
            data->minValue = data->arr->at(i);
        }
        Sleep(7);
        if (data->arr->at(i) > data->maxValue)
        {
            data->maxValue = data->arr->at(i);
        }
        Sleep(7);
    }
    return 0;
}

DWORD WINAPI findAvarage (LPVOID lpParameter)
{
    dataStruct* data = (dataStruct*)(lpParameter);
    int size = data->arr->size();
    double sum = 0;
    for (int i = 0; i < size; ++i)
    {
        sum += data->arr->at(i);
        Sleep(12);
    }
    double avarage = sum / size;
    data->averageValue = avarage;
    return 0;
}



using namespace std;
int main()
{
    cout << "Enter array size: ";
    int size;
    cin>>size;
    if(size <= 0)
    {
        cout << "Error: Array size must be positive... " << endl;
        return 1;
    }
    vector<int> array(size);
    cout << "Enter " << size << " array elements" << endl;
    for (int i = 0; i < size; ++i)
    {
        cout << "[" << i << "] ";
        cin >> array[i];
    }

    for (int i = 0; i < size; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    dataStruct data;
    data.arr = &array;


    HANDLE hMinMaxThread = CreateThread(NULL, 0, findMinMax, &data, 0, NULL);
    HANDLE hAvarageThread = CreateThread(NULL, 0, findAvarage, &data, 0, NULL);

    if (hMinMaxThread == NULL || hAvarageThread == NULL)
    {
        cout << "Error: Failed to create threads..." << endl;
        return 1;
    }
    WaitForSingleObject(hMinMaxThread, INFINITE);\
    cout << "DEBUG: MinMax thread has finished waiting." << endl; // <--- МАЯЧОК 4
    WaitForSingleObject(hAvarageThread, INFINITE);
    cout << "DEBUG: Average thread has finished waiting." << endl; // <--- МАЯЧОК 5
    cout << "ALL threads finished... " << endl;
    
    CloseHandle(hMinMaxThread);
    CloseHandle(hAvarageThread);

    cout << "Main thread continues..." << endl;

    cout << "Result from threeds:" <<endl;
    cout << "Min element: " << data.minValue << endl;
    cout << "Max element: " << data.maxValue << endl;
    cout << "Average value: " << data.averageValue << endl;

    int minIndex = -1;
    int maxIndex = -1;

    for (int i = 0; i < size; ++i)
    {
        if (array[i] == data.minValue && minIndex == -1)
        {
            minIndex = i;
        }
        if (array[i] == data.maxValue && maxIndex == -1)
        {
            maxIndex = i;
        }

    }
    if (maxIndex != -1 && minIndex != -1)
    {
        array[minIndex] = static_cast<int>(data.averageValue);
        array[maxIndex] = static_cast<int>(data.averageValue);
    }

    for (int val : array)
    {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}