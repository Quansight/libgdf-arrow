#pass the dependency libraries as optional arguments using ${ARGN}
#NOTE the order of libraries matter, so try to link first with the most high level lib
function(configure_test TEST_NAME Tests_SRCS)
    message(STATUS "${TEST_NAME} will link against: gdf-arrow arrow")
    set(HOST_COMPILER_DEBUG_FLAGS "-g -O0")

    cuda_add_executable(${TEST_NAME} ${Tests_SRCS} OPTIONS "${HOST_COMPILER_DEBUG_FLAGS}")
    set_target_properties(${TEST_NAME} PROPERTIES COMPILE_FLAGS "${HOST_COMPILER_DEBUG_FLAGS}")
    
    target_link_libraries(${TEST_NAME} gmock_main gmock GTest::GTest gdf-arrow arrow)

    #register the target as CMake test so we can use ctest for this executable
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

## Main ##

enable_testing()

# Configure unit tests with Google Test
# -------------------
message(STATUS "******** Configuring tests ********")

message(STATUS "******** Tests are ready ********")
