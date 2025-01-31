cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(ENABLE_COLOR_OUTPUT "Enable colored compiler output" on)

project(svlm)

find_package(Catch2 3 REQUIRED /usr/local/lib)


include_directories(SYSTEM "/usr/local/include")

add_executable(t_operand_01.out t_operand_01.cc)
add_executable(t_operand_value_01.out t_operand_value_01.cc)
add_executable(t_operand_list_01.out t_operand_list_01.cc)
add_executable(t_operand_list_02.out t_operand_list_02.cc)
add_executable(t_operand_map_01.out t_operand_map_01.cc)
add_executable(t_operand_map_02.out t_operand_map_02.cc)
add_executable(t_operand_map_03.out t_operand_map_03.cc)
add_executable(t_root_01.out t_root_01.cc)
add_executable(t_operand_tuple_01.out t_operand_tuple_01.cc)
add_executable(010-TestCase 010-TestCase.cpp)

# add_library(mylib SHARED lib.cc)

target_link_libraries(t_operand_01.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)
target_link_libraries(t_operand_value_01.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)
target_link_libraries(t_operand_list_01.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)
target_link_libraries(t_operand_list_02.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)
target_link_libraries(t_operand_map_01.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)
target_link_libraries(t_operand_map_02.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)
target_link_libraries(t_operand_map_03.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)
target_link_libraries(t_root_01.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)
target_link_libraries(010-TestCase PRIVATE Catch2::Catch2WithMain)
target_link_libraries(t_operand_tuple_01.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)


enable_testing()
add_test(NAME t_operand_01.out COMMAND t_operand_01.out)
add_test(NAME t_operand_value_01.out COMMAND t_operand_value_01.out)
add_test(NAME t_operand_list_01.out COMMAND t_operand_list_01.out)
add_test(NAME t_operand_list_02.out COMMAND t_operand_list_02.out)
add_test(NAME t_operand_map_01.out COMMAND t_operand_map_01.out)
add_test(NAME t_operand_map_02.out COMMAND t_operand_map_02.out)
add_test(NAME t_operand_map_03.out COMMAND t_operand_map_03.out)
add_test(NAME t_root_01.out COMMAND t_root_01.out)
add_test(NAME t_operand_tuple_01.out COMMAND t_operand_tuple_01.out)