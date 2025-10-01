# --- Базовая настройка проекта ---
cmake_minimum_required(VERSION 3.10)
project(OS_Lab2_Threads CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)

add_executable(main
    src/main.cpp
    src/logic.cpp
    src/core.cpp
)

if(WIN32)
    target_compile_options(main PRIVATE -mconsole)
endif()

enable_testing()

add_subdirectory(tests/catch2)

add_executable(run_tests
    tests/tests.cpp
    src/logic.cpp
)

target_link_libraries(run_tests PRIVATE Catch2::Catch2WithMain)

add_test(NAME AllUnitTests COMMAND run_tests)