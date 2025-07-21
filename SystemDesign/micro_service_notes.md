# Microservice

Microservices can be described as a suite of independently deployable, small, modular services, this moduler architecture allows developers to integrate changes more often.

However, Microservices can add complexity in terms of deployments and operations.


## Service Discovery

For different services to be able to communiate each other, they first need to know each other's location or API URL.

we can of course hard code each one API in each service, but a better approach is to have a **service discovery** node.

There are 2 types of service discovery

1. Client Side Service Dsicovery
2. Server Side Service Dsicovery

A quick exaplanation can be found [What is service discovery really all about? - Microservices Basics Tutorial](https://www.youtube.com/watch?v=GboiMJm6WlA)


## [How do Microservices Communicate With Each Other?](https://www.geeksforgeeks.org/how-do-microservices-communicate-with-each-other/)

https://www.index.dev/blog/implementing-microservices-for-scalability-maintainability


https://medium.com/design-microservices-architecture-with-patterns/microservices-asynchronous-message-based-communication-6643bee06123


### RPC

1. refer to CS241

The major components of a RPC system includes

1. Client/Server Stubs: Act as local proxies, handling serialization/deserialization.

> Client Stub (Proxy): Marshals (serializes) parameters into a network-transmittable format.
> Server Stub (Skeleton): Unmarshals (deserializes) parameters and invokes the server procedure.

2. Interface Definition Language (IDL): Defines service interfaces (e.g., methods, parameters). An IDL compiler generates client/server stubs.

> This is a tool in modern rpc frameworks, where user can define the parameters and methods to **autogenerate** stubs in different programming languages.

3. Client Application: Initiates the remote call.
4. Server Application: Executes the remote procedure and returns results.


## REST API vs. RPC: Key Differences and When to Use Each

## 🏗️ Architectural Styles
| **Aspect**        | **REST API**              | **RPC**                  |
| ----------------- | ------------------------- | ------------------------ |
| **Paradigm**      | Resource-oriented (nouns) | Action-oriented (verbs)  |
| **Communication** | Client-server (stateless) | Direct method invocation |
| **Coupling**      | Loose coupling            | Tight coupling           |

## 🛠️ Technical Implementation
| **Feature**     | **REST**                      | **RPC**                         |
| --------------- | ----------------------------- | ------------------------------- |
| **Transport**   | HTTP/HTTPS only               | HTTP, TCP, WebSockets, etc.     |
| **Data Format** | JSON/XML (human-readable)     | JSON, Protobuf, Thrift (binary) |
| **Caching**     | Native (HTTP caching headers) | Custom implementation required  |
| **Tooling**     | OpenAPI, Postman, Swagger     | gRPC, Thrift, JSON-RPC          |

## 🚀 Performance Characteristics
| **Metric**     | **REST**                            | **RPC**                            |
| -------------- | ----------------------------------- | ---------------------------------- |
| **Overhead**   | Higher (HTTP headers, text formats) | Lower (binary protocols)           |
| **Latency**    | Moderate                            | Ultra-low (e.g., gRPC over HTTP/2) |
| **Throughput** | Good                                | Excellent                          |

## 🌐 Use Case Comparison
### When to Choose **REST API**
✅ **Public-facing services** (e.g., Stripe API)  
✅ **Resource-centric operations** (CRUD on `users`, `products`)  
✅ **Web/mobile client compatibility**  
✅ **Stateless scalability needs**  

### When to Choose **RPC**
✅ **Internal microservices communication**  
✅ **Performance-critical systems** (trading, IoT)  
✅ **Strong typing requirements**  
✅ **Stateful interactions** (e.g., real-time games)  


### [System Design Global Payment Processing | Paypal](https://www.youtube.com/watch?v=7MXV7RfNtv0&t=1206s)

