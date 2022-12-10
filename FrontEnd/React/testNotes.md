# [Test](https://create-react-app.dev/docs/running-tests)

Testing typically involves with a **runner** and **libraries** to support more specific needs.

A test runner is the same as `gTest` which has its own skeleton that allows you do implement your test suites and test cases. It includes assertions, mock for your written tests. This natively works for pure JS code. A runner normally we also call it a framework includes a simulated browser implementation.

A test library can be a solution for testing web pages by querying and interacting with DOM nodes, it provides methods to quickly get elements. There are also other libraries for handling different tasks.

# Jest

Jest is a test runner/framework.

> jest-dom is a library from the DOM Testing Library that provides **extra Jest assertions** to use in tests.

# [React Testing Library](https://www.youtube.com/watch?v=7dTTFW7yACQ&list=PL4cUxeGkcC9gm4_-5UsNmLqMosM-dzuvQ)

RTL is a library specific designed for React project. It's a sub-Library of [Testing Library](https://testing-library.com) which provides a variety of libraries for different projects.

## [render](https://testing-library.com/docs/react-testing-library/api#render)

Render the component into a container which is appended to `document.body`.

## [screen](https://testing-library.com/docs/queries/about#screen)

All of the queries exported by DOM Testing Library accept a **container** as the first argument. **Because querying the entire document.body is very common**, DOM Testing Library also exports a `screen` object which has every query that is **pre-bound to document.body**

## [Not wrapped in act Errors](https://davidwcai.medium.com/react-testing-library-and-the-not-wrapped-in-act-errors-491a5629193b)

In test, the code to render and update React components need to be included in React’s call stack. Thus, all actions have to be wrapped by [act()](https://reactjs.org/docs/test-utils.html#act). To reduce boilerplate, `RTL` has wrapped everything by `act` for us. However, under certain situations, `RTL` may still throw this error. check the title link for details.
