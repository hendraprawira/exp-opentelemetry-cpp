/*
 * Copyright PT LEN INNOVATION TECHNOLOGY
 *
 * THIS SOFTWARE SOURCE CODE AND ANY EXECUTABLE DERIVED THEREOF ARE PROPRIETARY
 * TO PT LEN INNOVATION TECHNOLOGY, AS APPLICABLE, AND SHALL NOT BE USED IN ANY WAY
 * OTHER THAN BEFOREHAND AGREED ON BY PT LEN INNOVATION TECHNOLOGY, NOR BE REPRODUCED
 * OR DISCLOSED TO THIRD PARTIES WITHOUT PRIOR WRITTEN AUTHORIZATION BY
 * PT LEN INNOVATION TECHNOLOGY, AS APPLICABLE.
 */

/*
 =================================================================================================================
 Name        : ir_video_control_controller.cpp
 Author      : Angga Gemilang
 Version     : 0.2.0 27/06/2024
 Description : Controller for IR Video Power Control setting
 =================================================================================================================
*/
#include "opentelemetry/semconv/incubating/rpc_attributes.h"
#include "opentelemetry/trace/context.h"
#include "opentelemetry/trace/span_context_kv_iterable_view.h"
#include "tracer_common.h"
#include "messages_controller.h"

using Span        = opentelemetry::trace::Span;
using SpanContext = opentelemetry::trace::SpanContext;
using namespace opentelemetry::trace;

namespace context = opentelemetry::context;
namespace semconv = opentelemetry::semconv;
MessagesController::MessagesController() = default;


grpc::Status MessagesController::Greet
(
    grpc::ServerContext* context,
    const grpc_example::GreetRequest* request,
    grpc_example::GreetResponse* reply
)
{
    StartSpanOptions options;
    options.kind = SpanKind::kServer;
    // extract context from grpc metadata
    GrpcServerCarrier carrier(context);

    auto prop        = context::propagation::GlobalTextMapPropagator::GetGlobalPropagator();
    auto current_ctx = context::RuntimeContext::GetCurrent();
    auto new_context = prop->Extract(carrier, current_ctx);
    options.parent   = GetSpan(new_context)->GetContext();

    std::string span_name = "GreeterService/Greet";
    auto span             = get_tracer("grpc")->StartSpan(span_name,
                                                          {{semconv::rpc::kRpcSystem, "grpc"},
                                                           {semconv::rpc::kRpcService, "GreeterService"},
                                                           {semconv::rpc::kRpcMethod, "Greet"},
                                                           {semconv::rpc::kRpcGrpcStatusCode, 0}},
                                                          options);
    auto scope            = get_tracer("grpc")->WithActiveSpan(span);

    // Fetch and parse whatever HTTP headers we can from the gRPC request.
    span->AddEvent("Processing client attributes");

    const std::string &req = request->request();
    std::cout << '\n' << "grpc_client says: " << req << '\n';
    std::string message = "The pleasure is mine.";
    // Send response to client
    span->AddEvent("Response sent to client");

    span->SetStatus(StatusCode::kOk);
    // Make sure to end your spans!
    span->End();

    return this->get_messages_response(request, reply, "aa");

}


grpc::Status MessagesController::get_messages_response
(
    const grpc_example::GreetRequest* request,
    grpc_example::GreetResponse* reply,
    const std::string &resp
)
{
      // Create a SpanOptions object and set the kind to Server to inform OpenTel.

    reply->set_response("IR Video Power AA has successfully set");
    return grpc::Status::OK;
}
