cmake_minimum_required(VERSION 3.21)
project(cw_os)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка предельных значений для использования функций Windows API
add_definitions(-DWIN32_LEAN_AND_MEAN)
add_definitions(-D_WIN32_WINNT=0x0A00)


# Определяем исполняемый файл main
add_executable(main
        main.cpp
        cw/user_data/src/user_data.cpp
        cw/table/src/table.cpp
        cw/schema/src/schema.cpp
        cw/schemas_pool/src/schemas_pool.cpp
        cw/database/src/data_base.cpp
        logger/client_logger/src/client_logger.cpp
        logger/logger/src/logger.cpp
        logger/logger/src/logger_guardant.cpp
        allocator/allocator/src/allocator_guardant.cpp
        allocator/allocator/src/allocator_test_utils.cpp
        allocator/allocator_boundary_tags/src/allocator_boundary_tags.cpp
        cw/string_pool/src/string_pool.cpp
        allocator/allocator_global_heap/src/allocator_global_heap.cpp)


add_executable(cw_main
        main.cpp
        cw/user_data/src/user_data.cpp
        cw/table/src/table.cpp
        cw/schema/src/schema.cpp
        cw/schemas_pool/src/schemas_pool.cpp
        cw/database/src/data_base.cpp
        logger/client_logger/src/client_logger.cpp
        logger/logger/src/logger.cpp
        logger/logger/src/logger_guardant.cpp
        allocator/allocator/src/allocator_guardant.cpp
        allocator/allocator/src/allocator_test_utils.cpp
        allocator/allocator_boundary_tags/src/allocator_boundary_tags.cpp
        cw/string_pool/src/string_pool.cpp
        allocator/allocator_global_heap/src/allocator_global_heap.cpp)


