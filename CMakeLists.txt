cmake_minimum_required(VERSION 3.2)
set(TARGET join_server)

# устанавливаем имя проекта и его версию
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    message("TRAVIS_BUILD_NUMBER IS DEFINED:" $ENV{TRAVIS_BUILD_NUMBER})
    project(${TARGET} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    message("TRAVIS_BUILD_NUMBER IS NOT DEFINED")
    project(${TARGET} VERSION 0.0.1)
endif()

find_package(Boost COMPONENTS program_options system thread REQUIRED)
find_package(Threads REQUIRED)

# включаем тесты
enable_testing()

# подключаем тесты
add_subdirectory(src)
add_subdirectory(tests)
