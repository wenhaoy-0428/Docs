# Web Security

For the majority of notes please refer to [Web Security Academy](https://portswigger.net/web-security/all-materials)

## Bypass IP-based brute-force protection

### Counter Reset

Sometime, a successful login will reset the failure counter and thus, we brute force the password while use correct account to login interchangeably. However, this may not always be the case.

### XFF

In a http request, there is a **"X-Forwarded-For" (XFF)** header that is an optional HTTP header that can be included in an HTTP request. It is used to identify the original IP address of a client when the request has passed through one or more proxy servers or load balancers.

When a client sends an HTTP request to a server through a proxy or load balancer, the proxy server or load balancer can add the "X-Forwarded-For" header to the request, indicating the client's original IP address. Each proxy server or load balancer that the request passes through appends its IP address to the header, resulting in a comma-separated list of IP addresses.

```
GET /example HTTP/1.1
Host: www.example.com
X-Forwarded-For: clientIP, proxy1IP, proxy2IP
```

Therefore, we can change the XFF header to a different value each time, we can bypass the IP-based protection. Normally, this can be just a random integer.

> Note: XFF is not a standard header, even it's commonly used, doesn't mean all backend supports reading it.
