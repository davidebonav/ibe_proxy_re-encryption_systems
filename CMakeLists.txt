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
# add_executable(test-elgamal-mod test/test-elgamal-mod.c)

# add_executable(main-anon-proxy examples/main-anon-proxy.c)
# add_executable(test-anon-proxy test/test-anon-proxy.c)


# set output directory of executable
set_target_properties(
    main-bb-ibe-system
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}"
)

# set_target_properties(
#         bench-elgamal-mod
#         PROPERTIES
#         RUNTIME_OUTPUT_DIRECTORY "${BENCHMARK_OUTPUT_PATH}"
# )

# set_target_properties(
#         test-elgamal-mod test-anon-proxy
#         PROPERTIES
#         RUNTIME_OUTPUT_DIRECTORY "${TEST_OUTPUT_PATH}"
# )

# serve solo per i file con il main per le library non è lincata
target_link_libraries(main-bb-ibe-system mdr my-lib m gmp nettle hogweed pbc)
target_link_libraries(main-bb-ibe-system mdr my-lib m gmp nettle hogweed pbc)

# target_link_libraries(test-elgamal-mod mdr elgamal-mod m gmp nettle)
# target_link_libraries(test-elgamal-mod mdr elgamal-mod m gmp nettle)


# target_link_libraries(main-anon-proxy mdr anon-proxy m gmp nettle)
# target_link_libraries(test-anon-proxy mdr anon-proxy m gmp nettle)