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


#### Quotes and Curly Braces

You should either use `quotes` (for string values) or `curly braces` (for expressions), but not both in the same attribute.

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

##### Variables

JSX see variables in curly braces. In the following example, `logo` is identified as a variable.
```js
<img src={logo} className="App-logo" alt="logo" />
```


## JSX

JSX mixes HTML and JS syntax, but internally, it creates a React object to which the rendering will refer.

```jsx
const element = (
  <h1 className="greeting">
    Hello, world!
  </h1>
);
```
```js
const element = React.createElement(
  'h1',
  {className: 'greeting'},
  'Hello, world!'
);
```

> You can always use Js with provided API to replace JSX syntax. 

```js
// Note: this structure is simplified
const element = {
  type: 'h1',
  props: {
    className: 'greeting',
    children: 'Hello, world!'
  }
};
``` 

## [Reconciliation](https://reactjs.org/docs/reconciliation.html)

React has its own tree in tandem with the DOM tree.

React compares elements/components in the React tree and updates when necessary, the algorithm is described in the above link.

When `unmounting` a element/component, all its state are destroyed and any components below that element will also get unmounted and have their state destroyed. 

## Component

Define a component as you like:

* If it represents an obvious "chunk" of your app, it's probably a component
* If it gets reused often, it's probably a component.

**Components must always return something**. If at any point in the future you try to render a component that does not return anything, React will display an error in your browser.

Js codes defined outside of a component (in the same file) will not be consider part of the component(view) as they will not be returned, thus will not be re-rendered. They can be used in component in the same file. 

#### Class Component

This form of component is declared in JS class format. However, this form of component is old and outdated after the appearance of [Hooks](#hooks). Use [Function Component](#function-component) for better syntax.


In class component, [state](#state) is a member object, the only way to change it is through the constructor of `state`.
```jsx
// Wrong
this.state.comment = 'Hello';
// Correct
this.setState({comment: 'Hello'});
```

In the above example, `setState` accepts an object. This object is **merged** into the `state`. Meaning, when a component has multiple states, `setState` will only replace the one you specified. 
```jsx
  constructor(props) {
    super(props);
    this.state = {
      posts: [],
      comments: []
    };
  }
```

> Since it's merged, in a class setting, you can use `setState` to add new state that's not declared earlier.
```jsx
this.setState({
  [name]: value
});
```


[Life cycle](https://projects.wojtekmaj.pl/react-lifecycle-methods-diagram/)

`componentDidMount()` function will be called after the component is rendered.

`componentWillUnmount()` function will be called when the component is destroyed.



#### When Class Component is over Functional Component

However, class component is still the only way to work around in some situations.

1. [Error Boundaries](https://reactjs.org/docs/error-boundaries.html) can only be class components.

2. You may not use the [ref](https://reactjs.org/docs/refs-and-the-dom.html#accessing-refs) attribute on `function components` because they don’t have instances.

3. Class components have life cycle methods, while functional components don't.

4. State in class components are **merged** while `useState` in function components replace the states.

#### Function Component



#### Conditional Rendering

We can use `if` to control if a component is rendered. 

From top level:

```jsx
render() {
    if (isLoggedIn) {
      button = <LogoutButton onClick={this.handleLogoutClick} />;
    } else {
      button = <LoginButton onClick={this.handleLoginClick} />;
    }
}
```


From child component level:
We can also use `&&` and `?` for inline syntax
```jsx

  return (
    <div>
      <h1>Hello!</h1>
      {unreadMessages.length > 0 &&
        <h2>
          You have {unreadMessages.length} unread messages.
        </h2>
      }
    </div>
    )
```

> When we want to prevent a component from rendering, even when Top component tries to render it. We can return `null` in the child component.

#### [Composition vs Inheritance](https://reactjs.org/docs/composition-vs-inheritance.html#specialization)

Inheritance in Component is not recommended. When having common reusable code, it's always a better idea to create common modules and import them. To mimic the inheritance style in components, use `composition` instead. 

`Inheritance` and `Composition` are both used to define **new** components based on **old** components.

`Inheritance` is like a hierarchy tree where the higher the attribute is in the tree, the more common it is for all classes in the tree.

`Composition` on the other hands is more like a summary. It concentrates on the actions a class can **do**. So we define actions instead of classes, and compose those actions into a class to demonstrate its capabilities.

> Watch [Composition over Inheritance](https://www.youtube.com/watch?v=wfMtDGfHWpA) for why you should **never** use Inheritance.

In React, `Composition` typically is `Containment`. We define a base component and its necessary layout, then it accepts new features using `children` prop. The new component defines itself by composing new features to the old component. Watch [Composition in React](https://www.youtube.com/watch?v=of7isf3YBZ4) for better demonstration.


> The idea of [containment]((https://csharp.2000things.com/2012/10/09/688-aggregation-composition-and-containment/)) in object-oriented programming is the idea that an outer class contains an instance of another class and allows access to the contained object through its own methods. As such, `Composition` is more preferable to [Context](#context-api) for `Props drilling`, because we can now pass props from outer layer directly to nested layers, thanks to `containment`.


```jsx
function FancyBorder(props) {
  return (
    <div className={'FancyBorder FancyBorder-' + props.color}>
      {props.children}
    </div>
  );
}


function WelcomeDialog() {
  return (
    <FancyBorder color="blue">
      <h1 className="Dialog-title">
        Welcome
      </h1>
      <p className="Dialog-message">
        Thank you for visiting our spacecraft!
      </p>
    </FancyBorder>
  );
}
```

> In the above example, `WelcomeDialog`, the outer layer, composes the tree by defining the content of its children. Unlike normal abstractions where we only use `<FancyBorder>` without the closing tag and have its content defined in its own module, we use `<FancyBorder>` and `</FancyBorder>` closing tag, where in between is the content.



## prop

A `prop` is any data passed into a React component. React `props` are comparable to HTML attributes. Props are **read only**, but [States](#state) of a component can be updated. 


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
`key` is a special prop, and can't be used for user defined purpose. It's used to in List to help React identify each item. 

When inserting elements to the back of a list, React will compare each list element (which can be a component and needs updating) from the head to tail. Because we're only inserting to the back, all elements stay intact (no changes in content, type, attributes ...), a simple check and insert gives us the new React tree.


However, when inserting elements to the front, all elements will be changed, because their indexes change (attribute change). Thus, the whole React tree (list as the root) will be re-rendered. This is a huge performance issue.

To solve the problem, we use `key` in replace of `index`. Check [keys](https://reactjs.org/docs/reconciliation.html#keys) for the official documentations. 

> You should always pass a unique key to anything you render with iteration


#### [Callback Prop](https://developer.mozilla.org/en-US/docs/Learn/Tools_and_testing/Client-side_JavaScript_frameworks/React_interactivity_events_state#callback_props)

The interactivity of one component, in reality, will affect other parts of the App. However, dataflow is **unidirectional** as mentioned [above](#prop). Thus, We can pass a callback function as prop from the top layer to the bottom components. Thus, when an event happens to a component, we can use the callback function to pass the changes to the top layer.

> Passing data in the bottom up direction using `prop` is an appropriate way. However, this method will quickly run out of control when the nested level is huge. Another way of achieving this is to use [Context API](#context-api)


## State

Data such as this, which a component itself owns, is called `state`. State is another powerful tool for React because components not only **own** state, but can **update** it later. *It's not possible to update the [props](#prop) a component receives; only to read them.*

> The wondering here could be : what's the difference between state and a class variable? They sound extremely similar. The answer is, they serve the same purpose. The difference is that, **React will keep track of states, and once a state changes, it will automatically call `render()` to update the UI with the latest update**. However, using class variable won't don't let React know, hence you may have to re-render yourself. 

!> To make the re-render the state, you have to use the provided updateMethod when creating the state.

!> React may batch multiple setState() calls into a single update for performance. [So setState may be asynchronous](https://reactjs.org/docs/state-and-lifecycle.html#state-updates-may-be-asynchronous) and you should not rely on current value to calculate next state. The fix is lying in the above link.

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

It's tricky when using [this](/FrontEnd/Js/jsNotes.md#this) in callbacks, not only in Event Handlers, but this a more common scenario. In the following code, `this` in `handleClick` will be `undefined` when called. Because `this` in regular function is not bound. 

```jsx
class LoggingButton extends React.Component {
  handleClick() {
    console.log('this is:', this);
  };
  render() {
    return (
      <button onClick={this.handleClick}>
        Click me
      </button>
    );
  }
}
```

The fix is using
1. `bind()`.
```jsx
<button onClick={this.handleClick.bind(this, extraData)}>
```

2. use arrow function in declaration. (formally called `public class fields syntax`)
```jsx
handleClick = () => {
    console.log('this is:', this);
  };
```

3. use arrow function in event handler.
```jsx
<button onClick={() => this.handleClick()}>
```


## [Refs](https://reactjs.org/docs/refs-and-the-dom.html)

`Refs` are useful when we want the traditional way to select an element.

ref updates happen before `componentDidMount` or `componentDidUpdate` lifecycle methods.

**You may not use the ref attribute on function components because they don’t have instances.** 

> But you can use ref in a functional component referring to a DOM element or class component. It's just the functional component itself can be referred by others.

The workaround is to use [useImperativeHandle](https://reactjs.org/docs/hooks-reference.html#useimperativehandle) and [forwardRef](https://reactjs.org/docs/react-api.html#reactforwardref)


#### Usage

- In class components, we use the `React.createRef()` to create an empty reference and attach it to a component or DOM node.

> An alternative way to this is using [Callback Refs](https://reactjs.org/docs/refs-and-the-dom.html#callback-refs), where we attach a function to a component or DOM node, which will be called when **mounted** and **unmounted** with the React component instance or DOM node as argument, and `null` respectively. So we can store it later on.

!> Note, because both when the component is `mounted` and `unmounted`, will the callback be called, using inline callback functions will cause the function to be called twice, once with `null` when unmounting previous one, and one with a component instance when `mounting`. [WHY INLINE calls twice?](#TODO)

- In function components, we use the `useRef` hook. 


#### Exposing DOM Refs to Parent Components

This allows parent to have control over the nodes in a child component. Not recommended, but useful sometimes.

Several ways to do this:

1. [forwardRef](https://reactjs.org/docs/forwarding-refs.html)
2. Create a ref in parent, and pass it to child component through props and attach it to the DOM. 
3. Use Callback refs the same way as `#2`







## [Code Splitting](https://reactjs.org/docs/code-splitting.html)

Currently, We use JS to render HTML, and all the modules and dependencies are bundled together into a single file by bundlers like `Webpack`, and `Parcel`. The content will be displayed once the User finishes loading the file and rendering. Thus, when the bundled file becomes large enough, to load and render the whole file requires noticeable longer time. 

The idea of `code splitting` is to split the integrated single bundle into multiple bundles, where bundles will be loaded only when necessary. Check out [How to Improve Performance in React with Code Splitting on YouTube](https://www.youtube.com/watch?v=-4fyyyQjsz8) for demonstration. 

`React.lazy` provides code splitting by dynamic loading.
```jsx
const OtherComponent = React.lazy(() => import('./OtherComponent'));
```

The lazy component should then be rendered inside a `Suspense` component. And `fallback` attribute provides loading screen when rendering the component that is in a different bundle. `fallback` typically blast in and out very quickly.

```jsx
import React, { Suspense } from 'react';

const OtherComponent = React.lazy(() => import('./OtherComponent'));

function MyComponent() {
  return (
    <div>
      <Suspense fallback={<div>Loading...</div>}>
        <OtherComponent />
      </Suspense>
    </div>
  );
}
```

> Only modules dynamically imported are classified into different bundles.

!> `React.lazy` only supports default exports. To use import by name, add an intermediate module layer that default [exports the importing elements](/FrontEnd/Js/jsNotes.md#export-importing-modules) by name.

## [Context API](https://reactjs.org/docs/context.html)

Context API is a good way to pass around data, a more simpler way is to pass data through [props](#prop) which is more commonly used when nested level is low. However, the problem of `prop` gets more obvious as nested level increases. To pass an attribute that all children should have, like `theme`, we have to include `theme` in `props` for every children component, which is extremely cumbersome.

!> Context is designed to share data that can be considered `“global”` for a tree of React components. Unless to define something in global, like `theme`, `language`, it's extremely rare to use it. Because, defines components based on context, will make it less reusable. In the following example, `ThemedButton` will throw error when `context` is not defined in a different environment where we want to reuse it.

```jsx
const ThemeContext = React.createContext('light');

class App extends React.Component {
  render() {
    // Use a Provider to pass the current theme to the tree below.
    // Any component can read it, no matter how deep it is.
    // In this example, we're passing "dark" as the current value.
    return (
      <ThemeContext.Provider value="dark">
        <Toolbar />
      </ThemeContext.Provider>
    );
  }
}

// A component in the middle doesn't have to
// pass the theme down explicitly anymore.
function Toolbar() {
  return (
    <div>
      <ThemedButton />
    </div>
  );
}

class ThemedButton extends React.Component {
  // Assign a contextType to read the current theme context.
  // React will find the closest theme Provider above and use its value.
  // In this example, the current theme is "dark".
  static contextType = ThemeContext;
  render() {
    return <Button theme={this.context} />;
  }
}
```

To overcome the cumbersomeness `prop` introduces, Use [Composition](#composition-vs-inheritance) instead. Watch [Using Composition in React to Avoid "Prop Drilling"](https://www.youtube.com/watch?v=3XaXKiXtNjw&t=707s) for a detailed walk-through.


#### Context Workflow

1. A parent component creates a context using `React.createContext(defaultValue)`
2. A parent component creates a scope (tree node) with that context using `<Context.Provider value="abc">`
3. A child component consumes it using [.contextType](https://reactjs.org/docs/context.html#classcontexttype) static property, `useContext` hook function or `Context.Consumer` 

> `.contextType` is used for class component, while `Context.Consumer` and `useContext` are used for function component.

4. When React sees a component consumes a context, it will follow up the tree to find the provider's value. If no provider found, use the default value of the context.



!> `Context.Provider` registers the context and the context is only seeable for all descendants in the tree. The propagation from Provider to its descendant consumers (including `.contextType` <sub>implied static property of a class component</sub> and `useContext` <sub>A hook</sub>) is not subject to the `shouldComponentUpdate` method which is the normal workflow to determine if an update should perform, so the consumer is updated even when an ancestor component skips an update.


#### [Caveats](https://reactjs.org/docs/context.html#caveats)

Passing Objects and Functions as value in Provider will always cause all consumers to re-render. 
Make them as `states` to address the problem.







## Hooks


Hooks are functions that let you “hook into” React state and lifecycle features from **function** components. Thus, function components can replace the majority functionalities of class components. 

In class components, we have `componentDidMount`, `componentDidUpdate` and more lifecycle functions allowing us to do things at different stages. However, the same behavior(functions) has to split into different lifecycle functions and different behaviors are coerced together in the same lifecycle function. Thus, `hooks` come to rescue.

```jsx
// The old discussed pattern
class FriendStatusWithCounter extends React.Component {
  constructor(props) {
    super(props);
    this.state = { count: 0, isOnline: null };
    this.handleStatusChange = this.handleStatusChange.bind(this);
  }

  componentDidMount() {
    document.title = `You clicked ${this.state.count} times`;
    ChatAPI.subscribeToFriendStatus(
      this.props.friend.id,
      this.handleStatusChange
    );
  }

  componentDidUpdate() {
    document.title = `You clicked ${this.state.count} times`;
  }

  componentWillUnmount() {
    ChatAPI.unsubscribeFromFriendStatus(
      this.props.friend.id,
      this.handleStatusChange
    );
  }

  handleStatusChange(status) {
    this.setState({
      isOnline: status.isOnline
    });
  }
  // ...
```


Also, we use [render prop](#render-prop) and [HOC](https://reactjs.org/docs/higher-order-components.html) to extract duplicated code, but they all introduce a wrapper layer. We can know build our own `Hooks` to do the common **stateful** logics (a logic involves with state) and import them to different components without introducing new layers.


> The states returned by a hook are independent, meaning the state component `A` receives from a hook is totally isolated from the state component `B` receives from the same hook. This is why hooks allow us to reuse [stateful](https://reactjs.org/docs/hooks-overview.html#building-your-own-hooks) logics not state logics. This is also true for calling the same hooks in the same component.


#### Rules of hooks

1. Only **call Hooks at the top level**. Don’t call Hooks inside loops, conditions, or nested functions.

> Because the [order of hooks declared matters](https://reactjs.org/docs/hooks-rules.html#explanationt), which needs to be the same among all renders. However, loops and conditions can change the oder at runtime.

2. Only **call Hooks from React function components**. Don’t call Hooks from regular JavaScript functions. (There is just one other valid place to call Hooks — your own custom Hooks. We’ll learn about them in a moment.)



#### General Hooks

- `useState`is useful to create and store variables.
> However, unlike `this.setState` in a class, updating a state variable always replaces it instead of merging it, using hooks.

- [useRef](https://reactjs.org/docs/hooks-reference.html#useref) is particularly useful for referring to DOM elements.
- [useEffect](https://reactjs.org/docs/hooks-reference.html#useeffect) is so named because it runs **after React renders** (meaning it doesn't care if the component is mounting or updating) a given component, and will run any side-effects that we'd like to add to the render process, which we can't run inside the main function body. It also accepts a list that tells add the additional rendering only when states in the list change.

`useEffect` Hook as `componentDidMount`, `componentDidUpdate`, and `componentWillUnmount` combined.

```jsx
useEffect(() => {
  if (isEditing) {
    editFieldRef.current.focus();
  } else {
    editButtonRef.current.focus();
  }
}, [isEditing]);
```

> `useEffect` can return a function which will be automatically called [when the component updates](https://reactjs.org/docs/hooks-effect.html#explanation-why-effects-run-on-each-update). Also, `useEffect` will be replaced by a new one after each renders. Meaning [the function passed to useEffect is going to be different on every render](https://reactjs.org/docs/hooks-effect.html#detailed-explanation)

> To avoid calling `useEffect` on updates, we can [add dependencies](https://reactjs.org/docs/hooks-effect.html#tip-optimizing-performance-by-skipping-effects) that tells React to perform the side-effect only when certain states changes. **If you want to run an effect and clean it up only once (on mount and unmount), you can pass an empty array ([]) as a second argument.**

#### Custom Hooks

A custom Hook is a JavaScript function whose name starts with ”use” and that may call other Hooks. Therefore, Custom Hooks are essentially a wrapper of built-in Hooks and states.



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


## Routing

In original scenarios, when user click on a button to jump into a new page, the request is send to the *Server side*, and request a new page to the client to render. Clients are allowed to jump from pages to pages, and all pages have different paths. This is called `Server-Side-Routing`.

Now, with React, we have a single webPage, with many different views(components). Each time we click on a button, we have the views to be swapped, instead of having a totally different page. Hence, we need to handle views routing. This is called `Client-Side-Routing`.

#### [React Router](https://reactrouter.com/en/main)



## Render Prop

Render prop is a technique for sharing code between React components using a prop whose value is a function.

There are two scenarios that are identical but viewed in different perspectives that use `render prop`

1. When we have a common feature (state or method) that want to be used with different components.

2. When serval components have the same feature, thus there's duplication of code.

To solve the second scenario, we extract an additional wrapper, that contains the common feature (state or method). Thus the problem is reduced to the first scenario.

![render prop architecture](/FrontEnd/React/Assets/render-prop.png)

Suppose, `Component1` and `Component2` both have a `counter`, and we extract the the `counter` and its `setter` to a wrapper to reduce code duplication, as follows.

```jsx
class Wrapper extends React.Component {
  constructor(props) {
    super(props);
    // the common state
    this.state = { count: 0};
  }
  // The common method
  handler = () => {
    this.setState({count: this.state.count + 1});
  }

  render() {
    return (
      <div>
        <Component1 count={count} handler={handler}>
      </div>
    )
  }
}
```

> Now, we can pass the common features from wrapper to `Component1` getting closer to the architecture in the image. But the problem is that the layout of Wrapper is fixed, if we want to use it with `Component2` we have to specify another wrapper that have exactly the same layout except returning `Component2`. So basically, we add another layer of abstraction and the code duplication is not solved. Or we can use condition rendering, but it's hard to scale up, it's ridiculous to write `if` statements to handle if we have 5 Components or even more.

Remember, [Composition](#composition-vs-inheritance) is a good for components that don’t know their children ahead of time. So we have flexibility over the children of a component. 

```jsx
class App extends React.Component {
  render() {
    return (
      <Wrapper>
        <Component1 count={???}>
        // OR <Component2 count={???}> 
      </Wrapper>
    )
  }
}

class Wrapper extends React.Component {
  constructor(props) {
    super(props);
    // the common state
    this.state = { count: 0};
  }
  // The common method
  handler = () => {
    this.setState({count: this.state.count + 1});
  }

  render() {
    return (
      <div>
        {this.props.children}
      </div>
    )
  }
}
```

> Now, we're getting closer to our goal, now we can swap the children of `Wrapper` as we want. However, we lose `state` information and methods. As `App` component doesn't own these features. One of solving this problem is simply lifting the `state` into `App` component. But what if the states are more semantic and make more sense in the `Wrapper` (here we just name it `Wrapper` but it can be something meaningful in reality)? By doing so, we sacrifice organization of our code.

With the idea of `Composition`, we can pass a function from `App` that tells what `Wrapper` should do, and in `Wrapper` it calls the function and passes the states it owns. The function here is what we call `render prop`.

```jsx
class App extends React.Component {
  render() {
    return (
      <Wrapper render={count => <Component1 count={count}>}}>
      <Wrapper render={count => <Component2 count={count}>}}>
    )
  }
}

class Wrapper extends React.Component {
  constructor(props) {
    super(props);
    // the common state
    this.state = { count: 0};
  }
  // The common method
  handler = () => {
    this.setState({count: this.state.count + 1});
  }

  render() {
    return (
      <div>
        this.props.render(this.state.count);
      </div>
    )
  }
}
```

