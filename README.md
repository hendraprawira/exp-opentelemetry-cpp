# Installing opentelemetry-cpp

1. Install VCPKG.
2. Install dependencies: gtest, benchmark, protobuf.
    
    ```bash
    ./vcpkg install gtest benchmark protobuf
    ```

3. Create directory and clone sources.

    ```bash
    mkdir source && cd source && git clone --recurse-submodules https://github.com/open-telemetry/opentelemetry-cpp
    ```

4. Configure sources using CMAKE, use ```-DWITH_OTLP_GRPC=ON``` to enable gRPC exporter and ```-DWITH_OTLP_HTTP=ON``` to enable HTTP exporter.

    ```bash
    mkdir build && cd build && cmake -DCMAKE_TOOLCHAIN_FILE=[VCPKG root directory]/scripts/buildsystems/vcpkg.cmake ..
    ```

5. Build sources using CMAKE.

    ```bash
    cmake --build . --target all
    ```

6. Install header and library files on installation directory.

    ```bash
    cmake --install . --prefix [opentelemetry-cpp root directory]
    ```

# Using opentelemetry-cpp

1. Set opentelemetry-cpp CMAKE perfix path in CMakeLists.txt file.

    ```bash
    set(OPENTELEMETRY_ROOT "[opentelemetry-cpp root directory]")
    set(CMAKE_PREFIX_PATH "${OPENTELEMETRY_ROOT}")
    ```

2. Add header and library directory in CMakeLists.txt file.

    ```bash
    include_directories(
        ...
        "[opentelemetry-cpp root directory]/include"
    )
    link_directories(
        ...
        "[opentelemetry-cpp root directory]/lib"
    )
    ```

3. Set libraries to be used in CMakeLists.txt file.

    ```bash
    find_package(opentelemetry-cpp CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE absl::bad_variant_access opentelemetry-cpp::api opentelemetry-cpp::ext opentelemetry-cpp::sdk opentelemetry-cpp::logs opentelemetry-cpp::trace opentelemetry-cpp::ostream_span_exporter opentelemetry-cpp::otlp_grpc_exporter)
    ```