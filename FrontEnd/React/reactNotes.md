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

## [Add React to a website without create a react app](https://reactjs.org/docs/add-react-to-a-website.html)


## Variables

JSX see variables in curly braces. In the following example, `logo` is identified as a variable.
```js
<img src={logo} className="App-logo" alt="logo" />
```

## Component

#### prop

A `prop` is any data passed into a React component. React `props` are comparable to HTML attributes.

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







## [Virtual DOM](https://reactjs.org/docs/faq-internals.html#what-is-the-virtual-dom)
//TODO

## [JSX](https://reactjs.org/docs/jsx-in-depth.html)
//TODO