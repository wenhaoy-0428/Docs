## Jenkins

### What is Jenkins?

Jenkins is an open-source automation server that enables developers to build, test, and deploy applications efficiently. It's a key tool in DevOps practices that helps implement Continuous Integration (CI) and Continuous Deployment (CD) pipelines.

> Jenkins is a self-contained **Java program** itself.

**Key Benefits:**
- Automates repetitive tasks in the software development lifecycle
- Integrates with various tools and technologies
- Provides early feedback on code changes
- Reduces manual errors and deployment time
- Supports distributed builds across multiple machines

### Basic Concepts

#### 1. **Job/Project**
- A job is a runnable task in Jenkins
- Contains configuration for what to build, when to build, and how to build
- Types include:
  - **Freestyle Project**: Simple, GUI-based configuration
    
    >  [Freestyle projects feel like Shell scripting that allows you to run whatever scripts.](https://youtu.be/6YZvp2GwT0A?t=287)
    
  - **Pipeline**: Code-based job definition using Jenkinsfile
  
    > Use *stages* to break down components of builds

    ```groovy
    pipeline {
        agent any
        stages {
            stage('Checkout') {
                steps {
                    // Pull source code from repository
                    checkout scm
                }
            }
            stage('Build') {
                steps {
                    // Compile and package the application
                    echo 'Building the application...'
                    sh 'mvn clean compile'
                }
            }
            stage('Test') {
                steps {
                    // Run unit tests
                    echo 'Running tests...'
                    sh 'mvn test'
                }
            }
            stage('Package') {
                steps {
                    // Create deployable artifacts
                    echo 'Packaging application...'
                    sh 'mvn package'
                }
            }
            stage('Deploy') {
                steps {
                    // Deploy to target environment
                    echo 'Deploying application...'
                    sh 'deploy-script.sh'
                }
            }
        }
    }
    ```
  
  - **Multi-branch Pipeline**: Automatically creates pipelines for branches
  - **Folder**: Organizes jobs hierarchically


For the difference between Pipeline and Freestyle refer to [What Is The Difference Between Freestyle and Pipeline in Jenkins](https://www.youtube.com/watch?v=IOUm1lw7F58)

> In summary, we can achieve the Pipeline by having a single script, or split several steps into different freestyle projects and chain them, this this is so much pain as it's not durable and not easily maintained.

> while standard Jenkins `freestyle` job support simple continuous integration by allowing you to define sequential tasks in an application lifecycle, they do not create a persistent record of execution, enable one script to address all the steps in a complex workflow.

> The Pipeline plugin was built with requirements for a flexible, extensible, and script based CD workflow capability in mind.


#### 2. **Build**
- An execution of a job
- Each build gets a unique number
- Contains logs, artifacts, and test results
- Can be triggered manually, by schedule, or by events (like code commits)

#### 3. **Workspace**
- A directory where Jenkins executes builds
- Contains source code and build artifacts
- Cleaned up automatically or manually
- Each job typically has its own workspace

#### 4. **Node/Agent**
- **Master Node**: Main Jenkins server that schedules builds and manages configuration
- **Agent/Slave Node**: Remote machines that execute builds
- Allows distributed builds and load balancing
- Can be static (always connected) or dynamic (launched on demand)

In **Jenkins**, **agents** (formerly called "slaves") are worker machines that offload tasks from the **Jenkins controller** (main server). They allow you to distribute builds and workloads across multiple machines, improving scalability and performance.  

1. **Purpose**  
   - Execute **build jobs** (instead of running everything on the controller).  
   - Support different **environments** (OS, tools, dependencies).  
   - Parallelize workloads (e.g., running tests on multiple agents).  

2. **Types of Agents**  
   - **Permanent Agents** (Static)  
     - Manually configured machines that stay connected (e.g., physical servers, VMs).  
   - **Ephemeral Agents** (Dynamic)  
     - Temporary agents spun up on-demand (e.g., Docker, Kubernetes pods, cloud instances).  

3. **Agent Communication**  
   - **SSH** (for Linux/Unix agents).  
   - **JNLP (Java Web Start)** (for agents running Jenkins agent.jar).  
   - **Windows Agent Service** (for Windows machines).  

4. **Agent Modes**  
   - **Master → Agent (Controller → Agent)**  
     - The Jenkins controller schedules jobs on agents.  
   - **Agent → Master (Reverse SSH/JNLP)**  
     - Agents connect to the controller (useful for restricted networks).  


#### 5. **Pipeline**
- A suite of plugins supporting CI/CD pipelines
- Defined using Groovy-based DSL
- Two syntax types:
  - **Declarative Pipeline**: Structured, easier syntax
  - **Scripted Pipeline**: More flexible, procedural approach

```groovy
// Example Declarative Pipeline
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying..'
            }
        }
    }
}
```

#### 6. **Jenkinsfile**
- A text file containing pipeline definition
- Stored in source control alongside code
- Enables "Pipeline as Code" approach
- Version controlled with the application code

[Pipeline syntax can be divided into 2 categories](https://www.jenkins.io/doc/book/pipeline/#pipeline-syntax-overview):

##### **Declarative Pipeline**
- **Newer, recommended syntax** (introduced in Pipeline 2.5)
- More structured and opinionated approach
- Easier to read and write for beginners
- Built-in validation and error handling
- Automatically generates stage view in Jenkins UI

**Basic Structure:**
```groovy
pipeline {
    agent any
    
    stages {
        stage('Build') {
            steps {
                echo 'Building the application'
            }
        }
        stage('Test') {
            steps {
                echo 'Running tests'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying application'
            }
        }
    }
}
```

**Key Components:**
- `pipeline {}` - Root block that contains the entire pipeline
- `agent` - Specifies where the pipeline should run
- `stages {}` - Contains all the pipeline stages
- `stage('name') {}` - Individual pipeline stage
- `steps {}` - Contains the actual commands to execute
- `post {}` - Actions to run after pipeline completion

##### **Scripted Pipeline**
- **Original syntax** based on Groovy DSL
- More flexible and programmatic approach
- Requires more Groovy/programming knowledge
- Better for complex conditional logic and dynamic pipelines
- Uses `node` blocks instead of `pipeline` blocks

**Basic Structure:**
```groovy
node {
    stage('Build') {
        echo 'Building the application'
    }
    
    stage('Test') {
        echo 'Running tests'
    }
    
    stage('Deploy') {
        echo 'Deploying application'
    }
}
```

**Key Differences:**
| Aspect           | Declarative            | Scripted              |
| ---------------- | ---------------------- | --------------------- |
| Learning Curve   | Easier                 | Steeper               |
| Flexibility      | Limited but sufficient | Highly flexible       |
| Error Handling   | Built-in               | Manual implementation |
| Validation       | Automatic              | Manual                |
| Groovy Knowledge | Minimal                | Extensive             |

##### **Common Pipeline Elements**

**Environment Variables:**
```groovy
// Declarative
pipeline {
    environment {
        DEPLOY_ENV = 'staging'
        API_KEY = credentials('api-key-id')
    }
    // stages...
}

// Scripted
node {
    env.DEPLOY_ENV = 'staging'
    withCredentials([string(credentialsId: 'api-key-id', variable: 'API_KEY')]) {
        // stages...
    }
}
```

**Conditional Execution:**
```groovy
// Declarative
stage('Deploy to Production') {
    when {
        branch 'main'
    }
    steps {
        echo 'Deploying to production'
    }
}

// Scripted
stage('Deploy to Production') {
    if (env.BRANCH_NAME == 'main') {
        echo 'Deploying to production'
    }
}
```

**Post Actions:**
```groovy
// Declarative
post {
    always {
        cleanWs()
    }
    success {
        emailext subject: 'Pipeline Success', body: 'Build completed successfully'
    }
    failure {
        emailext subject: 'Pipeline Failed', body: 'Build failed'
    }
}
```

##### **Best Practices**
- **Start with Declarative**: Easier to learn and maintain
- **Use version control**: Always commit Jenkinsfile to your repository
- **Keep it simple**: Break complex logic into separate functions or scripts
- **Use shared libraries**: For reusable pipeline code across projects
- **Implement proper error handling**: Use try-catch blocks and post actions
- **Use meaningful stage names**: Makes it easier to track progress in UI

#### 7. **Plugins**
- Extend Jenkins functionality
- Over 1,800+ plugins available
- Common categories:
  - Source Code Management (Git, SVN)
  - Build Tools (Maven, Gradle, npm)
  - Testing (JUnit, TestNG)
  - Deployment (Docker, Kubernetes)
  - Notifications (Email, Slack)

#### 8. **Triggers**
- Define when builds should start
- Types include:
  - **SCM Polling**: Check for code changes periodically
  - **Webhooks**: Triggered by external events (GitHub push)
  - **Build Periodically**: Cron-like scheduling
  - **Upstream/Downstream**: Triggered by other jobs

#### 9. **Artifacts**
- Files generated by builds that should be preserved
- Examples: JAR files, documentation, test reports
- Can be archived and downloaded
- Used for deployment or further processing

#### 10. **Build Environment**
- Configuration for build execution
- Environment variables
- Build tools and dependencies
- Security credentials

### Core Workflow

1. **Source Code Management**: Jenkins pulls code from repositories
2. **Build Trigger**: Build starts based on configured triggers
3. **Build Execution**: Code is compiled, tested, and packaged
4. **Post-Build Actions**: Artifacts are archived, notifications sent
5. **Deployment**: Application is deployed to target environments

### Jenkins Architecture

```
┌─────────────────┐
│   Jenkins       │
│   Master        │ ← Web UI, Job Management, Build Scheduling
└─────────────────┘
         │
    ┌────┴────┐
    │         │
┌───▼───┐ ┌───▼───┐
│Agent 1│ │Agent 2│ ← Execute builds, run tests
└───────┘ └───────┘
```

### Common Use Cases

- **Continuous Integration**: Automatically build and test code changes
- **Continuous Deployment**: Deploy applications to various environments
- **Automated Testing**: Run unit, integration, and acceptance tests
- **Code Quality**: Integrate with SonarQube, static analysis tools
- **Infrastructure as Code**: Deploy and manage infrastructure
- **Backup and Maintenance**: Automate routine system tasks


## Discovery


#### Exclude branches that are also filed as PRs

**Discovers all branches EXCEPT those that have an associated open pull request.**

**Primary Use Case: Avoiding Duplicate Builds**
The Duplicate Build Problem

```text
Branch: feature/payment-integration
    ↓
PR #123: feature/payment-integration → main
WITHOUT this option:

Build #1: feature/payment-integration (branch push)

Build #2: PR #123 (pull request)
```

Two nearly identical builds running simultaneously


A branch without a PR will build in these common scenarios: **basic push**

1. Initial Branch Creation/Push
2. Subsequent Commits to the Branch

```bash
git checkout feature/login
# Fix a bug, add more code
git add .
git commit -m "Fix login validation"
git push origin feature/login
```

Real-World Development Scenarios

```text
Day 1: Create feature/login → Build #1
Day 2: Add validation → Build #2  
Day 3: Fix bug → Build #3
Day 4: Ready for review → Create PR
```


### Kubenetes install


1. use `Helm` to get config values

```bash
helm repo add jenkins https://charts.jenkins.io
helm repo update

curl -o jenkins-values.yaml https://raw.githubusercontent.com/jenkinsci/helm-charts/main/charts/jenkins/values.yaml

# create namespace
kubectl create namespace jenkins
```

2. config necessary configs

```yaml
  # If you are using the ingress definitions provided by this chart via the `controller.ingress` block,
  # the configured hostname will be the ingress hostname starting with `https://`
  # or `http://` depending on the `tls` configuration.
  # The Protocol can be overwritten by specifying `controller.jenkinsUrlProtocol`.
  # -- Set protocol for Jenkins URL; `https` if `controller.ingress.tls`, `http` otherwise
  jenkinsUrlProtocol: http

  # -- Set Jenkins URL if you are not using the ingress definitions provided by the chart
  jenkinsUrl: http://jenkins.cares-copilot.com

  ingress:
    # -- Enables ingress
    enabled: true
    ingressClassName: nginx

persistence:
  # -- Enable the use of a Jenkins PVC
  enabled: true

  # A manually managed Persistent Volume and Claim
  # Requires persistence.enabled: true
  # If defined, PVC must be created manually before volume will be bound
  # -- Provide the name of a PVC
  existingClaim:

  # jenkins data Persistent Volume Storage Class
  # If defined, storageClassName: <storageClass>
  # If set to "-", storageClassName: "", which disables dynamic provisioning
  # If undefined (the default) or set to null, no storageClassName spec is
  #   set, choosing the default provisioner (gp2 on AWS, standard on GKE, AWS & OpenStack)
  # -- Storage class for the PVC
  storageClass: longhorn
  # -- Annotations for the PVC
  annotations: {}
  # -- Labels for the PVC
  labels: {}
  # -- The PVC access mode
  accessMode: "ReadWriteOnce"
```

3. install

```bash
helm install jenkins jenkins/jenkins -n jenkins -f jenkins-values.yaml
```

For the ingress configuration and refer to [k8sNotes Ingress Controller]()

