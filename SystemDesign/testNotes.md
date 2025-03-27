1. [Software Testing Methodologies](https://smartbear.com/learn/automated-testing/software-testing-methodologies/)
2. [How To Write Better Tests In 6 Easy Steps](https://www.youtube.com/watch?v=FcHUPqKRvxQ)
3. [The Golden Rule of Assertions](https://www.epicweb.dev/the-golden-rule-of-assertions)

[What is Agile Testing? | Agile Scrum Testing Methodologies | Software Testing Tutorial | Edureka](https://www.youtube.com/watch?v=UQWyG3xSr5k)


https://www.browserstack.com/guide/software-testing-methodologies


[What Is Agile Methodology? | Introduction to Agile Methodology in Six Minutes | Simplilearn](https://www.youtube.com/watch?v=8eVXTyIZ1Hs)





## Practices

1. Writing test targeting 100% coverage is **wrong**!

> 100% coverage doesn't mean the tests are great

2. Write code for behavior (input -> output), not implementation details

3. isolate test cases as much as possible, so the change of 1 test doesn't influence the others. This certainly violates the don't repeat yourself principle, but it's totally fine.

## Unite Test


## Integration Test

A dedicated enviornment has to be created that runs both runtimes to make this possible.

A docker-compose is a great tool for this case.

## End-to-End test

[5 Types of Testing Software Every Developer Needs to Know!](https://www.youtube.com/watch?v=YaXJeUkBe4Y&t=9s)


## White / Black box 


### Black Box Testing

**Definition:** Evaluates functionality without knowledge of internal code. Tests are based on requirements and user perspectives.

**Focus:**

* Input-output validation, usability, and compliance with specifications.

* Identifying gaps in functionality or user experience.

**Performed by:** QA teams or end-users.

## Smoke 

So in software, a smoke test might be a quick check to see if the basic functionality works. Like a sanity check after a new build to ensure that major features are working and there are no show-stopping bugs. 


After a new deployment, check if users can launch the app, log in, and access primary menus.

Basic stability of the build