file(GLOB_RECURSE RexStdTest_LIBS_INC    ${CMAKE_SOURCE_DIR}/source/RexStdTest/include/*.h)
file(GLOB_RECURSE RexStdTest_LIBS_SRC    ${CMAKE_SOURCE_DIR}/source/RexStdTest/src/*.cpp)

add_executable(RexStdTest ${RexStdTest_LIBS_INC} ${RexStdTest_LIBS_SRC})

target_include_directories(RexStdTest PUBLIC ${CMAKE_SOURCE_DIR}/source/RexStdTest/include)
target_include_directories(RexStdTest PUBLIC ${CMAKE_SOURCE_DIR}/source/RexStd/include)
