project(Spartaexception_test)

add_executable(SpartaException_test SpartaException_test.cpp)

include(../TestingMacros.cmake)

sparta_test(SpartaException_test SpartaException_test_RUN)
