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

### Service


In Kubernetes, a **Service** is a method for exposing a network application that is running as one or more Pods in your cluster.

> A single service is bound to one or more pods


Each Pod gets its own IP address (Kubernetes expects network plugins to ensure this). For a given Deployment in your cluster, the set of Pods running in one moment in time could be different from the set of Pods running that application a moment later.

This leads to a problem: if some set of Pods (call them "backends") provides functionality to other Pods (call them "frontends") inside your cluster, how do the frontends find out and keep track of which IP address to connect to, so that the frontend can use the backend part of the workload?

To solve this we can define a service `ClusterIP`

Service 的 ClusterIP 就是给它背后那一群 Pod 起了一个『统一入口』，集群内只要访问这个 IP（或更常见的 DNS 名）就能落到其中某一个 Pod 上.

> Choosing `ClusterIP` makes the Service only reachable from within the cluster.





### Ingress


If your workload speaks HTTP, you might choose to use an Ingress to control how web traffic reaches that workload. Ingress is not a Service type, but it acts as the entry point for your cluster. **An Ingress lets you consolidate your routing rules into a single resource**, so that you can expose multiple components of your workload, running separately in your cluster, behind a single listener.


Regard an Ingress as a routing table, it defines with hostname maps to which service.

In order for the ingress to work, we need a ingress controller which is actually a pod doing the job to handle the routing. example controllers are `ingress-nginx`


```yaml
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: demo-ingress
  namespace: demo
  annotations:
    # 下面两行只有用 nginx-ingress 时才需要，可按需删
    nginx.ingress.kubernetes.io/rewrite-target: /
spec:
  # 指定由哪个 IngressClass 处理；集群里必须已部署同名 Controller
  ingressClassName: nginx
  rules:
  - host: demo.example.com      # 改成本机 hosts 能解析的域名
    http:
      paths:
      - path: /
        pathType: Prefix
        backend:
          service:
            name: nginx-svc
            port:
              number: 80
      - path: /api
        pathType: Prefix
        backend:
          service:
            name: whoami-svc
            port:
              number: 80
  # 如果想强制 HTTPS，可再配 tls: 段落
```

Here, it defines `demo.example.com` maps to `nginx-svc` service. 

Here, it declares that `demo.example.com` should be routed to the Service named `nginx-svc`; it is simply telling the Ingress Controller, **“Look up the Endpoints behind nginx-svc and give me the list.”**

> The Controller then forwards traffic **straight to those Pod IPs** at their target ports, never touching the ClusterIP.

Thus the Service acts only as a label-based finder plus port spec, not as a hop in the data path.



### Ingress Controller


Ingress Controller 本身就是一个（或一组）Pod；给它再配一个 Service of type NodePort 就等于在运行它的每个节点上都挖了一个 30000–32767 范围内的高端口。任何客户端只要访问 <任意节点IP>:那个NodePort 就能把流量送进 Controller Pod，于是整个 Ingress 通路就通了。

当Ingress Controller被设置为Loadbalancer时，asks the **cloud provider** to create an external cloud load balancer， and
a) 向外网申请一个真正的 云负载均衡器（AWS ELB/ALB、GCP GLB、阿里云 SLB…）；
b) 把云 LB 的后端池指向集群里 所有节点 的 NodePort（k8s 会自动创建对应的 NodePort 即使你没显式写）；
c) 把云 LB 的公网 IP 写回 Service 的 status.loadBalancer.ingress 字段。



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


### Install Ingress Controller


```bash
helm repo add ingress-nginx https://kubernetes.github.io/ingress-nginx
helm repo update
helm -n ingress-nginx install ingress-nginx ingress-nginx/ingress-nginx --create-namespace
```

### install MetalLB

If we define Ingress Controller to be type of `NodePort`, later when visiting, we have to define
domain name with port, which is inconnvinent, thus, a better approach is to define a LoadBalancer.

```bash
helm repo add metallb https://metallb.github.io/metallb
kubectl create namespace metallb-system
helm install metallb metallb/metallb
```

Also apply config for configuring ip address pool

```bash
cat > metallb-config.yaml << 'EOF'
apiVersion: metallb.io/v1beta1
kind: IPAddressPool
metadata:
  name: default-pool
  namespace: metallb-system
spec:
  addresses:
  - 10.21.10.200-10.21.10.210  # 📍 使用你的节点网段
---
apiVersion: metallb.io/v1beta1
kind: L2Advertisement
metadata:
  name: default-advertisement
  namespace: metallb-system
spec:
  ipAddressPools:
  - default-pool
EOF
```

> For the addresses, this has to be the same net for your local network, so that others can access.

```bash
kubectl apply -f metallb-config.yaml
```

#### Install Longhorn

For Storage, install https://longhorn.io/docs/1.10.1/deploy/install/install-with-helm/

Don't forget to use 


```bash
helm show values <release name>
```

to use get the confiration file, and update reclaim policy to `Retain`

```bash
reclaimPolicy: Retain
```

###### enable Longhorn UI

Enable xieIngress in `longhorn-values.yaml`

```yaml
ingress:
  # -- Setting that allows Longhorn to generate ingress records for the Longhorn UI service.
  enabled: true
  ingressClassName: nginx
  # -- Hostname of the Layer 7 load balancer.
  host: longhorn.cares-copilot.com
  ....
  annotations:
    # type of authentication
    nginx.ingress.kubernetes.io/auth-type: basic
    # prevent the controller from redirecting (308) to HTTPS
    nginx.ingress.kubernetes.io/ssl-redirect: 'false'
    # name of the secret that contains the user/password definitions
    nginx.ingress.kubernetes.io/auth-secret: basic-auth
    # message to display with an appropriate context why the authentication is required
    nginx.ingress.kubernetes.io/auth-realm: 'Authentication Required '
    # custom max body size for file uploading like backing image uploading
    nginx.ingress.kubernetes.io/proxy-body-size: 10000m

```

create Auth credential for admin using secret with name `basic-auth`, https://longhorn.io/docs/1.10.1/deploy/accessing-the-ui/longhorn-ingress/

```bash
$ USER=<USERNAME_HERE>; PASSWORD=<PASSWORD_HERE>; echo "${USER}:$(openssl passwd -stdin -apr1 <<< ${PASSWORD})" >> auth

# USER=longhorn_admin; PASSWORD=ujFkycnf1Awp; echo "${USER}:$(openssl passwd -stdin -apr1 <<< ${PASSWORD})" >> auth


kubectl -n longhorn-system create secret generic basic-auth --from-file=auth
```

#### Backups

connect Aliyun OSS for backup, configure in the `longhorn-values.yaml` the backupTarget to be `s3://<bucket_name>.<region>` according to [Backup Target Setup](https://longhorn.io/docs/1.10.1/snapshots-and-backups/backup-and-restore/set-backup-target/#set-up-aws-s3-backupstore)

```yaml
defaultBackupStore:
  # -- Endpoint used to access the default backupstore. (Options: "NFS", "CIFS", "AWS", "GCP", "AZURE")
  backupTarget: "s3://local-k8s-longhorn-backups.oss-cn-hongkong/"
  # -- Name of the Kubernetes secret associated with the default backup target.
  backupTargetCredentialSecret: aliyun-oss-access-credentials
  # -- Number of seconds that Longhorn waits before checking the default backupstore for new backups. The default value is "300". When the value is "0", polling is disabled.
  pollInterval: 300
```

Define `aliyun-oss-access-credentials` secret

```bash
kubectl create secret generic aliyun-oss-access-credentials   -n longhorn-system   --from-literal=AWS_ACCESS_KEY_ID=****
--from-literal=AWS_SECRET_ACCESS_KEY=****   
--from-literal=AWS_ENDPOINTS=https://s3.oss-cn-hongkong.aliyuncs.com  --from-literal=AWS_REGION=oss-cn-hongkong --from-literal=VIRTUAL_HOSTED_STYLE=true
```

since Aliyun uses virtual-hosted-addresss (the url schema is `s3://<butcket_name>.<region>` instead of `s3://<butcket_name>@<region>`), we also need to specify `VIRTUAL_HOSTED_STYLE=true` in secret.

#### reccurring jobs

Now, we have a backup target, to run the bakcup daily or monthly, we also need to setup a recurring job to perform such backups.

Through [UI](https://longhorn.io/docs/1.10.1/snapshots-and-backups/scheduling-backups-and-snapshots/), add jobs.

> leave `group` to default so that we can have all volumes without group specified to enjoy the recurring jobs.

> all volumes have to be healthy for the recurring backup job to work.



### Install gitea


```bash
helm repo add gitea-charts https://dl.gitea.com/charts/
kubectl create namespace gitea


helm install gitea gitea-charts/gitea -f gitea-values.yaml -n gitea
```

#### Upgrade from SingleNode to MultiNode Cluster


By default the `values.yaml` indicates the persistence of `gitea.shared.storage` to use `ReadWriteOnce` which means only a single pod can access the volume. This `RWO` only fits when the cluster has a single workder node. When adding a new node, and update the `replicaCount` in the `values.yaml` from 1 to 2, the second pod will not init correctly due to mounting error.


To fix this, either, we define `accessModes: - ReadWriteMany` in advance before initing gitea

```yaml
persistence:
  enabled: true
  create: true
  mount: true
  claimName: gitea-shared-storage
  size: 10Gi
  accessModes:
    - ReadWriteMany
  labels: {}
  storageClass: "longhorn"
```

Or for existing volumes using RWO, the access mode can't be changed once created, so we have to remount the volume and restore the data.

1. downgrade the replicaCount of existing gitea to 0

```bash
helm upgrade gitea gitea-charts/gitea -n gitea \
  --set replicaCount=0 -f gitea-values.yaml
```

> This will cause all pods to be deleted, but the volumes and pvcs are still reserved.

2. delete existing pvc

```bash
kubectl delete pvc gitea-shared-storage -n gitea
```

3. find the corresponding volume bounded to `gitea-shared-storage` pod in the longhorn web ui, click **restore** 
  > This will prompt to create a new volume based on the backup, in this case apart from the new volume name, we have to specify the access mode of the new volume to be `ReadWriteMany`

4. for the newly created `RWX` volume, which is supposed to be **detached**  at this moment, click **create PV/PVC**, this will prompt to enter the PVC name and namespace, specify `gitea-shared-storage` and `gitea`.

5. Now, everything should work, increase the `replicaCount` of the `gitea-values.yaml` back to 2 from 0 to restore the whole system.

### expose ssh

Since Ingress only works with http, while gitea push and many other operations replies on ssh, in the `values.yaml` we also need to specify  `type: LoadBalancer`.


```yaml
  ssh:
    type: LoadBalancer
    port: 22
    # clusterIP:
    loadBalancerIP:
    nodePort:
    externalTrafficPolicy:
    externalIPs:
    ipFamilyPolicy:
    ipFamilies:
    hostPort:
    loadBalancerSourceRanges: []
    annotations: {}
    labels: {}
    loadBalancerClass:
```

> When specifying `LoadBalancer`, k8s will automatically assign an external ip using the LoadBalancer provider of the cluster if has one, here, since we installed a `Metallb`, it works.

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

### Inter Connection

Now, services can be accessed by the external domain name specified by the ingress, however, the provided domain name can not be accessed by the cluster, for example, external users can use `git.cares-copilot.com` to access gitea, but the internal jenkins can't resolve this dns but to use `git-http:3000` which is internally available.

We can resolve this, by having a dns resolver externally that is accessed by the network, or we need to configure the `coredns` that is provided by the cluster.

```bash
# 1. 查看当前的 CoreDNS 配置
kubectl get configmap -n kube-system coredns -o yaml

# 2. 编辑 CoreDNS 配置，添加外部域名转发
kubectl edit configmap -n kube-system coredns
```

add dns resolution to hosts
```
  hosts {
    10.21.10.5 git.cares-copilot.com
    10.21.10.5 jenkins.cares-copilot.com
    10.21.10.5 longhorn.cares-copilot.com
    # 或者使用通配符（如果 CoreDNS 版本支持）
    # 10.21.10.5 *.cares-copilot.com
    fallthrough
  }
```

The final config look like

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: coredns
  namespace: kube-system
data:
  Corefile: |
    .:53 {
        errors
        health {
           lameduck 5s
        }
        ready
        kubernetes cluster.local in-addr.arpa ip6.arpa {
           pods insecure
           fallthrough in-addr.arpa ip6.arpa
           ttl 30
        }
        # 添加 hosts 配置
        hosts {
          10.21.10.5 git.cares-copilot.com
          10.21.10.5 jenkins.cares-copilot.com
          10.21.10.5 longhorn.cares-copilot.com
          # 或者使用通配符（如果 CoreDNS 版本支持）
          # 10.21.10.5 *.cares-copilot.com
          fallthrough
        }
        prometheus :9153
        forward . /etc/resolv.conf
        cache 30
        loop
        reload
        loadbalance
    }
```

To test it out

```bash
# 启动临时调试 Pod
kubectl run -it --rm debug --image=alpine --restart=Never -- sh

# 安装工具
apk add curl

# 测试解析
nslookup jenkins.cares-copilot.com
# 应返回 10.21.10.5

# 测试连通性
curl -I http://jenkins.cares-copilot.com
# 应返回 HTTP 200 或 403（说明能访问 Jenkins）

# 测试 Gitea Webhook endpoint
curl -I http://jenkins.cares-copilot.com/gitea-webhook/post
# 应返回 HTTP 405（说明 endpoint 存在）
```



