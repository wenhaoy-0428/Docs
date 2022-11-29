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



## [Virtual DOM](https://reactjs.org/docs/faq-internals.html#what-is-the-virtual-dom)
//TODO

## [JSX](https://reactjs.org/docs/jsx-in-depth.html)
//TODO