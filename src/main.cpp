#include <iostream>
#include <vector>
#include <windows.h>
#include <optional>
#include "logic.h" // Включаем "чистую" логику

using namespace std;

// --- Вспомогательные функции и структуры для main ---
struct ThreadData {
    vector<int>* vec_ptr;
    int maxValue;
    int minValue;
    double averageValue;
};

DWORD WINAPI findMinMaxThread(LPVOID lpParameter) {
    ThreadData* data = (ThreadData*)lpParameter;
    MinMax result = FunctionfindMinMax(*(data->vec_ptr));
    data->minValue = result.min;
    data->maxValue = result.max;
    cout << "MinMax thread finished." << endl;
    return 0;
}

DWORD WINAPI findAverageThread(LPVOID lpParameter) {
    ThreadData* data = (ThreadData*)lpParameter;
    Avarage result = FunctionfindAvarage(*(data->vec_ptr));
    data->averageValue = result.avarage;
    cout << "Average thread finished." << endl;
    return 0;
}

optional<vector<int>> initializeArrayFromInput() {
    cout << "Enter size of array: ";
    int size;
    cin >> size;
    if (size <= 0) {
        cout << "ERROR: Array size must be positive..." << endl;
        return nullopt;
    }
    vector<int> vec(size);
    cout << "Enter " << size << " array elements:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "[" << i << "] ";
        cin >> vec[i];
    }
    return vec;
}

void performCalculationsAndPrintFinalResult(vector<int>& vec) {
    ThreadData data;
    data.vec_ptr = &vec;
    HANDLE hMinMaxThread = CreateThread(NULL, 0, findMinMaxThread, &data, 0, NULL);
    HANDLE hAverageThread = CreateThread(NULL, 0, findAverageThread, &data, 0, NULL);
    HANDLE handles[] = { hMinMaxThread, hAverageThread };
    WaitForMultipleObjects(2, handles, TRUE, INFINITE);
    CloseHandle(hMinMaxThread);
    CloseHandle(hAverageThread);

    cout << "\nAll worker threads finished." << endl;
    cout << "\nResults from threads:" << endl;
    cout << "Min value: " << data.minValue << endl;
    cout << "Max value: " << data.maxValue << endl;
    cout << "Average value: " << data.averageValue << endl;
    
    int minIndex = -1, maxIndex = -1;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == data.minValue && minIndex == -1) minIndex = i;
        if (vec[i] == data.maxValue && maxIndex == -1) maxIndex = i;
    }

    if (minIndex != -1) vec[minIndex] = static_cast<int>(data.averageValue);
    if (maxIndex != -1) vec[maxIndex] = static_cast<int>(data.averageValue);

    cout << "\nFinal array:" << endl;
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// --- Главная функция ---
int main() {
    auto optionalVec = initializeArrayFromInput();
    if (!optionalVec) {
        return 1;
    }
    vector<int> vec = *optionalVec;

    cout << "\nInitial array: ";
    for (int val : vec) { cout << val << " "; }
    cout << endl;
    
    performCalculationsAndPrintFinalResult(vec);
    
    return 0;
}