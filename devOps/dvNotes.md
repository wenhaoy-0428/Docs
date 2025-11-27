## Terraform

**What is Terraform?**

Terraform is an Infrastructure as Code (IaC) tool developed by HashiCorp. It allows you to define and provision infrastructure resources using declarative configuration files.

**Purpose:**
- **Infrastructure Provisioning**: Automates the creation, modification, and deletion of cloud resources (e.g., virtual machines, networks, storage)
- **Multi-Cloud Support**: Works with AWS, Azure, GCP, and many other cloud providers
- **Version Control**: Infrastructure configurations can be stored in Git, enabling collaboration and history tracking
- **Idempotent**: Running the same configuration multiple times produces the same result

**Use Case Example:**
Use Terraform to automatically create ECS instances on the cloud, set up networking, and provision the necessary infrastructure before deploying applications.

## Ansible

**What is Ansible?**

Ansible is an open-source automation tool for configuration management, application deployment, and task automation. It uses a simple, human-readable YAML syntax.

**Purpose:**
- **Configuration Management**: Automates the configuration of servers and applications
- **Agentless**: Works over SSH, no need to install agents on target machines
- **Idempotent**: Ensures the desired state is achieved without making unnecessary changes
- **Orchestration**: Coordinates complex deployments across multiple servers

**Important Note:**
Yes! When Ansible runs, it WILL change your local server configuration. Therefore, you should use virtual machines or temporary servers for testing. If using temporary servers, Terraform can automatically create and delete them.

**Use Case Example:**
After Terraform creates the infrastructure, Ansible configures the ECS instances by installing software, setting up services, configuring files, and preparing the environment for application deployment.


## The Complete DevOps Workflow

Here's how these tools work together:

1. **Terraform** → Creates ECS instances and infrastructure on the cloud
2. **Ansible** → Configures the ECS instances (installs Docker, sets up environment, etc.)
3. **Docker** → Pulls and runs the application containers

This complete workflow enables automated testing and deployment cycles!


An example in Cloud Native Dev may look like the following

1. Terraform - 创建基础设施

```yaml
# main.tf - 创建云服务器
resource "alicloud_instance" "test_environment" {
  instance_type = "ecs.g6.large"  # 与生产环境相同规格
  image_id      = "ubuntu_20_04_x64_20G_alibase_20210910.vhd"
  
  # 网络配置
  vswitch_id = alicloud_vswitch.test.id
  security_groups = [alicloud_security_group.test.id]
  
  # 资源标签
  tags = {
    Name    = "prod-like-test-${timestamp()}"
    Project = "ci-testing"
    Owner   = "devops"
  }
}

# 输出服务器信息，供后续步骤使用
output "ecs_ip" {
  value = alicloud_instance.test_environment.public_ip
}

output "ecs_id" {
  value = alicloud_instance.test_environment.id
}
```

2. Ansible - 配置服务器

```yaml
# playbook.yml - 准备服务器环境
- name: 配置生产级别ECS环境
  hosts: "{{ target_host }}"
  become: yes
  vars:
    docker_version: "20.10"  # 与生产环境相同
    app_user: "appuser"
    
  tasks:
    - name: 安装Docker
      apt:
        name:
          - docker.io
          - docker-compose
        state: present
        
    - name: 创建应用用户
      user:
        name: "{{ app_user }}"
        groups: docker
        shell: /bin/bash
        
    - name: 配置系统参数（与生产一致）
      sysctl:
        name: "{{ item.name }}"
        value: "{{ item.value }}"
      loop:
        - { name: net.core.somaxconn, value: '1024' }
        - { name: vm.swappiness, value: '10' }
        
    - name: 创建应用目录
      file:
        path: /opt/{{ app_user }}/app
        state: directory
        owner: "{{ app_user }}"
        group: "{{ app_user }}"
```

3. Docker - 部署应用

```yaml
# docker-compose.prod-like.yml
version: '3.8'
services:
  app:
    build: .
    image: myapp:${GIT_COMMIT}
    networks:
      app_net:
        ipv4_address: 192.168.100.10  # 固定IP，模拟生产
    environment:
      - DATABASE_URL=postgresql://user:pass@db:5432/app
      - REDIS_URL=redis://redis:6379
    depends_on:
      - db
      - redis
      
  db:
    image: postgres:13  # 与生产相同版本
    networks:
      app_net:
        ipv4_address: 192.168.100.20
    environment:
      POSTGRES_DB: app
      POSTGRES_USER: user
      POSTGRES_PASSWORD: pass
      
  redis:
    image: redis:6-alpine
    networks:
      app_net:
        ipv4_address: 192.168.100.30

networks:
  app_net:
    driver: bridge
    ipam:
      config:
        - subnet: 192.168.100.0/24  # 模拟生产网段
```

4. jenkins


```bash
// Jenkinsfile
pipeline {
    agent any
    
    stages {
        stage('创建测试环境') {
            steps {
                script {
                    // 1. Terraform 创建ECS
                    sh '''
                        cd terraform/
                        terraform init
                        terraform apply -auto-approve
                    '''
                    
                    // 获取ECS IP
                    env.ECS_IP = sh(
                        script: 'cd terraform && terraform output -raw ecs_ip',
                        returnStdout: true
                    ).trim()
                }
            }
        }
        
        stage('配置服务器') {
            steps {
                script {
                    // 2. Ansible 配置ECS
                    sh """
                        ansible-playbook -i '${env.ECS_IP},' playbooks/setup-ecs.yml \
                          --extra-vars "target_host=${env.ECS_IP}" \
                          --user=root \
                          --private-key=~/.ssh/aliyun_key
                    """
                }
            }
        }
        
        stage('部署应用') {
            steps {
                script {
                    // 3. 部署Docker应用
                    sh """
                        ssh -o StrictHostKeyChecking=no root@${env.ECS_IP} "
                          git clone https://github.com/your/app.git /opt/appuser/app
                          cd /opt/appuser/app
                          docker-compose -f docker-compose.prod-like.yml up -d
                        "
                    """
                }
            }
        }
        
        stage('运行测试') {
            steps {
                script {
                    // 4. 在生产级别环境中测试
                    sh """
                        ssh root@${env.ECS_IP} "
                          docker-compose -f docker-compose.prod-like.yml exec app npm test
                          docker-compose -f docker-compose.prod-like.yml exec app npm run test:integration
                          
                          # 健康检查
                          curl -f http://192.168.100.10:3000/health || exit 1
                        "
                    """
                }
            }
        }
    }
    
    post {
        always {
            script {
                // 收集日志
                sh """
                    ssh root@${env.ECS_IP} "
                      docker-compose -f docker-compose.prod-like.yml logs > test_logs.txt
                    " || true
                """
            }
        }
        success {
            script {
                echo "✅ 测试成功！环境保持运行用于调试"
                echo "🔗 访问地址: http://${env.ECS_IP}"
            }
        }
        failure {
            script {
                echo "❌ 测试失败，清理环境..."
                sh '''
                    cd terraform/
                    terraform destroy -auto-approve
                '''
            }
        }
    }
}
```