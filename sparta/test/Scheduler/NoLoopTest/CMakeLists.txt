project(Scheduler_noloop_test)

add_executable(Scheduler_noloop_test Scheduler_noloop_test.cpp)

include(../../TestingMacros.cmake)

sparta_named_test_no_valgrind(Scheduler_noloop_test Scheduler_noloop_test Scheduler_noloop_test)
