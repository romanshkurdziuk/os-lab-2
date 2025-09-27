// Этот файл теперь будет очень простым
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// Подключаем НАШИ заголовочные файлы, если они есть.
// В нашем случае, нам нужно как-то получить доступ к функциям из main.cpp
// Правильный способ - создать main.h, но для простоты мы оставим main.cpp
// в сборке тестов.

// Импортируем то, что нам нужно протестировать.
// Для этого нам нужно вынести прототипы функций в отдельный файл.
// НО! Чтобы не усложнять, давай пока просто объявим их здесь.

#include <vector>

using namespace std;

// Структуры, которые мы тестируем
struct MinMax { int min; int max; };
struct Avarage { double avarage; };

// Прототипы функций из main.cpp, которые мы тестируем
MinMax FunctionfindMinMax(const vector<int>& vec);
Avarage FunctionfindAvarage(const vector<int>& vec);


// Тесты остаются такими же
TEST_CASE("Min/Max logic", "[minmax]") {
    vector<int> test_vec = {10, 5, 100, 1, 50};
    MinMax result = FunctionfindMinMax(test_vec);
    REQUIRE(result.min == 1);
    REQUIRE(result.max == 100);
}

TEST_CASE("Average logic", "[average]") {
    vector<int> test_vec = {1, 2, 3, 4, 5};
    Avarage result = FunctionfindAvarage(test_vec);
    REQUIRE(result.avarage == Catch::Approx(3.0));
}