# Kubernetes

Kubernetes runs your workload by placing containers into **Pods** to run on **Nodes**. *A node may be a virtual or physical machine*, depending on the cluster. Each node is managed by the **control plane** and contains the services necessary to run Pods.

> Services of an APP are containerized and turned into Pods.

## Architecture

The whole architecture of Kubernetes can be classified as 2 major components.

1. Worker nodes


2. Control Plane


![architecture](./Assets/components-of-kubernetes.svg)


### Worker nodes

Which host [Pods](#pods) to run the application workload. More specifically, the worker nodes manages **kubelets** and it is the **kubelets**, agents that run on each node in the cluster that makes sure that containers are running in a Pod. 


### [Control plane](https://kubernetes.io/docs/concepts/overview/components/#control-plane-components)

The control plane manages the worker nodes and the Pods in the cluster. It makes global decisions about the whole cluster. Therefore, there're normally multiple of such components for fault tolerance.

#### API server

The core of Kubernetes' control plane is the [API server](https://kubernetes.io/docs/concepts/overview/components/#kube-apiserver)

The API server exposes an HTTP API that lets end users, different parts of your cluster, and external components communicate with one another.


## Concepts

### Node

A node may be a virtual or physical machine, depending on the cluster

### [Pods](https://kubernetes.io/docs/concepts/workloads/pods/)

A Pod (as in a pod of whales or pea pod) is a group of one or more containers, with shared storage and network resources, and a specification for how to run the containers.

**A Pod is not a process, but an environment for running container(s).**
Therefore, Restarting a container in a Pod should not be confused with restarting a Pod.

> A Pod is similar to **a set of containers with shared namespaces and shared filesystem volumes**

> In the majority of cases, Pods run a single container. The "one-container-per-Pod" model basically means a Pod is just a wrapper of a container.


#### Defining a pod

We can directly write a Pod yaml file to create as well as using cli to add the pod to the cluster. 

**However**, it's almost always to create pods using [workload resource api](#workload-resources), which is an abstract layer over Pods.

[**Naked Pods will not be rescheduled in the event of a node failure.**](https://kubernetes.io/docs/concepts/configuration/overview/#naked-pods-vs-replicasets-deployments-and-jobs)


https://kubernetes.io/docs/concepts/workloads/pods/#pod-templates


### Workload Resources

A higher abstraction level than a Pod, then the Kubernetes control plane automatically manages Pod objects on your behalf, based on the specification for the workload object you defined.


### Define Services

Define services before Workload Resources.

When Kubernetes starts a container, it provides environment variables pointing to all the Services which were running when the container was started. **any Service that a Pod wants to access must be created before the Pod itself,**

For clusterIP:

`port` is the listing port that the service itself listens to. (not defined will be random but matches the service port of an Ingress)
`targetPort` is the destination it should forward to.

> `targetPort` should match an open port of a pod.

For NodePort:

Cluster doesn't have an IP address, but nodes have. Therefore, NodePort Service **statically** assigns a port on **each worker node**. Also necessary bounding to clusterIP service is automatically created. So that We can use the **public** ip of a node and the port to access.

> You have to get a public ip for the node yourself, the node ip itself is private.




## [Volumes](https://www.youtube.com/watch?v=0swOh5C3OVM)

Kubernetes doesn't have data persistence out of box, a `mysql` database pod after restart will lose all its data. Therefore, we have volumes to persist


There are 3 major components of Kubernetes storage

1. Persistent Volume, 
2. Persistent Volume Claim
3. Storage Class


A reference: [Static vs. Dynamic Storage Provisioning: A Look Under the Hood](https://bluexp.netapp.com/blog/cvo-blg-static-vs.-dynamic-storage-provisioning-a-look-under-the-hood#h_h1)


### Persistent Volume 

PV is also a resource so that it can be defined using a yaml file. However, it serves purely as an interface of a storage to cluster. The actual backend storage is created / managed all by ourselves. Therefore, the backend can be a local storage, google cloud and so on. The available storage backend can be found at the Kubernetes websites.

**PV doesn't have namespaces. Therefore, its visible to the whole cluster**

> Therefore, we can regard PV as a representative of an actual storage.

> PVs live in a cluster and their are multiple ones controlled by the administrator of the cluster.


### Persistent Volume Claim

For a pod, or more specifically a container inside a pod to mount a PV. It has to send a request to the cluster to ask for the resource. Such requests are called Persistent Volume Claim. The PVC contains the number of storage that is required, and the cluster will go through all the available PV in the cluster that found a suitable one that can satisfy the claim.

### Storage Class

As mentioned in the [Persistent Volume](#persistent-volume), PV are resource manged by the administrators, and they're mounted to containers by PVC. However, this assumes among requesting a new PVC, there's an available and suitable PV in the cluster. 

To create a PV, the administrators have to **MANUALLY** create one with provisions. This is certainly undesirable. Therefore, to automate the process, administrators can declare Storage Classes with provisioners (the backend, e.g Google Cloud). So that when requested, PV can be dynamically created. 




### kubectl

CLI that used to inspect and manage **cluster resources**, and view logs.

Under the hood it uses the [API server](#api-server).

### Minikube

lets you run Kubernetes **locally**. minikube runs an all-in-one or a multi-node local Kubernetes cluster on your personal computer. For testing purposes.

#### Commands


Apply Pods

```bash
kubectl apply -f path/to/pods.yaml
```

List all contexts. Context stores the user and cluster information used for authentication as well as controlling the resources. More details can be found [kubectl context vs cluster](https://stackoverflow.com/questions/56299440/kubectl-context-vs-cluster)

```bash
kubectl config get-contexts
```


## [Write Yaml](https://kubernetes.io/docs/concepts/overview/working-with-objects/#describing-a-kubernetes-object)

We can regard all the components of Kubernetes as objects, and use yaml file to declare objects.


### Service accounts

Service Accounts are used to authenticate **pods** when they need to interact with the Kubernetes API server or other cluster resources. This identity is useful in various situations, including authenticating to the API server or implementing identity-based security policies.

Here's how it works:

1. Pod Authentication: When a pod needs to make requests to the Kubernetes API server or access other resources within the cluster, it uses its associated Service Account for authentication.
2. Service Account Token: Each pod is mounted with a Service Account token at a specific path within the pod's filesystem. This token is a credential that allows the pod to authenticate with the Kubernetes API server.
3. **RBAC Permissions**: The permissions granted to a pod are determined by the Service Account's associated Role-Based Access Control (RBAC) policies. These policies define what resources the pod can access and what actions it can perform within the cluster.



