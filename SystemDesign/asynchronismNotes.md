# Message Queue

Why Message queue is important and what problem it solves

1. [What is a Message Queue and When should you use Messaging Queue Systems Like RabbitMQ and Kafka](https://www.youtube.com/watch?v=W4_aGb_MOls)
2. [Kafka Tutorial for Beginners | Everything you need to get started](https://www.youtube.com/watch?v=QkdkLdMBuL0)

> This video also explains what proble message queue solves with kafka


## [Kafka](https://www.youtube.com/watch?v=IsgRatCefVc)

Producers send messages to topics, and Kafka’s partitioner (default: round-robin or key-based hashing) determines which partition (and thus broker) the message lands in.

Brokers are chosen based on partition leadership (**each partition has a leader broker**) for data replication


### Message Brokers

each broker has multiple topics, and the number of topics is the same across brokers. Each broker only stores certain partitions of these topics. When a producer sends data, it goes to a particular broker and is stored in a partition. Then a consumer consumes from that partition and acks.


### Consumer Groups

consumers subscribe to topics. However, in Kafka, consumers are typically part of consumer groups. **Each partition is consumed by only one** consumer within a group. So, multiple consumers in the same group won't read the same partition; they split the partitions among themselves. 

However, as how [retention](#retention) works, mutiple consumer group can subscribe to the same topic partition, so that there still can be multiple consumers consuming the same messages.

> It's the bussiness logic to isolate same services from consuming the same partition which may result in race conditon.


### Retention

In Kafka, data retention is independent of consumer acknowledgments (acks), which means messages can be deleted due to retention policies even if they haven’t been consumed or acknowledged.

> There is no acknowledgement.

Consumers track their position in a topic partition using offsets (a numeric identifier for each message). If a consumer crashes or restarts, it resumes reading from the last committed offset.

> It's the consumer's responsibility to persist the offset.


https://www.youtube.com/watch?v=Ch5VhJzaoaI


https://www.youtube.com/watch?v=IsgRatCefVc