# Load Balancer | Reverse Proxy

## Load Balancer

Load balancers can also help with **horizontal scaling**, improving performance and availability. Scaling out using commodity machines is more cost efficient and results in higher availability than scaling up a single server on more expensive hardware, called Vertical Scaling.

![lb](./assets/what-is-a-load-balancer.png)

LB is particularly useful when the bussiness grows and muliple servers are needed to handle the volume of requests. **A LB acts like an entry point where its IP is provided to the DNS server.**

1. SSL/TLS Termination

> Decrypts HTTPS traffic at the LB, reducing backend server load.

2. Health Checks

> Monitors server/Pod health to avoid sending traffic to failed instances. This can be done by periodically send requests to a /health endpoint (expects HTTP 200 OK), and other methodlogies.

However, this results in single point failure where a failure of LB will cause the whole network become unreachable.

Therefore, redundenct LB is required to achive **High Availibility**.

To protect against failures, it's common to set up multiple load balancers, either in **active-passive** or **active-active** mode.

1. active-passive 

One NGINX node handles traffic; a standby node takes over if the active fails.

`keepalived` is run on both nodes and (both nodes have to be within the same subset). A floating IP address (Virtual IP) shared between servers in an HA setup. Clients connect to this IP, and Keepalived ensures it’s always assigned to a healthy server.

> So DNS server records the VIP.

2. active-active

2 nodes handles the trafiic simultineously. This requries some DNS Configurations to use round-robin DNS (e.g., assign multiple IPs to lb.yourdomain.com), so that the DNS server is responsible to select the LB.

## Reverse Proxy

A reverse proxy is a web server that centralizes internal services and provides unified interfaces to the public.

Whearas deploying a load balancer is useful when you have multiple servers serving the same function, reverse proxy is useful when the backend servers provide different services.

Often the time, Reverse proxy and load balancer are bundled together in terms of actucal software.




