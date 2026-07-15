

## References

[Best practices for traces](https://grafana.com/docs/tempo/latest/set-up-for-tracing/instrument-send/best-practices/#best-practices-for-traces)

OpenTelemetry has semantic conventions for span attributes. They provide a shared vocabulary, which keeps traces consistent and meaningful across services.

[OpenTelemetry semantic conventions](https://github.com/open-telemetry/semantic-conventions/blob/main/docs/README.md)

## Architecture and flow

**Loki 存 logs，Prometheus 存 metrics，Tempo 存 traces。**

在这套 observability 里，调用路径是：

```text
Next.js / s2t / medling
        |
        | 产生 trace / span
        v
      Alloy
        |
        | 转发 traces
        v
      Tempo
        |
        | Grafana 查询
        v
     Grafana UI
```

## Tempo 是干嘛的？

Tempo 是 **trace 后端数据库**。

你的 app 里通过 OpenTelemetry 创建 trace，例如：

```text
用户点击上传音频
  -> Next.js API
    -> s2t service
      -> whisper
      -> database
```

这整条调用链是一个 **trace**，每一步是一个 **span**：

```text
Trace: upload-audio-request

Span 1: POST /api/upload
Span 2: call s2t service
Span 3: run whisper
Span 4: save result to db
Span 5: return response
```

这些 span 需要落库，**Tempo 就是存 trace/span 的地方**。Grafana 官方将 Tempo 定位为分布式追踪后端，可搜索 traces，并把 traces 与 logs、metrics 关联起来。([Grafana Labs][1])

## Alloy 和 Tempo 怎么分工？

**Alloy 是中转站 / collector。**

它负责接收 app 发来的 OTLP traces，然后处理、batch、转发。

**Tempo 是最终存储 traces 的 backend。**

Grafana 文档里也是这个模型：Alloy 运行 tracing pipeline，从应用收集 traces 写入 Tempo；Alloy 的 OTLP receiver 接收 OpenTelemetry 数据，再转发到其他组件。([Grafana Labs][2])

所以整体分工是：

```text
App 不直接查 Tempo
App 只负责发 trace 到 Alloy

Alloy 不负责长期存 trace
Alloy 只负责收集和转发

Tempo 不负责插桩
Tempo 只负责接收、存储、查询 trace
```

### 1. App 里接入 OpenTelemetry

例如 Next.js backend 或 s2t service 里配置：

```ts
OTEL_EXPORTER_OTLP_ENDPOINT=http://alloy:4318
OTEL_SERVICE_NAME=s2t-service
```

App 运行时就会产生 trace。

### 2. Alloy 暴露 OTLP endpoint

Alloy 需要开 OTLP receiver，例如：

```hcl
otelcol.receiver.otlp "default" {
  http {
    endpoint = "0.0.0.0:4318"
  }

  grpc {
    endpoint = "0.0.0.0:4317"
  }

  output {
    traces = [otelcol.processor.batch.default.input]
  }
}
```

### 3. Alloy 转发到 Tempo

```hcl
otelcol.processor.batch "default" {
  output {
    traces = [otelcol.exporter.otlp.tempo.input]
  }
}

otelcol.exporter.otlp "tempo" {
  client {
    endpoint = "tempo:4317"
    tls {
      insecure = true
    }
  }
}
```

端口关系：

```text
App -> Alloy:4318
Alloy -> Tempo:4317
```

Grafana 文档也提到，Alloy/Collector 通常用 OTLP exporter/receiver 把 spans 发给 Tempo。([Grafana Labs][3])

### 4. Grafana 添加 Tempo data source

在 Grafana 里加一个 data source：

```text
Type: Tempo
URL: http://tempo:3200
```

然后就可以在 Grafana 里搜 traces。

## 你要记住的使用场景

Tempo 不是用来看普通日志的。它主要回答这个问题：

```text
这个请求到底慢在哪里？
```

比如：

```text
用户上传音频用了 18 秒
```

你在 Tempo 里看到：

```text
POST /api/upload              18.0s
  call s2t-service             17.2s
    download file               0.4s
    run whisper                15.8s
    save transcript             0.5s
  return response               0.3s
```

这时候你就知道，慢的是 `run whisper`，不是 Next.js，也不是数据库。

## 和 Loki 的区别

| 工具       | 存什么  | 你问它什么                                  |
| ---------- | ------- | ------------------------------------------- |
| Loki       | logs    | 当时发生了什么？报了什么错？                |
| Tempo      | traces  | 这个请求经过了哪些服务？哪一步慢？          |
| Prometheus | metrics | 最近整体是否异常？QPS、错误率、延迟是多少？ |

最终理解：

```text
Prometheus 告诉你：系统慢了
Loki 告诉你：哪里报错了
Tempo 告诉你：这个请求具体卡在哪一步
```

## 最小 docker compose 关系

大概是这样：

```yaml
services:
  alloy:
    image: grafana/alloy
    ports:
      - "4317:4317"
      - "4318:4318"
    depends_on:
      - tempo

  tempo:
    image: grafana/tempo
    ports:
      - "3200:3200"

  grafana:
    image: grafana/grafana
    ports:
      - "3000:3000"
    depends_on:
      - tempo
```

你的 app 不需要连 Grafana，也不需要连 Loki。

它只需要把 traces 发给 Alloy：

```text
OTEL_EXPORTER_OTLP_ENDPOINT=http://alloy:4318
```

然后 Alloy 再发给 Tempo。

> 在配置好 OpenTelemetry SDK + exporter 之后，大部分 span/trace 会自动发送。

## 为什么不直接连 Tempo 而是连接 Alloy？

可以直接连 Tempo，**但生产里通常不建议 App 直接连 Tempo**。更推荐：

```text
App -> Alloy -> Tempo
```

原因不是“必须”，而是 **Alloy 作为 collector / gateway 更好管理**。

### 先说结论

如果是本地 demo：

```text
App -> Tempo
```

可以。

如果是正式一点的环境：

```text
App -> Alloy -> Tempo
```

更合理。

### 为什么中间要 Alloy？

#### 1. App 不应该知道后端细节

如果 App 直接连 Tempo：

```text
OTEL_EXPORTER_OTLP_ENDPOINT=http://tempo:4317
```

以后你换后端，比如：

```text
Tempo -> Grafana Cloud Tempo
Tempo -> Jaeger
Tempo -> Datadog
Tempo -> Honeycomb
```

你就要改所有 App 的配置。

如果中间有 Alloy：

```text
App -> Alloy
Alloy -> Tempo
```

App 永远只知道：

```text
OTEL_EXPORTER_OTLP_ENDPOINT=http://alloy:4318
```

后面换什么，由 Alloy 改配置就行。

---

#### 2. Alloy 可以统一收 logs / metrics / traces

你现在不是只有 traces，而是：

```text
Pino logs -> docker logs -> Alloy -> Loki
Traces -> Alloy -> Tempo
```

以后可能还有：

```text
Metrics -> Alloy -> Prometheus / Mimir
```

所以 Alloy 是统一入口：

```text
App / Docker / Services
        |
        v
      Alloy
     /  |  \
    v   v   v
  Loki Tempo Prometheus
```

这样 observability 入口更清楚。

---

#### 3. Alloy 可以做 batch / retry / queue

App 直接连 Tempo 的话：

```text
App -> Tempo
```

如果 Tempo 短暂不可用，App 的 exporter 可能会失败、丢 span，或者影响应用资源。

中间有 Alloy：

```text
App -> Alloy -> Tempo
```

Alloy 可以帮你做：

```text
batch
retry
buffer
限流
失败处理
```

至少 App 不需要直接承担所有后端波动。

---

#### 4. Alloy 可以统一加工数据

比如你想统一给所有 traces 加标签：

```text
environment = production
region = hk
service.namespace = medling
deployment.version = v1.3.0
```

如果 App 直接连 Tempo，你要在每个服务里配。

如果走 Alloy，可以集中处理。例如：

```text
所有 traces 进 Alloy
Alloy 给它们统一加 metadata
再发给 Tempo
```

这对后面在 Grafana 里筛选很有用：

```text
service.name = s2t-service
environment = production
```

---

#### 5. Alloy 可以采样，减少存储压力

Traces 可能很多。

比如你不想每个成功请求都存，只想存：

```text
错误请求
慢请求
部分正常请求
```

那可以在 collector 层做 sampling。

如果 App 直接连 Tempo，采样逻辑可能要放到每个服务里。

如果走 Alloy：

```text
App 全量发给 Alloy
Alloy 判断哪些发给 Tempo
```

更集中。

---

#### 6. 安全边界更清楚

Tempo 是存储后端，不一定应该暴露给所有 App，尤其不应该公网暴露。

更好的方式是：

```text
App 只能访问 Alloy
Alloy 才能访问 Tempo
Grafana 才能查询 Tempo
```

也就是：

```text
App network -> Alloy
Observability network -> Tempo / Loki / Grafana
```

Tempo 不需要对外暴露，只在内部网络给 Alloy 和 Grafana 用。

---

### 那什么时候可以直接连 Tempo？

可以，尤其是：

```text
本地开发
单服务 demo
临时验证 trace 是否能通
没有 Alloy
```

比如：

```text
Next.js -> Tempo -> Grafana
```

这没问题。

但一旦你有多个服务：

```text
Next.js
s2t
medling
whisper
video-service
```

那就推荐统一：

```text
所有服务 -> Alloy -> Tempo
```

## 你这套系统里应该怎么做？

你现在已经有 Alloy 了，所以最合理的是：

```text
Next.js browser/backend
s2t service
medling service
        |
        | OTLP traces
        v
      Alloy
        |
        v
      Tempo
        |
        v
     Grafana
```

也就是：

```env
OTEL_EXPORTER_OTLP_ENDPOINT=http://alloy:4318
```

而不是：

```env
OTEL_EXPORTER_OTLP_ENDPOINT=http://tempo:4317
```

## 一句话理解

**Tempo 是数据库，Alloy 是接待员。**

App 不应该每个都直接跑去找数据库。
App 把 telemetry 交给 Alloy，Alloy 再统一决定怎么处理、发给谁、加什么标签、要不要采样、失败怎么重试。

所以最终你记这个：

```text
能直连 Tempo，但不优雅。
有 Alloy，就让 App 全部连 Alloy。
Tempo 只负责存 traces。
Alloy 负责收、处理、转发 traces。
```
