cmake_minimum_required(VERSION 3.22.1)



set(CMAKE_BUILD_TYPE Debug)
set(Readline_INCLUDE_DIR /usr/include/readline)
set(Readline_LIBRARY /usr/readline/lib/libreadline.so) # Adjust the library name if necessary
set(Readline_LIBRARY /usr/lib/x86_64-linux-gnu/libreadline.so)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(Readline REQUIRED)

project(svlm)


bison_target(MyParser svlm_grammar.y ${CMAKE_CURRENT_BINARY_DIR}/svlm_parser.cc
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/svlm_parser.hh)

flex_target(MyScanner svlm_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/svlm_scanner.cc)





add_executable(${PROJECT_NAME} 
  main.cc svlm_parser.cc svlm_ast.cc svlm_interactive.cc svlm_scanner.cc 
  svlm_parser.cc prompt.cc commandline.cc
  ${BISON_MyParser_OUTPUTS}
)

add_library(svlm-node  ast.cc number.cc operand.cc ast_map.cc ast_list.cc operand_tostr.cc operand_math.cc operand_visitors.cc que_node.cc my_helpers.cc )
add_library(svlm-logger  scope_logger.cc)

target_link_libraries(${PROJECT_NAME} svlm-node svlm-logger ${Readline_LIBRARY})


include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}  ${CMAKE_CURRENT_SOURCE_DIR}
  )

