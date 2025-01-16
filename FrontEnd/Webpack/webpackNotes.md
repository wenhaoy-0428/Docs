# Webpack

Webpack is a module bundler for `JS` and `JS` only, there are also loaders play like plugins to allow it work with `css`, `scss` files. 

What Webpack does is bundle multiple JS modules into a single `main.js`(the name is improvised here). Thus, in development, we can have human-readable organization of our code layout, and a single, linted JS file for publication. 

Webpack offers similar job as `Parcel` and it's internally included in React.

## Loaders

Webpack by default only knows how to bundle JS files. However, in modern development, we may import not only js files, but css and other formats. Thus, we need a pre-processor that can help to bundle. This is loader.

A demonstration video can be found at [https://www.youtube.com/watch?v=gtZs1BPgf6Y](https://youtu.be/gtZs1BPgf6Y?t=108)


## [Module Federation](https://www.youtube.com/watch?v=D3XYAx30CNc&t=326s)

Share code between 2 projects.


## [Code Splitting](https://webpack.js.org/guides/code-splitting/)

Code Splitting allows you to split your code into various bundles. This can help to reduce the load time.

There're 3 general approaches 

1. Entry Points
2. SplitChunksPlugin
3. Dynamic Imports

### Dynamic Imports

[This is a built-in feature that ES6 supports](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Modules#dynamic_module_loading). The most important effects of this function is that lazy loading is possible. Certain modules can be imported only when certain conditions are met. Reducing the initial bundle size. This is also the essence of how react lazy works. [React code splitting](https://legacy.reactjs.org/docs/code-splitting.html#:~:text=is%20first%20rendered.-,React.,export%20containing%20a%20React%20component.)


## [Treeshaking](https://webpack.js.org/guides/tree-shaking/)

Tree shaking is a term commonly used in the JavaScript context for dead-code elimination.
