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


When sending a message from the main process to a renderer process, you need to specify which renderer is receiving the message. Messages need to be sent to a renderer process via its WebContents instance









## [The Unitility Process](https://www.electronjs.org/docs/latest/tutorial/process-model#the-utility-process)

An Electron app can always **prefer** the UtilityProcess API over Node.js `child_process.fork` API when there is need to fork a child process from the main process, as the utility process can establish a communication channel with a renderer process using [`MessagePorts`](https://developer.mozilla.org/en-US/docs/Web/API/MessagePort)


## Context Isolation

Context Isolation is a feature that ensures that both your **preload scripts** and Electron's **internal** logic run in a separate context to the website you load in a `webContents` (html).

