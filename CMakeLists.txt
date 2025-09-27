# --- Базовая настройка проекта ---
cmake_minimum_required(VERSION 3.10)
project(OS_Lab2_Threads CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Указываем CMake, где искать заголовочные файлы ---
# Теперь #include "logic.h" будет работать из любого места.
include_directories(include)


# --- Основная исполняемая программа (main.exe) ---

# Указываем, что наша программа состоит из ДВУХ исходных файлов:
# main.cpp (где пользовательский интерфейс и потоки) и
# logic.cpp (где математические вычисления).
add_executable(main
    src/main.cpp
    src/logic.cpp
)

# Для Windows добавляем флаг -mconsole, чтобы избежать ошибок линковки с WinMain.
if(WIN32)
    target_compile_options(main PRIVATE -mconsole)
endif()


# --- Настройка тестов ---

# Включаем фреймворк для тестирования CTest (встроен в CMake).
enable_testing()

# Добавляем поддиректорию с Catch2. CMake сам найдет там CMakeLists.txt
# и создаст цель Catch2::Catch2WithMain.
add_subdirectory(tests/catch2)

# Создаем исполняемый файл для тестов (run_tests.exe).
# Он состоит из файла с тестами (tests.cpp) и файла с ЛОГИКОЙ (logic.cpp),
# которую мы тестируем. Он НЕ включает main.cpp!
add_executable(run_tests
    tests/tests.cpp
    src/logic.cpp
)

# Связываем наши тесты с библиотекой Catch2.
# CMake сам пропишет все нужные пути для include и линковки.
target_link_libraries(run_tests PRIVATE Catch2::Catch2WithMain)

# Добавляем наш исполняемый файл с тестами в систему CTest,
# чтобы мы могли запускать их командой `ctest`.
add_test(NAME AllUnitTests COMMAND run_tests)