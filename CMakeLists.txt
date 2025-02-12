cmake_minimum_required(VERSION 3.21.0)
project(be-test VERSION 0.2.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/home/hendra/otels/lib/cmake/opentelemetry-cpp" ${CMAKE_PREFIX_PATH})

# Collect all source files except app.cpp
file(GLOB_RECURSE SOURCES src/*.cpp src/*.cc src/*.h src/*.hpp)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp)

# Add the executable, including all necessary source files
add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp
    ${SOURCES}
)

# Find and link dependencies
find_package(opentelemetry-cpp CONFIG REQUIRED)
set(opentelemetry-cpp_DIR /home/hendra/otels/include/opentelemetry)

find_package(gRPC CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts)

find_package(protobuf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

# Include and link OpenTelemetry
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENTELEMETRY_CPP_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENTELEMETRY_CPP_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
