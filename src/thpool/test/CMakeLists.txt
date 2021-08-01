# Scan source dir for standart source files and exclude main.cpp

include_directories(${PROJECT_SOURCE_DIR}/src)

set(REQUIRED_SOURCES)

if(NOT HAVE_PTHREAD_BARRIER)
    add_definitions(-DNO_PTHREAD_BARRIER=1)
    list(APPEND REQUIRED_SOURCES ${PROJECT_SOURCE_DIR}/src/pthread_barrier.c)
endif()

set(TEST_LIBRARIES Threads::Threads)
if(BUILD_SHARED_LIBS)
    list(APPEND TEST_LIBRARIES thpool_shared)
else()
    list(APPEND TEST_LIBRARIES thpool)
endif()

# Build tests
add_executable(test_thpool
    thpool_test.c
    thpool/thpool_no_work.c
    thpool/thpool_api.c
    thpool/thpool_pause_resume.c
    thpool/thpool_wait.c
    thpool/thpool_worker_try_once.c
    ${REQUIRED_SOURCES}
)
target_link_libraries(test_thpool ${TEST_LIBRARIES})
#target_compile_options(test_thpool PRIVATE -Wdeclaration-after-statement)
add_test(
    NAME test_thpool
    COMMAND $<TARGET_FILE:test_thpool>
)
set_tests_properties(test_thpool PROPERTIES LABELS "thpool")

add_executable(bench_thpool thpool_bench.c ${REQUIRED_SOURCES})
target_link_libraries(bench_thpool ${TEST_LIBRARIES})
