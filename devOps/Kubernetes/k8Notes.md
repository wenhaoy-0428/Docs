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

必须了解的 Kubernetes 核心概念

Workloads

1. 工作负载（Workloads）

| 资源类型    | 用途                | 适用场景           |
| ----------- | ------------------- | ------------------ |
| Deployment  | 无状态应用          | Web服务、API服务   |
| StatefulSet | 有状态应用          | 数据库、有状态服务 |
| DaemonSet   | 每个节点运行一个Pod | 日志收集、监控代理 |
| Job/CronJob | 批处理任务          | 数据备份、定时任务 |

2. 网络（Networking）

| 资源类型      | 用途                                     |
| ------------- | ---------------------------------------- |
| Service       | 内部服务发现和负载均衡                   |
| Ingress       | HTTP/HTTPS路由（需要Ingress Controller） |
| NetworkPolicy | 网络访问控制                             |

3. 配置（Configuration）

| 资源类型  | 用途                   |
| --------- | ---------------------- |
| ConfigMap | 配置文件、环境变量     |
| Secret    | 敏感信息（密码、密钥） |

4. 存储（Storage）

| 资源类型                    | 用途         |
| --------------------------- | ------------ |
| PersistentVolume (PV)       | 集群存储资源 |
| PersistentVolumeClaim (PVC) | Pod申请存储  |


🎯 学习路径建议

1. 第一阶段（基础）：

   1. Pod → Deployment → Service
   2. ConfigMap → Secret
   3. 基本故障排查

2. 第二阶段（进阶）：

   1. Ingress → 域名访问
   2. PersistentVolume → 数据持久化
   3. Resource Limits → 资源管理

3. 第三阶段（高级）：
   1. Helm → 应用打包
   2. HPA → 自动扩缩容
   3. NetworkPolicy → 网络安全



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

> to make life considerably easier, you don't need to manage each Pod directly. Instead, you can use workload resources that manage a set of pods on your behalf. These resources configure controllers that make sure the right number of the right kind of pod are running, to match the state you specified.

[**Naked Pods will not be rescheduled in the event of a node failure.**](https://kubernetes.io/docs/concepts/configuration/overview/#naked-pods-vs-replicasets-deployments-and-jobs)


https://kubernetes.io/docs/concepts/workloads/pods/#pod-templates


### [Workload Resources](https://kubernetes.io/docs/concepts/workloads/)

A higher abstraction level than a Pod, then the Kubernetes control plane automatically manages Pod objects on your behalf, based on the specification for the workload object you defined.

Kubernetes provides several built-in workload resources:

| 资源类型    | 用途                | 适用场景           |
| ----------- | ------------------- | ------------------ |
| Deployment  | 无状态应用          | Web服务、API服务   |
| StatefulSet | 有状态应用          | 数据库、有状态服务 |
| DaemonSet   | 每个节点运行一个Pod | 日志收集、监控代理 |
| Job/CronJob | 批处理任务          | 数据备份、定时任务 |



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



## Production


### Installation

For a cluster you're managing yourself, the officially supported tool for deploying Kubernetes is [kubeadm](https://kubernetes.io/docs/setup/#production-environment).


#### [Disable Swap](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/#swap-configuration)

```bash
sudo swapoff -a


# 备份 fstab
sudo cp /etc/fstab /etc/fstab.bak

# 注释掉所有包含 swap 的行
sudo sed -i '/swap/s/^/#/' /etc/fstab
```


#### [Add official Kubernetes APT repository](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/#installing-kubeadm-kubelet-and-kubectl)

```bash
sudo apt-get update
# apt-transport-https may be a dummy package; if so, you can skip that package
sudo apt-get install -y apt-transport-https ca-certificates curl gpg


# If the directory `/etc/apt/keyrings` does not exist, it should be created before the curl command, read the note below.
# sudo mkdir -p -m 755 /etc/apt/keyrings
curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.34/deb/Release.key | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpg

# This overwrites any existing configuration in /etc/apt/sources.list.d/kubernetes.list
echo 'deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.34/deb/ /' | sudo tee /etc/apt/sources.list.d/kubernetes.list
```


Install 

```bash
# kubectl is optional for worker nodes
sudo apt-get update
sudo apt-get install -y kubelet kubeadm kubectl
# 锁定版本，防止自动更新
sudo apt-mark hold kubelet kubeadm kubectl
```


#### [Install contianer runtime, specicially containerd](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/#installing-runtime)


To install `containerd`

1. [Add Docker APT repository](https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository)

```bash
# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```

2. install and start containerd

```bash
sudo apt-get install containerd.io

sudo systemctl start containerd
sudo systemctl enable containerd
```

3. [configure](https://kubernetes.io/docs/setup/production-environment/container-runtimes/#install-and-configure-prerequisites)


1. enable `ipv4_forward`

```bash
# sysctl params required by setup, params persist across reboots
cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
net.ipv4.ip_forward = 1
EOF

# Apply sysctl params without reboot
sudo sysctl --system
```

2. [load required kernel modules](https://www.plural.sh/blog/install-kubernetes-ubuntu-tutorial/)

> This is not mentioned in the official doc as kubeadm will not check this, but CNI `flannel` requires.

```bash
sudo modprobe overlay
sudo modprobe br_netfilter


cat <<EOF | sudo tee /etc/modules-load.d/k8s.conf
overlay
br_netfilter
EOF


cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-iptables = 1
net.ipv4.ip_forward = 1
net.bridge.bridge-nf-call-ip6tables = 1
EOF

sudo sysctl --system
```

3. set cgroup driver for kubelet and container runtime

> The `cgroupfs driver` is not recommended when `systemd` is the init system because `systemd` expects a single cgroup manager on the system.

```bash
# to test if systemd is the init system
ps -p 1 -o comm=
```

the cgroup drive of kubelet is default to systemd since v1.22, so we only have to configure container runtime to use the same driver

Follow https://kubernetes.io/docs/setup/production-environment/container-runtimes/#containerd

```bash
# (optional) consider resetting the /etc/containerd/config.toml first if the file is empty
containerd config default | sudo tee /etc/containerd/config.toml

# set SystemdCgroup = true
sudo sed -i 's/SystemdCgroup = false/SystemdCgroup = true/' /etc/containerd/config.toml

sudo systemctl restart containerd
```


Both workder/master nodes need to Proceed the above steps

From this point, only master ndoes should perform.


#### START

1. can use `kubeadm config print` conmannd to print the current config files

```bash
kubeadm config print init-defaults > kubeadm-config.yaml
```

If you have plans to upgrade this single control-plane kubeadm cluster to high availability you should specify the `--control-plane-endpoin`t to set the shared endpoint for all control-plane nodes. 

which corresponds to `controlPlaneEndpoint` in the config file

> Turning a single control plane cluster created without --control-plane-endpoint into a highly available cluster is not supported by kubeadm.

### [Install **CNI** which is used for the communication between pods](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/#pod-network)

3 popular CNI add-ons

include: 
1. Flannel
2. Calico
3. Cilium

ranking from easy to hard in term of learning curve and capability.



For Flannel


add the following to `/run/flannel/subnet.env` according to `https://github.com/kubernetes/kubernetes/issues/70202`

```bash
FLANNEL_NETWORK=10.244.0.0/16
FLANNEL_SUBNET=10.244.0.1/24
FLANNEL_MTU=1450
FLANNEL_IPMASQ=true
```

Also, add `podSubnet` under the network section in the init config file.

```yaml
networking:
    ...
    podSubnet: "10.244.0.0/16"
```


```bash
# start!
sudo kubeadm init --config=kubeadm-config.yaml
 
# Post init for kubectl
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

# kubectl should not be run as sudo
kubectl apply -f <add-on.yaml>
```

#### Install Longhorn

For Storage, install https://longhorn.io/docs/1.10.1/deploy/install/install-with-helm/

Don't forget to use 


```bash
helm show values <release name>
```

to use get the confiration file, and update reclaim policy to `Retain`

```

```





### Helm


[install helm](https://helm.sh/docs/intro/install/)


show helm default configs

```bash
helm show values <release name>
```


show current configs


```bash
helm get values <release name>
```




