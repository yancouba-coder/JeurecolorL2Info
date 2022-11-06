cmake_minimum_required(VERSION 2.6)


project(Recolor_TDM8_B C)
include(CTest)
enable_testing()



set(CMAKE_C_FLAGS "-std=c99 -g  -Wall --coverage")

add_library(game game_io.c game.c)


add_executable(recolor_text recolor_text.c)
target_link_libraries(recolor_text  game)

add_executable(recolor_solve recolor_solve.c)
target_link_libraries(recolor_solve  game)

add_executable(test_hchouchane test_game_hchouchane.c)
target_link_libraries(test_hchouchane  game)

add_executable(test_abocamara test_game_abocamara.c)
target_link_libraries(test_abocamara  game)

add_executable(test_evanopstal test_game_evanopstal.c)
target_link_libraries(test_evanopstal  game)

add_executable(test_ydiatta test_game_ydiatta.c)
target_link_libraries(test_ydiatta  game)



add_test(cm_test_hchouchane test_hchouchane )

add_test(cm_test_abocamara test_abocamara )

add_test(cm_test_evanopstal test_evanopstal )

add_test(cm_test_ydiatta test_ydiatta )