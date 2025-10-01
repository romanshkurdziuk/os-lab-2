#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <vector>

using namespace std;

struct MinMax { int min; int max; };
struct Avarage { double avarage; };

MinMax FunctionfindMinMax(const vector<int>& vec);
Avarage FunctionfindAvarage(const vector<int>& vec);


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