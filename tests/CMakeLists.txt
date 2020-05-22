cmake_minimum_required(VERSION 3.2)

set(TESTED_SRC
    ${CMAKE_SOURCE_DIR}/src/table.h ${CMAKE_SOURCE_DIR}/src/table.cpp
    ${CMAKE_SOURCE_DIR}/src/check_syntax_command.h ${CMAKE_SOURCE_DIR}/src/check_syntax_command.cpp
    ${CMAKE_SOURCE_DIR}/src/insert_command.h ${CMAKE_SOURCE_DIR}/src/insert_command.cpp
    ${CMAKE_SOURCE_DIR}/src/truncate_command.h ${CMAKE_SOURCE_DIR}/src/truncate_command.cpp
    ${CMAKE_SOURCE_DIR}/src/intersection_command.h ${CMAKE_SOURCE_DIR}/src/intersection_command.cpp
    ${CMAKE_SOURCE_DIR}/src/symmetric_difference_command.h ${CMAKE_SOURCE_DIR}/src/symmetric_difference_command.cpp
    ${CMAKE_SOURCE_DIR}/src/command_handling_exception.h ${CMAKE_SOURCE_DIR}/src/command_handling_exception.cpp
    ${CMAKE_SOURCE_DIR}/src/tables_manager.h ${CMAKE_SOURCE_DIR}/src/tables_manager.cpp)

set(TARGET_BIN
    join_server_test)

set(TARGET_SRC
    table_test.cpp
    commands_test.cpp
    core_mock.h)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_executable(${TARGET_BIN} ${TARGET_SRC} ${TESTED_SRC})

# включаем 17 стандарт
set_target_properties(${TARGET_BIN} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${TARGET_BIN}
    PRIVATE "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(${TARGET_BIN}
    ${Boost_LIBRARIES}
    CONAN_PKG::gtest
    Threads::Threads
)

# максимально строгие настройки компилятора
if (MSVC)
    target_compile_options(${TARGET_BIN} PRIVATE
        /W4
    )
else ()
    target_compile_options(${TARGET_BIN} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

add_test(${TARGET_BIN} bin/${TARGET_BIN})
