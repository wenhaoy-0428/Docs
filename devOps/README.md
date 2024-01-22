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
