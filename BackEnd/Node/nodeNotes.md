# Node

Node is not a programming language, or framework, it is a **runtime ENVIRONMENT** for Javascript. Node is a CPP program that is embedded with a Chrome V8 engine that provides JS runtime environment. With Node, now JS can be run not only inside a browser. Also, since, it's run by a cpp program natively on a computer environment, not JS can access file system and system info and etc, which makes it perfect for a serer. 

Since now the env is provided by node, and no longer is browser, many evn properties of browser are not available any more. For example, `document` which is a property of `window` is undefined inside node. While, Node provides other modules and global properties to allow to interact with the system and HTTP. For example, `global` object, and `HTTP` module.

> `document`, in browser, will be automatically prefixed with `window`

## Module 

Modularization is a common pattern in modern programming languages. In NodeJs, [Module Wrapper Function](https://youtu.be/TlB_eWDSMt4?t=1981) is used to encapsulate.

```js
// log.js

let a = 10

func log() {
    console.log(abc)
}

module.exports = log

// module.exports = {
//     log = log
// }

// app.js
const log = require('log')
```

In the above code snippet, we use `module.exports` to export properties that we wish to be exposed to the outside. And use `require` to import. Here `module` is actually **NOT** a global property. When the program runs, Node will automatically wrap the whole file (`log.js`) with a function, called **Module Wrapper Function** in the following form:

```js
func (exports, require, module, ...) {
    let a = 10

    func log() {
        ...
    }
    ...
}
```

**Whenever a file calls `require`, the imported MWF will be called**. (`module` property of app.js will be passed as **REFERENCE** in as argument). Hence, statement `module.export = ` will be run. Now, since the importing module follow the syntax to be only allowed to access properties from `module.export`, we achieve encapsulation.

> Since `require` will run the imported MWF, the following print will be printed, as well as the variable declaration. However, since `a` is not exported, it can not be accessed.


```js
// log.js
let a = 10
console.log(10)
```