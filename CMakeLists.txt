# cmake 最低版本要求
cmake_minimum_required(VERSION 3.5)
# 项目信息
project(SunnyRpc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -std=c++11")
set(SOURCE_FILES src/main.cpp include/rpc_server.h include/rpc_method.h include/rpc_socket.h src/rpc_socket.cpp include/commons.h)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

# http://aigo.iteye.com/blog/2295228
set(THIRD_INCLUDE_DIR /usr/local/Cellar/protobuf/2.6.1/include)
set (BOOST_ROOT /usr/local/Cellar/boost/1.60.0_1/)

find_package(Boost 1.60 REQUIRED)
if (Boost_FOUND)
    include_directories (${Boost_INCLUDE_DIR})
endif ()

add_subdirectory(proto)
include_directories(proto include ${THIRD_INCLUDE_DIR})
# 指定生成目标
add_executable(SunnyRpc ${SOURCE_FILES})
target_link_libraries(SunnyRpc ${Boost_LIBRARIES} echo ${PROTOBUF_LIBRARY})

message("system: ${CMAKE_SYSTEM_PREFIX_PATH}")
message("boost root: ${BOOST_ROOT}")
message("protobuf root: ${PROTOBUF_FOUND} ${PROTOBUF_INCLUDE_DIRS}")
message("cxx: ${CMAKE_CXX_FLAGS}")
