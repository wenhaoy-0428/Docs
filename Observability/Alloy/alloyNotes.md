# Alloy

Alloy collects metrics, logs, traces, and profiles in one unified solution. Instead of running separate collectors for each signal type, you configure a single tool that handles all your telemetry needs.

##  [How Grafana Alloy works](https://grafana.com/docs/alloy/latest/introduction/how-alloy-works/)

Understanding the architecture and design of Alloy helps you use it effectively.

### Where Alloy fits
A typical observability setup has three layers: data sources that generate telemetry, collection tools that gather and process it, and storage backends with visualization frontends for querying and exploring data.

Alloy operates in the collection layer, sitting between your data sources and your storage backends. It acts as the bridge between them, performing three main functions in your telemetry pipeline.

#### Collect telemetry data

Alloy gathers telemetry from any source in your infrastructure. You can configure it to scrape Prometheus endpoints for metrics or set up receivers to accept data pushed via the OpenTelemetry protocol. It tails log files and reads from system outputs to capture application and infrastructure logs. Service discovery automatically finds resources in Kubernetes, Docker, or cloud environments without requiring static configuration. You can also integrate with databases, message queues, and other systems to capture telemetry from specialized sources.

#### Transform and process data

Processing telemetry before sending it to backends optimizes costs and improves data quality. Create filters to drop unwanted data or redact sensitive information like tokens and credentials from logs before they reach storage. Add labels, metadata, or contextual information to enrich your data—for example, extract a cloud provider name from instance IDs to create useful aggregation labels. Standardize attribute names across services when different teams use inconsistent naming conventions. Implement sampling strategies to reduce high-volume data while preserving the signal you need for troubleshooting. Convert between formats, such as transforming Prometheus metrics to OpenTelemetry format, to ensure compatibility with your backends. Define routing rules to send different types of data to different destinations based on your operational requirements.

#### Send to backends

Alloy delivers processed telemetry to any storage system you choose. Send data to Grafana Cloud for managed observability, or export to your self-managed Grafana stack components. Connect to any Prometheus-compatible database for metrics and any OpenTelemetry-compatible backend for all signal types. Write to multiple destinations simultaneously, sending the same data to different systems or routing different data types to specialized backends.


## Components

Components are the building blocks of Alloy. Each component performs a single task, such as retrieving secrets, collecting metrics, or processing data.

Components are the defining feature of Alloy. They’re reusable pieces of business logic that perform a single task, such as retrieving secrets or collecting Prometheus metrics. You can wire them together to form programmable pipelines of telemetry data.

### Every component has **two main** parts:

* **Arguments**: Settings that configure the component’s behavior. These are the attributes and blocks you define inside the component block.
* **Exports**: Values that the component makes available to other components. The running component generates these exports and they can change over time.

When Alloy loads your configuration:

1. It reads the arguments you provided in each component block.
2. It creates a running instance of the component with those arguments.
3. The component starts its work and may update its exports as it runs.
4. Other components can reference these exports in their arguments.

### Component Syntax

```json
COMPONENT_NAME "LABEL" {
  // Arguments (attributes and nested blocks)
  attribute_name = "value"

  nested_block {
    setting = "value"
  }
}
```

> The body is made of the component’s supported arguments and supported nested blocks.

Typically components are system defined by Alloy, which defines their arguments and exports, here's a list of reference. [Component Reference](https://grafana.com/docs/alloy/latest/reference/components/)

Also, you definitely can define your own component, referring to [Custom Components](https://grafana.com/docs/alloy/latest/get-started/components/custom-components/).


https://grafana.com/docs/alloy/latest/get-started/components/#component-syntax