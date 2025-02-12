// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#ifdef BAZEL_BUILD
#  include "messages.grpc.pb.h"
#else
#  include "messages.grpc.pb.h"
#endif

#include "opentelemetry/semconv/incubating/rpc_attributes.h"
#include "opentelemetry/trace/context.h"
#include "opentelemetry/trace/span_context_kv_iterable_view.h"
#include "tracer_common.h"
#include "messages_controller.h"

#include "tracer.h"

#include <grpcpp/grpcpp.h>


#include <chrono>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <thread>

using Span        = opentelemetry::trace::Span;
using SpanContext = opentelemetry::trace::SpanContext;
using namespace opentelemetry::trace;

namespace context = opentelemetry::context;
namespace semconv = opentelemetry::semconv;

#include <iostream>
#include <memory>

int main(int argc, char **argv)
{
    // ::InitTracer();
    // Define the server address
    std::string server_address("0.0.0.0:5021");

    // Create the gRPC server
    grpc::ServerBuilder builder;

    // Add listening port
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    // Register service
    MessagesController messages_controller;
    builder.RegisterService(&messages_controller);

    // Build and start the server
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    if (!server) {
        std::cerr << "Failed to start the gRPC server on " << server_address << std::endl;
        return 1;
    }

    std::cout << "gRPC server listening on " << server_address << std::endl;

    // Wait for the server to shutdown
    server->Wait();

    return 0;
}
