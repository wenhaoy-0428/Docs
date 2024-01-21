# [Test](https://create-react-app.dev/docs/running-tests)

Testing typically involves with a **runner** and **libraries** to support more specific needs.

A test runner is the same as `gTest` which has its own skeleton that allows you do implement your test suites and test cases. It includes assertions, mock for your written tests. This natively works for pure JS code. A runner normally we also call it a framework includes a simulated browser implementation.

A test library can be a solution for testing web pages by querying and interacting with DOM nodes, it provides methods to quickly get elements. There are also other libraries for handling different tasks.

# Jest

Jest is a test runner/framework.

> jest-dom is a library from the DOM Testing Library that provides **extra Jest assertions** to use in tests.

## ["Cannot use import statement outside a module" with Axios](https://stackoverflow.com/questions/73958968/cannot-use-import-statement-outside-a-module-with-axios)

When mocking `axios`, Jest throws error `Cannot use import statement outside a module`. The above link solves the problem.

# [React Testing Library](https://www.youtube.com/watch?v=7dTTFW7yACQ&list=PL4cUxeGkcC9gm4_-5UsNmLqMosM-dzuvQ)

RTL is a library specific designed for React project. It's a sub-Library of [Testing Library](https://testing-library.com) which provides a variety of libraries for different projects.

## [render](https://testing-library.com/docs/react-testing-library/api#render)

Render the component into a container which is appended to `document.body`.

## [screen](https://testing-library.com/docs/queries/about#screen)

All of the queries exported by DOM Testing Library accept a **container** as the first argument. **Because querying the entire document.body is very common**, DOM Testing Library also exports a `screen` object which has every query that is **pre-bound to document.body**

## [Not wrapped in act Errors](https://davidwcai.medium.com/react-testing-library-and-the-not-wrapped-in-act-errors-491a5629193b)

In test, the code to render and update React components need to be included in React’s call stack. Thus, all actions have to be wrapped by [act()](https://reactjs.org/docs/test-utils.html#act). To reduce boilerplate, `RTL` has wrapped everything by `act` for us. However, under certain situations, `RTL` may still throw this error.

> React includes this error as an indicator that there is an unhandled state changes. This sort of warnings normally happen when there is a state change after test case finishes, which normally happens when there is a async function that changes the state after `act` is done. To address it, the simplest way is to tell react you notice the change by adding an expectation on an element that uses that state. And because, it's always an async function that changes the state, we'll wrap the `expect` in a `await waitFor`

!> Sometimes, `await waitFor` can be helpful. However, because `waitFor` is promise based and promise runs in [microTask](/FrontEnd/Js/jsNotes.md#task-queue-vs-microtask), thus it may block certain actions.

For example:

```js
// #.js
const submitForm = (values) => {
  console.log(JSON.stringify(values, null, 2));

  setFormStatus(status.loading);

  // handle request.
  axios
    .put("#", values)
    .then(() => {
      console.log("Submission Success");
      setFormStatus(status.success);
      // TODO: reset the form.
    })
    .catch((e) => {
      console.log(`Submission Failure: ${e}`);
      setFormStatus(status.failure);
    })
    .then(() => {
      console.log("Submission CleanUp");
      setTimeout(() => {
        console.log("Neutralizing Form");
        setFormStatus(status.neutral);
        // tell to animate.
        setSwitchSubmitBtn(!switchSubmitBtn);
      }, 1);
    });
};

// #test.js

const submitBtn = screen.getByTestId("submitBtn");
// click submit Button
user.click(submitBtn);
waitFor(() => {
  expect(screen.queryByTestId("checkIcon")).not.toBeNull();
});
// ! adding await will cause the event hoop to be stuck for settimeout in the submitForm promise.
waitFor(() => {
  expect(screen.queryByTestId("checkIcon")).toBeNull();
});
```

In the above example, if we add `await`, `Neutralizing Form` will be called, but setTimeOut is blocked by microTask await.

## Test with Tailwind

Jest uses jsDom as its inner browser implementation, which isn't compatible with Tailwind.
Thus, we need to:

1. manually compile a traditional CSS file.
2. [render](https://testing-library.com/docs/react-testing-library/api#container) in React Test Library wraps the rendered component into a `div` which attaches to `document.body`. And it supports custom `render`. Thus, we can use custom render to **inject** the compiled CSS file into the `document.head`.

Refer to [React testing library can't read styles using Tailwind CSS classes](https://stackoverflow.com/questions/71010317/react-testing-library-cant-read-styles-using-tailwind-css-classes)

## jsDom doesn't support Responsive Design Test

Don't waste your time using jsDom to test responsive design using CSS media query. [It simply doesn't support](https://stackoverflow.com/questions/64281467/react-testing-library-rtl-test-a-responsive-design). Use `Cypress` instead.

If you use `matchMediaQuery` to implement your responsive web design, [How to set media queries with jest?](https://stackoverflow.com/questions/57167525/how-to-set-media-queries-with-jest) may help.
