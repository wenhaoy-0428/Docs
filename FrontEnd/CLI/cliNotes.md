# Package Manager

What is `npm` or `yarn`?

`npm` is a package manager tool. There's a also a package registry, that is the central place (server) where a package manager tool downloads all the packages from, named the same. 

`yarn` is also a package manager tool. 

> Since `yarn` is package manager tools, and `npm` is a package registry, it's possible that we use `yarn` as tool and `npm` registry running behind. 



## [Example Walk through](https://developer.mozilla.org/en-US/docs/Learn/Tools_and_testing/Understanding_client-side_tools/Package_management#initialise_a_new_project)



## [Upgrade packages](https://developer.mozilla.org/en-US/docs/Learn/Tools_and_testing/Understanding_client-side_tools/Package_management#updating_dependencies)

```bash
npm update
```

It's important to remember that `npm update` will not upgrade the dependencies to beyond the range defined in the `package.json` — to do this you will need to install that version specifically.

## [Install packages]

- To install locally (only for the current project)
```bash
npm install pkg1 pkg2
```

- To install globally (for the whole computer environment)
```bash
npm install --globally pkg1 pkg2
```

- To install only for development
```bash
npm install --save-dev pkg1 pkg2
```

> This keyword tells the npm tool that these particular dependencies are only needed for development (npm therefore lists them in the `package.json` file under `devDependencies`, not `dependencies`)


## [Move devDependencies to dependencies](https://stackoverflow.com/questions/46903002/move-a-module-from-devdependencies-to-dependencies-in-npm-package-json)

```bash
# devD -> dep
npm i <module_name> -P

# dep -> devD
npm i <module_name> -D
```

# Parcel

Parcel is a front-end tool with many built-in features, including `serving`, `tree shaking`, `auto dependency installation`, `compilation`, and etc.

Parcel expects an `index.html` and an `index.js` file to work with.

## Serve

```bash
parcel index.html
```

> This serves the website as development, and supports many features benefit development

#### Serve for development

```bash
parcel serve index.html
```
> Same as omitting `serve` keyword

#### Serve for production

```bash
parcel build index.html
```

The destination for our production files is the dist directory.

#### Tree shaking

```bash
parcel build index.html --experimental-scope-hoisting
```

