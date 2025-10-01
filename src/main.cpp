#include <iostream>
#include <vector>
#include <optional>
#include "core.h"

optional<vector<int>> initializeArrayFromInput() 
{
    cout << "Enter size of array: ";
    int size;
    cin >> size;
    if (size <= 0) 
    {
        cout << "ERROR: Array size must be positive..." << endl;
        return nullopt;
    }
    vector<int> vec(size);
    cout << "Enter " << size << " array elements:" << endl;
    for (int i = 0; i < size; ++i) 
    {
        cout << "[" << i << "] ";
        cin >> vec[i];
    }
    return vec;
}

void printResults(const CalculationResult& result, const std::vector<int>& initialVector) 
{
    cout << "\nInitial array: ";
    for (int val : initialVector) { cout << val << " "; }
    cout << endl;

    cout << "\nResults from threads:" << endl;
    cout << "Min value: " << result.finalMinValue << endl;
    cout << "Max value: " << result.finalMaxValue << endl;
    cout << "Average value: " << result.finalAverageValue << endl;
    
    cout << "\nFinal array:" << endl;
    for (int val : result.finalArray) {
        cout << val << " ";
    }
    cout << endl;
}

int main() 
{
    auto optionalVec = initializeArrayFromInput();
    if (!optionalVec) {
        return 1;
    }
    vector<int> initialVec = *optionalVec;
    CalculationResult result = processArrayWithThreads(initialVec);

    printResults(result, initialVec);
    
    return 0;
}