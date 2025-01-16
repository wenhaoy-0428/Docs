# Main Workflow

1. Use JS framework, like React to utilize its component features to build the web application

2. Use SCSS to create CSS or use Postcss directly for nesting and TailWind for framework if needed.

3. Use module bundlers (Webpack, Parcel) to build all files(modules) into single, compact production files. 

4. Deploy.

> module bundlers are normally included in a framework. And JS test framework like Jest should also be considered using.

# Technologies

## [ESLint](https://juejin.cn/post/6959825653029928968)

JS is not a type free language and certain errors can only be spotted when running. Therefore, the linting process is a is a pre-processing to check potential grammar errors of JS.

## Babel

It's mainly for 

Converts JSX to JavaScript: Babel transforms JSX syntax into standard JavaScript function calls. For example, <div>Hello, World!</div> is converted to React.createElement('div', null, 'Hello, World!').

## [Webpack](./Webpack/webpackNotes.md)

Webpack is a module bundler for `JS` and `JS` only, there are also loaders play like plugins to allow it work with `css`, `scss` files.

### What problems does Webpack solve?

1. compatibility issue for modules in JS

For modular design of JS, it seems like a very common function for many languages, but was not built in for JS at the beginning. Therefore, in old days, `import` was unavailable and for multiple JS files, there had to be multiple `script` tags associated.

Since ES6 standards, `import` became a standard and near all modern browsers support `<script type="module" src....>` to load modules. However, for compatibility issues for older browsers,  `webpack` and similar tools can be used, as they will bundle all the JS files into a single file.

2. Even though modern browsers support importing modules in HTML, for react, and many other libraries that are used during development, we have to specify the an [import map](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Modules#remapping_module_paths) and process may be cumbersome. 

3. Bundlers like webpack, though — bundlers still do a good job at partitioning code into reasonably sized chunks, and are able to do other optimizations like minification, dead code elimination, and tree-shaking. From [A background on modules](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Modules#a_background_on_modules)

> For reference: [How do I include a JavaScript file in another JavaScript file?](https://stackoverflow.com/questions/950087/how-do-i-include-a-javascript-file-in-another-javascript-file)

## SCSS

SCSS is a CSS preprocessor that allows easier CSS variables and CSS nesting.

## Postcss 

Postcss is a post-processor that mainly serves as a tool to add fallback properties to support browser compatibility. However, it also serves the functionality a preprocessor does. 

## [Webpack + SCSS + PostCSS](https://www.youtube.com/watch?v=SH6Y_MQzFVw&t=9s)


## [TailWind CSS](https://www.youtube.com/watch?v=mr15Xzb1Ook)

This is a CSS framework that includes a bunch of classes that you can use. 





## Edge Side Includes


## Server side Includes