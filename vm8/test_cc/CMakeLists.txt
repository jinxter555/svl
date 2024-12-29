cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(svlm)

find_package(Catch2 3 REQUIRED /usr/local/lib)


include_directories(SYSTEM "/usr/local/include")

add_executable(t_operand01.out t_operand_01.cc)

# add_library(mylib SHARED lib.cc)

target_link_libraries(t_operand01.out PRIVATE svlm-node svlm-logger Catch2::Catch2WithMain)