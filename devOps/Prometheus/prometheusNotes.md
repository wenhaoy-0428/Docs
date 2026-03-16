[# Prometheus](https://prometheus.io/docs/introduction/overview/)

## What is Prometheus

Prometheus is an open-source systems monitoring and alerting toolkit originally built at SoundCloud. It is now a standalone open-source project and maintained independently of any company.

### Key Features

- **Multi-dimensional data model**: Time series identified by metric name and key-value pairs
- **PromQL (Prometheus Query Language)**: Powerful query language for aggregating and analyzing metrics
- **Pull-based metric collection**: Prometheus scrapes metrics from configured targets
- **No reliance on distributed storage**: Single server nodes are autonomous
- **Pushgateway support**: For short-lived jobs that can't be scraped
- **Visualization**: Built-in expression browser and integration with Grafana
- **Service discovery**: Dynamic target discovery in Kubernetes, Consul, etc.

## Architecture

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│  Services   │     │   Exporters │     │  Pushgateway│
│  (App Code) │     │  (Node Exporter) │  (Short-lived) │
└──────┬──────┘     └──────┬──────┘     └──────┬──────┘
       │                   │                   │
       │    Scrapes        │    Scrapes        │   Push
       ▼                   ▼                   ▼
┌─────────────────────────────────────────────────────────┐
│                     Prometheus Server                   │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐    │
│  │  Retrieval  │  │  TSDB       │  │  HTTP Server│    │
│  │  (Scraper)  │  │  (Storage)  │  │  (API)      │    │
│  └─────────────┘  └─────────────┘  └─────────────┘    │
└─────────────────────────────────────────────────────────┘
       │
       │ Query
       ▼
┌─────────────┐     ┌─────────────┐
│   Grafana   │     │  Alertmanager│
│ (Visualize) │     │  (Alerts)    │
└─────────────┘     └─────────────┘
```

## Core Concepts

### 1. Metrics Types

- **Counter**: Cumulative value that only increases (e.g., total requests)
- **Gauge**: Value that can go up and down (e.g., memory usage)
- **Histogram**: Distribution of values in buckets (e.g., request duration)
- **Summary**: Similar to histogram but with quantile tracking

### 2. Metric Format

```
<metric_name>{<label_name>=<label_value>} <value>
```

Example:
```
http_requests_total{method="GET",status="200"} 1027
```

### 3. Exporters

Exporters are binaries that expose Prometheus metrics from third-party systems:

- **node_exporter**: System metrics (CPU, memory, disk, network)
- **mysql_exporter**: MySQL database metrics
- **postgres_exporter**: PostgreSQL metrics
- **redis_exporter**: Redis metrics
- **nginx_exporter**: Nginx metrics
- **blackbox_exporter**: Black box probing (HTTP, TCP, DNS)

### 4. Service Discovery

Prometheus can automatically discover targets from:
- Kubernetes
- Consul
- AWS EC2
- Azure
- GCP
- Static configurations

## RED Pattern

The RED (Rate, Errors, Duration) pattern is a methodology for instrumenting services, particularly microservices. It provides a standardized way to measure service health from the user's perspective.

### The Three Pillars

| Metric       | Description                | Prometheus Metric Type | What to Measure                           |
| ------------ | -------------------------- | ---------------------- | ----------------------------------------- |
| **Rate**     | Requests per second        | Counter                | `rate(requests_total[5m])`                |
| **Errors**   | Errors per second          | Counter                | `rate(requests_total{status=~"5.."}[5m])` |
| **Duration** | Response time distribution | Histogram              | `histogram_quantile(0.95, ...)`           |

### Why RED over USE?

- **RED** is user-centric: measures from the client's perspective
- **USE** (Utilization, Saturation, Errors) is resource-centric: measures infrastructure
- RED is ideal for request-driven services (APIs, web apps)
- USE is better for resource-heavy workloads (databases, batch jobs)

### Example PromQL Queries

```promql
# Rate: Requests per second
rate(http_requests_total[5m])

# Errors: Error rate percentage
sum(rate(http_requests_total{status=~"5.."}[5m])) / sum(rate(http_requests_total[5m])) * 100

# Duration: P50 (median)
histogram_quantile(0.50, sum(rate(http_request_duration_seconds_bucket[5m])) by (le))

# Duration: P95
histogram_quantile(0.95, sum(rate(http_request_duration_seconds_bucket[5m])) by (le))

# Duration: P99
histogram_quantile(0.99, sum(rate(http_request_duration_seconds_bucket[5m])) by (le))
```

### Golden Signals

The RED pattern complements the four "Golden Signals" from Google's SRE book:

1. **Latency** → RED's Duration
2. **Traffic** → RED's Rate
3. **Errors** → RED's Errors
4. **Saturation** → (USE pattern - CPU, memory, etc.)

## Configuration

### prometheus.yml

```yaml
global:
  scrape_interval: 15s
  evaluation_interval: 15s

alerting:
  alertmanagers:
    - static_configs:
        - targets:
            - alertmanager:9093

rule_files:
  - "rules/*.yml"

scrape_configs:
  - job_name: "prometheus"
    static_configs:
      - targets: ["localhost:9090"]

  - job_name: "node"
    static_configs:
      - targets: ["node-exporter:9100"]

  - job_name: "my-app"
    metrics_path: "/metrics"
    static_configs:
      - targets: ["app:3000"]
```

## PromQL Basics

### Simple Queries

```promql
# Get all values of a metric
metric_name

# Filter by labels
metric_name{label="value"}

# Get specific label
metric_name{label="value"}
```

### Aggregation Functions

```promql
# Sum
sum(http_requests_total)

# Average
avg(cpu_usage_percent)

# Count
count(process_open_fds)

# Rate (per second)
rate(http_requests_total[5m])

# Increase
increase(http_requests_total[5m])

# Top 10
topk(10, http_requests_total)
```

### Operators

```promql
# Arithmetic
metric / 100

# Comparison
metric > 100

# Logical
metric > 100 and instance == "server1"
```

### Example Queries

```promql
# Requests per second
rate(http_requests_total[5m])

# Memory usage percentage
(node_memory_MemTotal_bytes - node_memory_MemAvailable_bytes) / node_memory_MemTotal_bytes * 100

# Error rate
sum(rate(http_requests_total{status=~"5.."}[5m])) / sum(rate(http_requests_total[5m]))

# 95th percentile latency
histogram_quantile(0.95, sum(rate(http_request_duration_seconds_bucket[5m])) by (le))
```

## Metrics

Metrics are **self-defined**. Prometheus doesn't auto-magically know what to measure - you define what you want to track.

### Defining Metrics

```javascript
const httpRequestsTotal = new promClient.Counter({
  name: 'http_requests_total',
  help: 'Total number of HTTP requests',
  labelNames: ['method', 'route', 'status'],
});
```

### Common Metric Types

| Type | Description | Examples |
|------|-------------|----------|
| **Counter** | Always increasing | `requests_total`, `errors_total` |
| **Gauge** | Can go up and down | `current_connections`, `memory_usage_bytes` |
| **Histogram** | Distributions of values | `request_duration_seconds`, `response_size_bytes` |

### Middleware Pattern

Middleware is the standard place to collect HTTP metrics because:

1. **Centralized** - one place tracks all requests
2. **Non-invasive** - doesn't pollute route handlers
3. **Automatic** - applies to all routes

```javascript
app.use((req, res, next) => {
  const start = Date.now();

  res.on('finish', () => {
    // Record metrics AFTER request completes
    httpRequestsTotal.inc({
      method: req.method,
      route: req.path,
      status: res.statusCode
    });
  });

  next();
});
```

### Alternative: Manual Instrumentation

You could also instrument specific routes manually:

```javascript
app.get('/users', (req, res) => {
  httpRequestsTotal.inc({ method: 'GET', route: '/users', status: 200 });
  // ... handler code
});
```

> **Note**: Middleware is cleaner and handles all routes automatically - less code duplication.

### Custom Metrics for Business Logic

You're not limited to HTTP metrics. You can add metrics anywhere in your application:

```javascript
// Custom metric for database queries
const dbQueryDuration = new promClient.Histogram({
  name: 'db_query_duration_seconds',
  help: 'Database query duration',
  labelNames: ['query_name'],
  buckets: [0.01, 0.05, 0.1, 0.5, 1],
});

// Custom metric for business operations
const ordersProcessed = new promClient.Counter({
  name: 'orders_processed_total',
  help: 'Total orders processed',
  labelNames: ['status'], // success, failed
});

// Use in your business logic
app.post('/orders', async (req, res) => {
  const start = Date.now();
  try {
    await processOrder(req.body);
    ordersProcessed.inc({ status: 'success' });
    res.json({ ok: true });
  } catch (e) {
    ordersProcessed.inc({ status: 'failed' });
    res.status(500).json({ error: e.message });
  } finally {
    dbQueryDuration.observe({ query_name: 'create_order' }, (Date.now() - start) / 1000);
  }
});
```

### Shared Registry Pattern

You don't create a new client per module. Use a single registry shared across your application:

```
src/
├── metrics.js      # Define metrics here, export them
├── index.js        # Import, use middleware
├── db.js           # Import, track DB metrics
└── auth.js         # Import, track auth metrics
```

**metrics.js** (shared module):
```javascript
const promClient = require('prom-client');

const register = new promClient.Registry();
promClient.collectDefaultMetrics({ register });

const httpRequestsTotal = new promClient.Counter({
  name: 'http_requests_total',
  help: 'Total HTTP requests',
  labelNames: ['method', 'route', 'status'],
  registers: [register],
});

const dbQueryDuration = new promClient.Histogram({
  name: 'db_query_duration_seconds',
  help: 'DB query duration',
  labelNames: ['query'],
  registers: [register],
});

module.exports = { register, httpRequestsTotal, dbQueryDuration };
```

**index.js** (main app):
```javascript
const { register, httpRequestsTotal } = require('./metrics');

// Use in middleware
app.use((req, res, next) => {
  httpRequestsTotal.inc({ method: req.method, route: req.path, status: res.statusCode });
  next();
});

// Expose /metrics endpoint
app.get('/metrics', async (req, res) => {
  res.set('Content-Type', register.contentType);
  res.send(await register.metrics());
});
```

**db.js** (database module):
```javascript
const { dbQueryDuration } = require('./metrics');

async function getUser(id) {
  const start = Date.now();
  // ... query
  dbQueryDuration.observe({ query: 'getUser' }, (Date.now() - start) / 1000);
}
```

| What | How Many |
|------|----------|
| Registry | One per process |
| Metrics | Many, all registered to that one registry |
| Export | Export metrics objects, import where needed |

All metrics go to the same registry, so `/metrics` endpoint returns everything in one scrape.

## Node.js Demo

### Prerequisites

```bash
# Create a new Node.js project
mkdir prometheus-demo
cd prometheus-demo
npm init -y

# Install required packages
npm install express prom-client
```

### 1. Basic Express App with Prometheus Metrics

```javascript
// app.js
const express = require('express');
const client = require('prom-client');

// Create a Registry
const register = new client.Registry();

// Add default metrics (CPU, memory, etc.)
client.collectDefaultMetrics({ register });

// Create custom counters
const httpRequestsTotal = new client.Counter({
  name: 'http_requests_total',
  help: 'Total number of HTTP requests',
  labelNames: ['method', 'status', 'path'],
  registers: [register],
});

// Create custom gauge
const activeConnections = new client.Gauge({
  name: 'active_connections',
  help: 'Number of active connections',
  registers: [register],
});

// Create custom histogram
const httpRequestDuration = new client.Histogram({
  name: 'http_request_duration_seconds',
  help: 'Duration of HTTP requests in seconds',
  labelNames: ['method', 'status', 'path'],
  buckets: [0.1, 0.5, 1, 2, 5, 10],
  registers: [register],
});

const app = express();

// Middleware to track metrics
app.use((req, res, next) => {
  const start = Date.now();

  res.on('finish', () => {
    const duration = (Date.now() - start) / 1000;
    const path = req.route ? req.route.path : req.path;

    httpRequestsTotal.inc({
      method: req.method,
      status: res.statusCode,
      path: path,
    });

    httpRequestDuration.observe({
      method: req.method,
      status: res.statusCode,
      path: path,
    });
  });

  next();
});

// Track active connections
app.use((req, res, next) => {
  activeConnections.inc();
  res.on('finish', () => activeConnections.dec());
  next();
});

// Metrics endpoint
app.get('/metrics', async (req, res) => {
  res.set('Content-Type', register.contentType);
  res.end(await register.metrics());
});

// Health check
app.get('/health', (req, res) => {
  res.json({ status: 'ok' });
});

// Sample endpoints
app.get('/api/users', (req, res) => {
  res.json([{ id: 1, name: 'John' }, { id: 2, name: 'Jane' }]);
});

app.get('/api/users/:id', (req, res) => {
  res.json({ id: req.params.id, name: 'John' });
});

app.post('/api/users', (req, res) => {
  res.status(201).json({ message: 'User created' });
});

const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
  console.log(`Metrics available at http://localhost:${PORT}/metrics`);
});
```

### 2. View Metrics

```bash
# Start the app
node app.js

# Access the metrics endpoint
curl http://localhost:3000/metrics
```

Example output:
```
# HELP http_requests_total Total number of HTTP requests
# TYPE http_requests_total counter
http_requests_total{method="GET",status="200",path="/api/users"} 5

# HELP http_request_duration_seconds Duration of HTTP requests in seconds
# TYPE http_request_duration_seconds histogram
http_request_duration_seconds_bucket{method="GET",status="200",path="/api/users",le="0.5"} 3

# HELP active_connections Number of active connections
# TYPE active_connections gauge
active_connections 0
```

### 3. Query in Prometheus / Grafana

If using Prometheus directly or Grafana, try these queries:

```promql
# Requests per endpoint
sum by (path) (http_requests_total)

# Request rate
rate(http_requests_total[5m])

# Average duration by endpoint
sum by (path) (rate(http_request_duration_seconds_sum[5m])) / sum by (path) (rate(http_request_duration_seconds_count[5m]))
```

## Alerting

### alertrules.yml

```yaml
groups:
  - name: application
    rules:
      - alert: HighRequestRate
        expr: rate(http_requests_total[5m]) > 100
        for: 5m
        labels:
          severity: warning
        annotations:
          summary: "High request rate detected"
          description: "Request rate is {{ $value }} req/s"

      - alert: HighErrorRate
        expr: sum(rate(http_requests_total{status=~"5.."}[5m])) / sum(rate(http_requests_total[5m])) > 0.05
        for: 2m
        labels:
          severity: critical
        annotations:
          summary: "High error rate"
          description: "Error rate is {{ $value | humanizePercentage }}"
```

## Best Practices

1. **Use appropriate metric types**
   - Counters for cumulative values
   - Gauges for current values
   - Histograms for distributions

2. **Keep cardinality low**
   - Avoid high-cardinality labels (user IDs, IPs)
   - Use bucketed values instead of exact values

3. **Use meaningful names**
   - `<metric_name>_total` for counters
   - Use snake_case
   - Add `_seconds` suffix for duration metrics

4. **Add appropriate help text**
   - Every metric should have a help description

5. **Scrape interval consideration**
   - 15s-30s is typical
   - Shorter for fast-changing metrics

## Related Tools

- **Grafana**: Visualization and dashboards
- **Alertmanager**: Alert routing and notification
- **Pushgateway**: For short-lived batch jobs
- **Thanos**: Long-term storage and high availability
- **Cortex**: Multi-tenant Prometheus as a service
