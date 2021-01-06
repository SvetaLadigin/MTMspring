cmake_minimum_required(VERSION 3.13)

add_executable(DryA Dry/mainA.c)
add_executable(DryB Dry/mainB.c)

set(EUROVISION_FILES judge.h state.h state.c judge.c utilities.c utilities.h eurovision.h eurovision.c new_map.c new_map.h)

include_directories(. tests)

#link_directories(libmtm/win64)
link_directories(libmtm/csl3)
add_link_options(-std=c99 -no-pie)

link_libraries(mtm)
add_compile_options(-std=c99 -Wall -pedantic-errors -Werror)

add_executable(EurovisionTests tests/test_utilities.h tests/eurovisionTests.c tests/eurovisionTestsMain.c ${EUROVISION_FILES})
add_executable(MapTests tests/test_utilities.h tests/map_example_test.c map.c map.h)
add_executable(FacebookTests euro_tests/tests/main.c ${EUROVISION_FILES})
add_executable(EuroTestFacebook2 tests/eurovisionFunctionalityTests.c ${EUROVISION_FILES})