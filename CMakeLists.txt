cmake_minimum_required(VERSION 3.10)
project(MyProject C)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(TEST_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_STATIC_LIBRARY_PREFIX "lib-")
set(CMAKE_SHARED_LIBRARY_PREFIX "lib-")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -DPBC_SUPPORT")

include_directories(libs-mdr src)

file(GLOB MDR_LIBRARIES_SOURCES libs-mdr/*.c)
file(GLOB MDR_LIBRARIES_HEADERS libs-mdr/*.h)
add_library(mdr ${MDR_LIBRARIES_SOURCES} ${MDR_LIBRARIES_HEADERS})

file(GLOB MY_LIBRARIES_SOURCES src/*.c)
file(GLOB MY_LIBRARIES_HEADERS src/*.h)
add_library(my-lib ${MY_LIBRARIES_SOURCES} ${MY_LIBRARIES_HEADERS})

# add_library(bb-ibe-system src/lib-bb-ibe-system.c src/lib-bb-ibe-system.h)
# add_library(anon-proxy src/lib-anon-proxy.c src/lib-anon-proxy.h)

add_executable(main-bb-ibe-system examples/main-bb-ibe-system.c)
add_executable(main-cbe-gamal-system examples/main-cbe-gamal-system.c)
add_executable(main-hybrid-reenc-system examples/main-hybrid-reenc-system.c)
add_executable(main-ibe-reenc-system examples/main-ibe-reenc-system.c)

add_executable(test-bb-ibe-system tests/test-bb-ibe-system.c)
add_executable(test-cbe-gamal-system tests/test-cbe-gamal-system.c)
add_executable(test-hybrid-reenc-system tests/test-hybrid-reenc-system.c)
add_executable(test-ibe-reenc-system tests/test-ibe-reenc-system.c)

# set output directory of executable
set_target_properties(
    main-bb-ibe-system main-cbe-gamal-system main-hybrid-reenc-system main-ibe-reenc-system 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}"
)

set_target_properties(
    test-bb-ibe-system test-cbe-gamal-system test-hybrid-reenc-system test-ibe-reenc-system
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${TEST_OUTPUT_PATH}"
)

# serve solo per i file con il main per le library non è lincata
target_link_libraries(main-bb-ibe-system mdr my-lib m gmp pbc)
target_link_libraries(main-bb-ibe-system mdr my-lib m gmp pbc)

target_link_libraries(main-cbe-gamal-system mdr my-lib m gmp pbc)
target_link_libraries(main-cbe-gamal-system mdr my-lib m gmp pbc)

target_link_libraries(main-hybrid-reenc-system mdr my-lib m gmp pbc)
target_link_libraries(main-hybrid-reenc-system mdr my-lib m gmp pbc)

target_link_libraries(main-ibe-reenc-system mdr my-lib m gmp pbc)
target_link_libraries(main-ibe-reenc-system mdr my-lib m gmp pbc)

target_link_libraries(test-bb-ibe-system mdr my-lib m gmp pbc)
target_link_libraries(test-bb-ibe-system mdr my-lib m gmp pbc)

target_link_libraries(test-cbe-gamal-system mdr my-lib m gmp pbc)
target_link_libraries(test-cbe-gamal-system mdr my-lib m gmp pbc)

target_link_libraries(test-hybrid-reenc-system mdr my-lib m gmp pbc)
target_link_libraries(test-hybrid-reenc-system mdr my-lib m gmp pbc)

target_link_libraries(test-ibe-reenc-system mdr my-lib m gmp pbc)
target_link_libraries(test-ibe-reenc-system mdr my-lib m gmp pbc)