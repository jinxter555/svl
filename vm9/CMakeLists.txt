cmake_minimum_required(VERSION 3.22.1)





set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(Readline_INCLUDE_DIR /usr/include/readline)
set(Readline_LIBRARY /usr/readline/lib/libreadline.so) # Adjust the library name if necessary
set(Readline_LIBRARY /usr/lib/x86_64-linux-gnu/libreadline.so)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(Readline REQUIRED)
find_package(Catch2 3 REQUIRED /usr/local/lib)

project(svlm)

option(ENABLE_COLOR_OUTPUT "Enable colored compiler output" on)
bison_target(MyParser svlm_grammar.y ${CMAKE_CURRENT_BINARY_DIR}/svlm_parser.cc DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/svlm_parser.hh)
 
flex_target(MyScanner svlm_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/svlm_scanner.cc)





add_executable(${PROJECT_NAME} main.cc svlm_parser.cc svlm_lang.cc svlm_interactive.cc svlm_scanner.cc svlm_parser.cc prompt.cc commandline.cc ${BISON_MyParser_OUTPUTS})

#add_library(svlm-node  number.cc operand.cc operand_visitors.cc operand_tostr.cc ast_node.cc ast_list.cc ast_map.cc my_helpers.cc svlm_lang.cc )
add_library( svlm-node  number.cc operand.cc operand_visitors.cc operand_tostr.cc operand_math.cc ast_node.cc ast_list.cc ast_map.cc 
ast_loop.cc my_helpers.cc svlm_lang.cc ast_case.cc svlm_dyn_loader.cc ast.cc module_registry.cc)
add_library(svlm-logger  scope_logger.cc)

target_link_libraries(${PROJECT_NAME} svlm-node svlm-logger ${Readline_LIBRARY})


include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}  ${CMAKE_CURRENT_SOURCE_DIR}
  "/usr/local/include"
)
include(CTest)
include(Catch)

add_subdirectory(test_cc)
