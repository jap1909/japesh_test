cmake_minimum_required(VERSION 3.10.2)
find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
#find_package(Rabbitmq-c REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_compile_options(-std=c++14)

include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
  ${jsoncpp_INCLUDE_DIRS}
  include/RESTServer
  
)




add_executable(
  waresense
  src/ApiController.cpp
 # src/RabbitMqController.cpp
  #src/utils.cpp
)

target_link_libraries(waresense stdc++ pthread jsoncpp ${Boost_LIBRARIES} mongo::bsoncxx_shared mongo::mongocxx_shared  rabbitmq ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} )

