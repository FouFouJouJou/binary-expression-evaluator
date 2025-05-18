cmake_minimum_required(VERSION 3.25)
project(binary-expression-evaluator VERSION 1.0 LANGUAGES C)
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(EXECUTABLE main)
add_executable(${EXECUTABLE})
target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Werror -g)
target_include_directories(${EXECUTABLE} PUBLIC ${INCLUDE_DIR})
target_sources(${EXECUTABLE} PUBLIC
  ${SOURCE_DIRECTORY}/binary_expression_tree.c
  ${SOURCE_DIRECTORY}/lexer.c
  ${SOURCE_DIRECTORY}/main.c
  ${SOURCE_DIRECTORY}/postfix.c
)
