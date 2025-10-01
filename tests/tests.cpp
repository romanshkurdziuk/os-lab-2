#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "logic.h"
#include <vector>
#include <limits>

// Тест-сьют для функции поиска минимума и максимума
TEST_CASE("FunctionfindMinMax tests", "[minmax]") {

    SECTION("Empty vector") {
        std::vector<int> vec = {};
        // Ожидаем {0, 0} согласно нашей реализации в logic.cpp
        MinMax expected = {0, 0}; 
        
        MinMax actual = FunctionfindMinMax(vec);
        
        REQUIRE(actual.min == expected.min);
        REQUIRE(actual.max == expected.max);
    }

    SECTION("Single element vector") {
        std::vector<int> vec = {42};
        MinMax expected = {42, 42};
        
        MinMax actual = FunctionfindMinMax(vec);
        
        REQUIRE(actual.min == expected.min);
        REQUIRE(actual.max == expected.max);
    }

    SECTION("Multiple elements with negative numbers") {
        std::vector<int> vec = {10, -5, 20, 0, -15};
        MinMax expected = {-15, 20};

        MinMax actual = FunctionfindMinMax(vec);

        REQUIRE(actual.min == expected.min);
        REQUIRE(actual.max == expected.max);
    }
    
    SECTION("Large numbers (boundary check)") {
        int max_int = (std::numeric_limits<int>::max)();
        int min_int = (std::numeric_limits<int>::min)();
        std::vector<int> vec = {max_int, 0, min_int};
        
        MinMax expected = {min_int, max_int};
        MinMax actual = FunctionfindMinMax(vec);

        REQUIRE(actual.min == expected.min);
        REQUIRE(actual.max == expected.max);
    }
}

// Тест-сьют для функции поиска среднего
TEST_CASE("FunctionfindAvarage tests", "[average]") {

    SECTION("Empty vector") {
        std::vector<int> vec = {};
        Avarage expected = {0.0};
        
        Avarage actual = FunctionfindAvarage(vec);
        
        // Для double используем Approx для безопасного сравнения
        REQUIRE(actual.avarage == Catch::Approx(expected.avarage));
    }

    SECTION("Simple integers resulting in whole number average") {
        std::vector<int> vec = {10, 20, 30}; // Сумма 60, среднее 20
        Avarage expected = {20.0};

        Avarage actual = FunctionfindAvarage(vec);

        REQUIRE(actual.avarage == Catch::Approx(expected.avarage));
    }

    SECTION("Integers resulting in fractional average") {
        std::vector<int> vec = {1, 2}; // Сумма 3, среднее 1.5
        Avarage expected = {1.5};

        Avarage actual = FunctionfindAvarage(vec);

        // Approx справляется с неточнстями float
        REQUIRE(actual.avarage == Catch::Approx(expected.avarage).epsilon(0.001));
    }
    
    SECTION("Vector with negative numbers") {
        std::vector<int> vec = {-10, 10, 5}; // Сумма 5, среднее 5/3 ~= 1.666...
        
        Avarage actual = FunctionfindAvarage(vec);
        double expectedValue = 5.0 / 3.0;

        REQUIRE(actual.avarage == Catch::Approx(expectedValue));
    }
}