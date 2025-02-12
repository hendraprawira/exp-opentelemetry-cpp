
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/batch_span_processor_factory.h"
#include "opentelemetry/sdk/trace/batch_span_processor_options.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/provider.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"

#include "opentelemetry/metrics/provider.h"
#include "opentelemetry/sdk/metrics/aggregation/default_aggregation.h"
#include "opentelemetry/sdk/metrics/export/periodic_exporting_metric_reader.h"
#include "opentelemetry/sdk/metrics/export/periodic_exporting_metric_reader_factory.h"
#include "opentelemetry/sdk/metrics/meter_context_factory.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"
#include "opentelemetry/sdk/metrics/meter_provider_factory.h"

#include "opentelemetry/logs/provider.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/processor.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"


#include "opentelemetry/exporters/otlp/otlp_grpc_exporter.h"
#include "opentelemetry/exporters/otlp/otlp_grpc_exporter_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/context/propagation/global_propagator.h"
#include "opentelemetry/trace/provider.h"

namespace trace_api = opentelemetry::trace;
namespace trace_sdk = opentelemetry::sdk::trace;

namespace metric_sdk = opentelemetry::sdk::metrics;
namespace metrics_api = opentelemetry::metrics;

namespace logs_api = opentelemetry::logs;
namespace logs_sdk = opentelemetry::sdk::logs;


void InitTracer()
{
    // Configure OTLP Exporter Options
    opentelemetry::exporter::otlp::OtlpGrpcExporterOptions options;
    options.endpoint = "http://your-tempo-or-grafana-endpoint:4317";  // Replace with your Tempo/Grafana URL
    options.use_ssl_credentials = false;  // Set true if using HTTPS

    // Create the OTLP Exporter
    auto exporter = opentelemetry::exporter::otlp::OtlpGrpcExporterFactory::Create(options);

    // // Create a Batch Span Processor
    // auto processor = opentelemetry::sdk::trace::BatchSpanProcessorFactory::Create(std::move(exporter));

    // // Add the Span Processor to a Tracer Provider
    // std::vector<std::unique_ptr<opentelemetry::sdk::trace::SpanProcessor>> processors;
    // processors.push_back(std::move(processor));
    // auto context = opentelemetry::sdk::trace::TracerContextFactory::Create(std::move(processors));
    // auto provider = opentelemetry::sdk::trace::TracerProviderFactory::Create(std::move(context));

    // // Set the Global Trace Provider
    // opentelemetry::trace::Provider::SetTracerProvider(provider);

    // // Set the Global Propagator for Trace Context
    // opentelemetry::context::propagation::GlobalTextMapPropagator::SetGlobalPropagator(
    //     opentelemetry::nostd::shared_ptr<opentelemetry::context::propagation::TextMapPropagator>(
    //         new opentelemetry::trace::propagation::HttpTraceContext()));
}
