cmake_minimum_required(VERSION 3.2)
set($TARGET join_server)

set(INTERFACE_HDRS
    interfaces/icore.h
    interfaces/icommand_handler.h
    interfaces/iserver.h
    interfaces/icommand.h
    interfaces/itables_manager.h)

set(COMMANDS_SRC
    check_syntax_command.h check_syntax_command.cpp
    insert_command.h insert_command.cpp
    truncate_command.h truncate_command.cpp
    intersection_command.h intersection_command.cpp
    symmetric_difference_command.h symmetric_difference_command.cpp)

set(NETWORKING_SRC
    async_server.h async_server.cpp
    session.h session.cpp)

add_executable(${TARGET}
    ${INTERFACE_HDRS}
    ${COMMANDS_SRC}
    ${NETWORKING_SRC}
    main.cpp
    args_parser.h args_parser.cpp
    core.h core.cpp
    command_handler.h command_handler.cpp
    tables_manager.h tables_manager.cpp
    table.h table.cpp)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${TARGET}
    PRIVATE ${Boost_INCLUDE_DIR}
)

# максимально строгие настройки компилятора
if (MSVC)
    target_compile_options(${TARGET} PRIVATE
        /W4
    )
else ()
    target_compile_options(${TARGET} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

target_link_libraries(${TARGET}
    ${Boost_LIBRARIES}
    Threads::Threads
)

# бинарник кладем в каталог bin
install(TARGETS ${TARGET} RUNTIME DESTINATION bin)

# генерить будем deb пакет
set(CPACK_GENERATOR DEB)

# конфигурируем deb пакет
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT oshuev.valery@yandex.ru)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-program-options,libboost-system") 

# подключем генератор пакетов
include(CPack)
