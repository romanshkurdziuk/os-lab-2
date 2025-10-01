#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "logic.h"
#include <vector>
#include <limits>

TEST_CASE("FunctionfindMinMax tests", "[minmax]") 
{

    SECTION("Empty vector") 
    {
        std::vector<int> vec = {};
        MinMaxResult expected = {0, 0}; 
        
        MinMaxResult actual = FunctionfindMinMax(vec);
        
        REQUIRE(actual.min == expected.min);
        REQUIRE(actual.max == expected.max);
    }

    SECTION("Single element vector") 
    {
        std::vector<int> vec = {42};
        MinMaxResult expected = {42, 42};
        
        MinMaxResult actual = FunctionfindMinMax(vec);
        
        REQUIRE(actual.min == expected.min);
        REQUIRE(actual.max == expected.max);
    }

    SECTION("Multiple elements with negative numbers") 
    {
        std::vector<int> vec = {10, -5, 20, 0, -15};
        MinMaxResult expected = {-15, 20};

        MinMaxResult actual = FunctionfindMinMax(vec);

        REQUIRE(actual.min == expected.min);
        REQUIRE(actual.max == expected.max);
    }
    
    SECTION("Large numbers (boundary check)") 
    {
        int max_int = (std::numeric_limits<int>::max)();
        int min_int = (std::numeric_limits<int>::min)();
        std::vector<int> vec = {max_int, 0, min_int};
        
        MinMaxResult expected = {min_int, max_int};
        MinMaxResult actual = FunctionfindMinMax(vec);

        REQUIRE(actual.min == expected.min);
        REQUIRE(actual.max == expected.max);
    }
}

TEST_CASE("FunctionfindAvarage tests", "[average]") 
{

    SECTION("Empty vector") 
    {
        std::vector<int> vec = {};
        AvarageResult expected = {0.0};
        
        AvarageResult actual = FunctionfindAvarage(vec);
        
        // Для double используем Approx для безопасного сравнения
        REQUIRE(actual.avarage == Catch::Approx(expected.avarage));
    }

    SECTION("Simple integers resulting in whole number average") 
    {
        std::vector<int> vec = {10, 20, 30}; 
        AvarageResult expected = {20.0};

        AvarageResult actual = FunctionfindAvarage(vec);

        REQUIRE(actual.avarage == Catch::Approx(expected.avarage));
    }

    SECTION("Integers resulting in fractional average") 
    {
        std::vector<int> vec = {1, 2};
        AvarageResult expected = {1.5};

        AvarageResult actual = FunctionfindAvarage(vec);

        // Approx справляется с неточнстями float
        REQUIRE(actual.avarage == Catch::Approx(expected.avarage).epsilon(0.001));
    }
    
    SECTION("Vector with negative numbers") 
    {
        std::vector<int> vec = {-10, 10, 5}; // Сумма 5, среднее 5/3 ~= 1.666...
        
        AvarageResult actual = FunctionfindAvarage(vec);
        double expectedValue = 5.0 / 3.0;

        REQUIRE(actual.avarage == Catch::Approx(expectedValue));
    }
}