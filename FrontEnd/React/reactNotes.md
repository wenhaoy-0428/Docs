# React

React is a **library** for building user interfaces. React is not a framework – it's not even exclusive to the web. It's used with other libraries to render to certain environments. For instance, `React Native` can be used to build mobile applications. To build for the web, developers use `React` in tandem with `ReactDOM`. Together, they solve the same problem other web frameworks do. 

React use its own `Domain Specific Language` [JSX](#jsx) which is an extension of JS which mixtures HTML syntax and JS, like the following,

```js
const header = (
  <header>
    <h1>Mozilla Developer Network</h1>
  </header>
);
```

> This snippet of code can't be recognized by HTML without a compiler. 

React also provides native approach to create elements without using a compiler that achieves the same result as above:
```js
const header = React.createElement("header", null,
  React.createElement("h1", null, "Mozilla Developer Network")
);
```

> Note: the native React approach still abstracts away the major headaches of pure JS. 

## StartUp

#### Auto Setup
We can use the following script to set up a React app with predefined rules and dependencies. React helps us to set up everything including compiler, bundler, linter, etc. 
```bash
npx create-react-app your-app-name-as-the-folder
```

> They above script suits for small-medium projects without too many headaches to setup the env. However, it loses the ability to customization.

To regain the ability of customization, we use `npm run eject` command defined in `package.json` to add back all the configs to the project we can tweak around. 

#### [Add React to a website without create a react app](https://reactjs.org/docs/add-react-to-a-website.html)


## Basic

When using HTML syntax in JSX, we use `className` which serves the same purpose as `class=""` in HTML. we can't use the word `class` — it's reserved, meaning JavaScript already uses it for a specific purpose and it would cause problems here in our code. 

[TODO-when-role-is-necessary](https://www.scottohara.me/blog/2019/01/12/lists-and-safari.html)

Sometimes, we may encounter situations where we have to use boolean with a curly braces:
```js
<input id="todo-0" type="checkbox" defaultChecked={true} />
```
and sometimes with a quote:
```js
<button type="button" className="btn toggle-btn" aria-pressed="true">
```
The reason behind is that `"true"` is parsed as a string literal not a boolean. `aria-pressed` is not a true boolean attribute in the way checked is. 

> Note `defaultChecked` is a JSX exclusive attribute in substitution of `checked` attribute in HTML, while `aria-pressed` is a standard attribute in Accessibility.


## Variables

JSX see variables in curly braces. In the following example, `logo` is identified as a variable.
```js
<img src={logo} className="App-logo" alt="logo" />
```

## Component

Define a component as you like:

* If it represents an obvious "chunk" of your app, it's probably a component
* If it gets reused often, it's probably a component.

**Components must always return something**. If at any point in the future you try to render a component that does not return anything, React will display an error in your browser.

Js codes defined outside of a component (in the same file) will not be consider part of the component(view) as they will not be returned, thus will not be re-rendered. They can be used in component in the same file. 

## prop

A `prop` is any data passed into a React component. React `props` are comparable to HTML attributes. Props are read only, but [States](#state) of a component can be updated.

In the calling side, it's the same as HTML syntax: `prop="value`
```js
root.render(<App subject="Clarice" />);
```

In the called side, it's a parameter passed into the component.
```js
function App(props) {
  console.log(props);
  return (
    // return statement
  );
}
```

> In React, dataflow is **unidirectional**: props can **only** be passed from Parent components down to Child components; and props are **read-only**.


#### attribute key in prop
`key` is a special prop, and can't be used for user defined purpose. It's used to in List to help React identify each item. Check [keys](https://reactjs.org/docs/lists-and-keys.html#keys) for the official documentations. 

> You should always pass a unique key to anything you render with iteration


#### [Callback Prop](https://developer.mozilla.org/en-US/docs/Learn/Tools_and_testing/Client-side_JavaScript_frameworks/React_interactivity_events_state#callback_props)

The interactivity of one component, in reality, will affect other parts of the App. However, dataflow is **unidirectional** as mentioned [above](#prop). Thus, We can pass a callback function as prop from the top layer to the bottom components. Thus, when an event happens to a component, we can use the callback function to pass the changes to the top layer.

> Passing data in the bottom up direction using `prop` is an appropriate way. However, this method will quickly run out of control when the nested level is huge. Another way of achieving this is to use [Context API](#context-api)


## State

Data such as this, which a component itself owns, is called `state`. State is another powerful tool for React because components not only **own** state, but can **update** it later. *It's not possible to update the [props](#prop) a component receives; only to read them.*

> The wondering here could be : what's the difference between state and a class variable? They sound extremely similar. The answer is, they serve the same purpose. The difference is that, **React will keep track of states, and once a state changes, it will automatically call `render()` to update the UI with the latest update**. However, using class variable won't don't let React know, hence you may have to re-render yourself. 

!> To make the re-render the state, you have to use the provided updateMethod when creating the state.


#### [how to store previous state](https://www.developerway.com/posts/implementing-advanced-use-previous-hook)

In [general hooks](#general-hooks), we introduced the `useRef` which attaches a reference to an element, and `useEffect` which is automatically when page rerenders. 

```jsx
const usePrevious = (value) => {
  const ref = useRef();
  useEffect(() => {
    ref.current = value;
  });
  return ref.current;
};

const targetPrevious = usePrevious(targetNow);
```

1. In the code above, we define a [custom hook](#custom-hooks), and pass the `state` we're interested in, in this case `targetNow`. The effect we want to achieve is that when `targetNow` changes, we can access its previous state value by using the variable `targetPrevious`.

2. Inside the `usePrevious` hook, we use `useRef` to store the previous value. The reason we don't use another `state` is that `state` changes will cause re-rending while `refs` don't.

> The reason, we don't use a variable is that it's not general. The following code will perform exactly the same as `usePrevious`. However, we need to create a single variable to store the previous one for every state we're interested in.

```js
let myTempPrev = undefined;

const [tempState, setTemp] = useState(1);
const tempPrev = usePrevious(tempState);

<div>
  <button onClick={() => {
    myTempPrev = tempState;
    setTemp(tempState + 1);
  }}>
      CLICK ME
  </button>
  <p>
    Now: {tempState}; Before: {tempPrev}; myBefore: {myTempPrev}
  </p>
  
</div>
```


3. `useEffect` will register the callback function, and calls it when rendering. 

> Note, due to the fact that [closure](/FrontEnd/Js/jsNotes.md#closure) exists for function, `value` and `ref` will remembered by the callback even after `usePrevious` finishes. a reference to `ref` will be stored by `targetPrevious`. 

4. Ultimately, when `targetNow` (a state) changes, it cause the component to be rerendered, and thus callbacks in `useEffect` will be called. In this case, `ref.current` will be assigned to the `value` of the previous value of `targetNow`, thanks to closure. 




## Hooks


React provides a variety of special functions that allow us to provide new capabilities to components, like [state](#state). These functions are called `hooks`

To use a hook function, import it first.
```jsx
import React, { useState } from "react";
```

#### General Hooks

- `useState`is useful to create and store variables.
- [useRef](https://reactjs.org/docs/hooks-reference.html#useref) is particularly useful for referring to DOM elements.
- [useEffect](https://reactjs.org/docs/hooks-reference.html#useeffect) is so named because it runs after React renders a given component, and will run any side-effects that we'd like to add to the render process, which we can't run inside the main function body. It also accepts a list that tells add the additional rendering only when states in the list change.

```jsx
useEffect(() => {
  if (isEditing) {
    editFieldRef.current.focus();
  } else {
    editButtonRef.current.focus();
  }
}, [isEditing]);
```

#### Custom Hooks
//TODO

#### [Get the value of an Input field using hooks](https://bobbyhadz.com/blog/react-get-input-value)

1. `useState` hook in tandem with `onChange` event to store the value into a `state`.
```jsx
import {useState} from 'react';

const App = () => {
  const [message, setMessage] = useState('');

  const handleChange = event => {
    setMessage(event.target.value);

    console.log('value is:', event.target.value);
  };

  return (
    <div>
      <input
        type="text"
        id="message"
        name="message"
        onChange={handleChange}
        value={message}
      />

      <h2>Message: {message}</h2>
    </div>
  );
};

export default App;
```

> This is method we cause the view to be re-rendered every time we change the input value. React is smart enough to re-render changes only.

2. `useRef` hooks

```jsx
import {useRef} from 'react';

const App = () => {
  const inputRef = useRef(null);

  function handleClick() {
    console.log(inputRef.current.value);
  }

  return (
    <div>
      <input
        ref={inputRef}
        type="text"
        id="message"
        name="message"
      />

      <button onClick={handleClick}>Log message</button>
    </div>
  );
};

export default App;
```

> It should be noted that when you change the value of the current property of the ref, no re-renders are caused.



## Events

In React, we write event handlers directly on the elements in our JSX, like this:

```jsx
<button
  type="button"
  onClick={() => alert("hi!")}
>
  Say hi!
</button>
```

> Note `onClick` is a JSX defined attribute, not the standard `onclick`. All browser events follow this format in JSX – `on`, followed by the `name of the event`.



## [Context API](https://reactjs.org/docs/context.html)

Context API is a good way to pass around data, a more simpler way is to pass data through [props](#prop), especially when passing [callback props](#callback-prop) when nested level is low.

//TODO:


## [Virtual DOM](https://reactjs.org/docs/faq-internals.html#what-is-the-virtual-dom)
//TODO

## [JSX](https://reactjs.org/docs/jsx-in-depth.html)
//TODO


## Routing

In original scenarios, when user click on a button to jump into a new page, the request is send to the *Server side*, and request a new page to the client to render. Clients are allowed to jump from pages to pages, and all pages have different paths. This is called `Server-Side-Routing`.

Now, with React, we have a single webPage, with many different views(components). Each time we click on a button, we have the views to be swapped, instead of having a totally different page. Hence, we need to handle views routing. This is called `Client-Side-Routing`.

#### Reach Routing
// TODO


#### React Routing

// TODO