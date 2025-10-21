## Platform

Note that there are only three possible platforms that Electron can run in: **win32** (Windows), **linux** (Linux), and **darwin** (macOS).


## Main scripts


Every Electron app starts with a **main script**, very similar to how a Node.js application is started. The main script runs in the **"main process".** To display a user interface, the main process creates renderer processes – usually in the form of windows, which Electron calls  `BrowserWindow`.

To get started, pretend that the main process is just like a Node.js process. All APIs and features found in Electron are accessible through the electron module, which can be required like any other Node.js module.


> It runs in a Node.js environment and is responsible for controlling your app's lifecycle, displaying native interfaces, performing privileged operations, and managing renderer processes (more on that later).


```js
const { app, BrowserWindow } = require('electron')
```

In the first line, we are importing two Electron modules with CommonJS module syntax:

[`app`](http://electronjs.org/docs/latest/api/app), which controls your application's event lifecycle.
[`BrowserWindow`](https://www.electronjs.org/docs/latest/api/browser-window), which creates and manages app windows.

> You might have noticed the capitalization difference between the app and BrowserWindow modules. Electron follows typical JavaScript conventions here, where PascalCase modules are instantiable class constructors (e.g. BrowserWindow, Tray, Notification) whereas camelCase modules are not instantiable (e.g. app, ipcRenderer, webContents).

**Electron's main process is a Node.js environment that has full operating system access. Each Electron app has a single main process**

The main process' primary purpose is to create and **manage application windows** with the `BrowserWindow` module.

## Renderer Process

Each web page your app displays in a window will run in a separate process called a **renderer process** (or simply renderer for short). Renderer processes have access to the same JavaScript APIs and tooling you use for typical front-end web development, such as using webpack to bundle and minify your code or React to build your user interfaces.


**Renderer processes run web pages and do not run Node.js by default for security reasons.**


## Application Behavior on different OS


### Windows / Linux

Application windows behave differently on each operating system. Rather than enforce these conventions by default, Electron gives you the choice to implement them in your app code if you wish to follow them. 

By convention,  the app is closed entirely when all windows are closed (Windows & Linux), to follow

```js
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') app.quit()
})
```


### Mac

MacOS apps generally continue running even without any windows open. Activating the app when no windows are available should open a new one.


```js
app.whenReady().then(() => {
  createWindow()

  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow()
  })
})
```

> Because windows cannot be created before the ready event, you should only listen for activate events after your app is initialized. Do this by only listening for activate events inside your existing whenReady() callback.




## Preload Script

Electron's main process is a Node.js environment that has full operating system access. On top of Electron modules, you can also access Node.js built-ins, as well as any packages installed via npm. On the other hand, renderer processes run web pages and do not run Node.js by default for security reasons.

To **bridge** Electron's different process types together, we will need to use a special script called a preload.

**Preload scripts are injected before a web page loads in the renderer**

Preload script shares a global `Window` interface with the renderers and can access Node.js APIs, it serves to enhance your renderer by exposing arbitrary APIs in the window global that your web contents can then consume.

Although preload scripts share a window global with the renderer they're attached to, you cannot directly attach any variables from the preload script to window because of the [contextIsolation](#context-isolation) default.

```js
// preload.js
window.myAPI = {
  desktop: true
}
```

```js
// renderer.js
console.log(window.myAPI)
// => undefined
```


> Since Electron 20, preload scripts are **sandboxed** by default and no longer have access to a full Node.js environment.

> The limited APIs available include

| API                | Detail                                                |
| ------------------ | ----------------------------------------------------- |
| Electron modules   | Renderer process modules                              |
| Node.js modules    | `events`, `timers`, `url`                             |
| Polyfilled globals | `Buffer`, `process`, `clearImmediate`, `setImmediate` |

> try use commonJS instead of ESM, where using ESM imports has a lot of caveats.



## IPC

Since it is not possible to access the Node.js APIs directly from the **renderer process**, nor the HTML Document Object Model (DOM) from the **main process**.

The solution for this problem is to use Electron's `ipcMain` and `ipcRenderer` modules for inter-process communication (IPC). 


We can set up ipcMain in the main process

```js
const { app, BrowserWindow, ipcMain } = require('electron/main')

const path = require('node:path')

const createWindow = () => {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js')
    }
  })
  win.loadFile('index.html')
}
app.whenReady().then(() => {
  ipcMain.handle('ping', () => 'pong')
  createWindow()
})
```

Since renderer.js runs in the renderer process, or in a web env, it doesn not have access to the `ipcRenderer` module, we need to use preload script to enable it.


```js
// preload.js
const { contextBridge, ipcRenderer } = require('electron')

contextBridge.exposeInMainWorld('versions', {
  node: () => process.versions.node,
  chrome: () => process.versions.chrome,
  electron: () => process.versions.electron,
  ping: () => ipcRenderer.invoke('ping')
  // we can also expose variables, not just functions
})
```

```js
// renderer.js
const func = async () => {
  const response = await window.versions.ping()
  console.log(response) // prints out 'pong'
}

func()
```

These channels are **arbitrary** (you can name them anything you want) and **bidirectional** (you can use the same channel name for both modules).

> Never expose the whole priviliged function / properties directly to the `windows` via brigde, this gives the renderer full access, instead, give them a controlled function that can be invoked with controlled inputs.


### [Pattern 1: Renderer to main (one-way)](https://www.electronjs.org/docs/latest/tutorial/ipc#pattern-1-renderer-to-main-one-way)

you can use the `ipcRenderer.send` API to send a message that is then received by the `ipcMain.on API`.


### [Pattern 2: Renderer to main (two-way)](https://www.electronjs.org/docs/latest/tutorial/ipc#pattern-2-renderer-to-main-two-way)

This can be done by using `ipcRenderer.invoke` paired with `ipcMain.handle`.

The difference from pattern 1 is that `handle` will have a return value that invoke can consume.

### [Pattern 3: Main to renderer](https://www.electronjs.org/docs/latest/tutorial/ipc#pattern-3-main-to-renderer)


When sending a message from the main process to a renderer process, you need to specify which renderer is receiving the message. Messages need to be sent to a renderer process via its `WebContents` instance

```js
click: () => mainWindow.webContents.send('update-counter', -1)
```

```js
// main.js
const { app, BrowserWindow, Menu, ipcMain } = require('electron')

const path = require('node:path')

function createWindow () {
  const mainWindow = new BrowserWindow({
    webPreferences: {
      preload: path.join(__dirname, 'preload.js')
    }
  })

  const menu = Menu.buildFromTemplate([
    {
      label: app.name,
      submenu: [
        {
          click: () => mainWindow.webContents.send('update-counter', 1),
          label: 'Increment'
        },
        {
          click: () => mainWindow.webContents.send('update-counter', -1),
          label: 'Decrement'
        }
      ]
    }
  ])
  Menu.setApplicationMenu(menu)

  mainWindow.loadFile('index.html')
}
// ...
```

```js
// preload.js omitted
```

```js
// renderer.js
const counter = document.getElementById('counter')

window.electronAPI.onUpdateCounter((value) => {
  const oldValue = Number(counter.innerText)
  const newValue = oldValue + value
  counter.innerText = newValue.toString()
})
```

#### Return value

Unlike `ipcRenderer.invoke` that can have a return value, we can only achive the return value by passing an additional `ipcRenderer.send` within the callback funcion.


```js
// preload.js
const { contextBridge, ipcRenderer } = require('electron')

contextBridge.exposeInMainWorld('electronAPI', {
  onUpdateCounter: (callback) => ipcRenderer.on('update-counter', (_event, value) => callback(value)),
  counterValue: (value) => ipcRenderer.send('counter-value', value)
})
```

```js
// renderer.js
const counter = document.getElementById('counter')

window.electronAPI.onUpdateCounter((value) => {
  const oldValue = Number(counter.innerText)
  const newValue = oldValue + value
  counter.innerText = newValue.toString()
  window.electronAPI.counterValue(newValue)
})
```







## [The Unitility Process](https://www.electronjs.org/docs/latest/tutorial/process-model#the-utility-process)

An Electron app can always **prefer** the UtilityProcess API over Node.js `child_process.fork` API when there is need to fork a child process from the main process, as the utility process can establish a communication channel with a renderer process using [`MessagePorts`](https://developer.mozilla.org/en-US/docs/Web/API/MessagePort)


## Context Isolation

Context Isolation is a feature that ensures that both your **preload scripts** and Electron's **internal** logic run in a separate context to the website you load in a `webContents` (html).

## Sandbox

### Sandbox-Renderer Process

When renderer processes in Electron are sandboxed, they behave in the same way as a regular Chrome renderer would. **A sandboxed renderer won't have a Node.js environment initialized**.


### Sandbox-Preload Scripts

Because the `require` function in **preload scripts** is a polyfill with limited functionality, you will not be able to use `CommonJS modules` to separate your preload script into multiple files. If you need to split your preload code, use a bundler such as `webpack` or `Parcel`.

### Disable sandboxing

In Electron, renderer sandboxing can be disabled on a per-process basis with the `sandbox: false` preference in the BrowserWindow constructor **or** whenever **Node.js integration is enabled** in the renderer.


```js
const win = new BrowserWindow({
    webPreferences: {
      sandbox: false
    }
  })
// or
const win = new BrowserWindow({
    webPreferences: {
      nodeIntegration: true
    }
  })
```


## Performance

1. [Analyze runtime performance](https://developer.chrome.com/docs/devtools/performance/)

### Analyze module 

``` bash
node --cpu-prof --heap-prof -e "require('request')"
```

### Loading and running code too soon

Bad example, where loading `foo-parser` module can be very expensive

```js
const fs = require('node:fs')

const fooParser = require('foo-parser')

class Parser {
  constructor () {
    this.files = fs.readdirSync('.')
  }

  getParsedFiles () {
    return fooParser.parse(this.files)
  }
}

const parser = new Parser()

module.exports = { parser }
```

instead, we can defer loading the module only when needed, e.g. when `getParsedFiles` is called

```js
// "fs" is likely already being loaded, so the `require()` call is cheap
const fs = require('node:fs')

class Parser {
  async getFiles () {
    // Touch the disk as soon as `getFiles` is called, not sooner.
    // Also, ensure that we're not blocking other operations by using
    // the asynchronous version.
    this.files = this.files || await fs.promises.readdir('.')

    return this.files
  }

  async getParsedFiles () {
    // Our fictitious foo-parser is a big and expensive module to load, so
    // defer that work until we actually need to parse files.
    // Since `require()` comes with a module cache, the `require()` call
    // will only be expensive once - subsequent calls of `getParsedFiles()`
    // will be faster.
    const fooParser = require('foo-parser')
    const files = await this.getFiles()

    return fooParser.parse(files)
  }
}

// This operation is now a lot cheaper than in our previous example
const parser = new Parser()

module.exports = { parser }
```

[Reference](https://www.electronjs.org/docs/latest/tutorial/performance#how-1)


> Scope of `requrie`

```js
function processData() {
    const path = require('path'); // Only available in this function
    return path.join('folder', 'file.txt');
}

console.log(path); // ❌ ReferenceError: path is not defined
```

However, even if you require the same module in different scopes, Node.js returns the cached instance.

```js
function funcA() {
    const moment = require('moment');
    return moment().format();
}

function funcB() {
    const moment = require('moment'); // Same cached instance
    return moment().add(1, 'day');
}
```

### Process

Electron's powerful multi-process architecture stands ready to assist you with your long-running tasks. The **main process** handles windows, interactions, and the communication between various components inside your app. It also houses the **UI thread**.





