# [Devops](https://www.youtube.com/watch?v=scEDHsr3APg)

Devops is a set of practices or a **pipeline** of building/improving the application. It's the **lifecycle** of application development nowadays. Similar to [Agile](https://www.youtube.com/watch?v=5RocT_OdQcA), Devops also emphasizes continuous improvements, but Agile is a project management concept, while Devops is pipeline of building the application.

The most important key of DevOps pipeline is to accelerate the process of development. Therefore, for each step of the devops pipeline, there're tools we can use, especially to **automate**.

**The most important and time consuming steps, apart from the development, are testing and deployment. Therefore, Continuous Integration and Continuous Deployment/Delivery (CI/CD) are the most important phases in Devops**

## [Continuous Integration](https://www.youtube.com/watch?v=G1u4WBdlWgU)

For each code merge, in order to make sure the new code doesn't break the other logics, a set of tests have to be conducted. Therefore, CI is an action defined by scripts to automatically run tests before merging. 

Continuous Integration is hard to separate from CD, as they're basically done at the same time. Sometimes, after passing the CI (it can also be done before CI), some images (like system images / docker images) are also compiled with the merging code. This action is CD.

For CI/CD pipeline, there're several popular tools, and [GitHub Action](#github-actions) is one of them (may not be the most popular one, but fairly easy to use). A good explanation can be fount in this video [CICD process explained with Hands On Project](https://youtu.be/G1u4WBdlWgU?t=460)

### GitHub Actions

1. [Concept Intro](https://www.youtube.com/watch?v=R8_veQiYBjI&t=1478s)
2. [CI for React](https://www.youtube.com/watch?v=eB0nUzAI7M8)




## Automating Docker Image Deployment

After building and publishing Docker images through CI/CD, automating their deployment ensures seamless updates without manual intervention. Here are the most effective approaches:

### 1. Watchtower
**Best for**: Simple automatic updates on single servers
- Monitors Docker registries for new image versions
- Automatically pulls updates and restarts containers with zero downtime
- Lightweight daemon with minimal resource overhead

```bash
# Basic setup - checks every 30 seconds
docker run -d \
    --name watchtower \
    -v /var/run/docker.sock:/var/run/docker.sock \
    containrrr/watchtower --interval 30

# Production setup with notifications
docker run -d \
    --name watchtower \
    -v /var/run/docker.sock:/var/run/docker.sock \
    -e WATCHTOWER_NOTIFICATIONS=slack \
    -e WATCHTOWER_NOTIFICATION_SLACK_HOOK_URL=your-webhook \
    containrrr/watchtower --cleanup
```

### 2. Extended CI/CD Pipeline
**Best for**: Full control over deployment process
- Extends GitHub Actions to handle deployment automatically
- Supports multiple environments (staging, production)
- Enables rollback strategies and health checks

```yaml
# Example GitHub Actions deployment step
- name: Deploy to Production
    uses: appleboy/ssh-action@v0.1.5
    with:
        host: ${{ secrets.HOST }}
        username: ${{ secrets.USERNAME }}
        key: ${{ secrets.KEY }}
        script: |
            docker pull ${{ env.IMAGE_NAME }}:latest
            docker stop app-container || true
            docker rm app-container || true
            docker run -d --name app-container -p 80:3000 ${{ env.IMAGE_NAME }}:latest
```

### 3. Jenkins with Docker Plugin
**Best for**: Enterprise environments with complex workflows
- Robust pipeline management with visual interface
- Extensive plugin ecosystem for Docker operations
- Built-in support for multi-stage deployments and approvals

### 4. Webhook-Triggered Deployment
**Best for**: Custom deployment logic and lightweight solutions
- GitHub Actions triggers webhook after successful image build
- Server runs minimal service to handle deployment requests
- Provides audit trail and custom notification systems

```javascript
// Simple Node.js webhook handler
app.post('/deploy', (req, res) => {
    if (validateWebhook(req)) {
        exec('docker-compose pull && docker-compose up -d', (error, stdout) => {
            if (error) {
                console.error('Deployment failed:', error);
                return res.status(500).send('Deployment failed');
            }
            console.log('Deployment successful:', stdout);
            res.send('Deployment triggered');
        });
    }
});
```

**Recommendation**: Start with Watchtower for simple applications, then migrate to extended CI/CD pipelines as your deployment requirements grow more complex.
