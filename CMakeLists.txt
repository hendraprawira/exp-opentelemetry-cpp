cmake_minimum_required(VERSION 3.31.0)
project(be-test VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

set(OPENTELEMETRY_ROOT "/home/mhutomop/Practices/OpenTelemetry/C++/library/source/opentelemetry-cpp")
set(CMAKE_PREFIX_PATH "${OPENTELEMETRY_ROOT}")

include_directories(
    "/home/mhutomop/vcpkg/installed/x64-linux/include"
    "/home/mhutomop/Practices/OpenTelemetry/C++/library/source/opentelemetry-cpp/include"
)
link_directories(
    "/home/mhutomop/vcpkg/installed/x64-linux/lib"
)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.cc src/*.h src/*.hpp)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp)
add_library(shared-objects OBJECT ${SOURCES})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp $<TARGET_OBJECTS:shared-objects>)

find_package(opentelemetry-cpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE absl::bad_variant_access opentelemetry-cpp::api opentelemetry-cpp::ext opentelemetry-cpp::sdk opentelemetry-cpp::logs opentelemetry-cpp::trace opentelemetry-cpp::ostream_span_exporter opentelemetry-cpp::otlp_grpc_exporter)
find_package(gRPC CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts)
find_package(protobuf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
