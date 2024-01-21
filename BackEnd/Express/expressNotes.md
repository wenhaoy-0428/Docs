# Express

Express is a framework for JS to alleviate some of the pain of writing server.

```js
// returns a function
const express = require('express')
// returns a Express object, by convention named app
const app = express()
```

When coding a serer With vanilla Node, we normally have the following code with the [Http module](https://nodejs.org/api/http.html) for URLs of requests

```js
const http = require('http');

const server = http.createServer((req, res) => {
    if (req.url === '/') {
        console.log('Home')
    }

    if (req.url === '/user') {
        console.log('user')
    }
})

server.listen(3000)
```

This approach looks ridiculous at the first gander as we have to put all branches inside a single function and uncountable if statements as the program grows.

Hence, Express provides more elegant way of doing this.

## Project SetUp

For more detail reference [How to Use TypeScript in a Node.js and Express Project](https://www.pullrequest.com/blog/intro-to-using-typescript-in-a-nodejs-express-project/) and [How to use express in typescript ?](https://www.geeksforgeeks.org/how-to-use-express-in-typescript/)

```bash
# init project
npm init -y

# add express
npm install express

# install ts related dependencies
npm install typescript ts-node @types/node @types/express --save-dev

# install nodemon so that server is automatically restarted to reflect changes.
npm install nodemon --save-dev

# Configure TS
npx tsc --init

# add package.json start script

"scripts": {
  "start": "nodemon app.ts",
  "test": "echo \"Error: no test specified\" && exit 1"
},
```

> For TS dependencies check [TypeScript](../TypeScript/tsNotes.md)

## Route

A simple way of getting rid of such many if statements is: 

```js
const express = require('express');
const app = express();

app.get('/', (req, res) => {
    console.log('home')
})

app.post('/user', (req, res) => {
    console.log('post')
})

app.get('/user/hello', (req, res) => {
    console.log('post')
})

app.get('/user/world', (req, res) => {
    console.log('post')
})

app.listen(3000);
```

This did avoid if statements, however, we still defining all the URLs inside the same file. For `user` related paths, we hope to have a nested route, where all `user` related routes are defined inside the same file like [Django](../Django/djangoNotes.md). 

[Router](https://youtu.be/SccSCuHhOw0?t=664) of Express is the handful tool for this purpose.

```js
// app.js
const express = require('express');
const app = express();
const userRouter = require('./routes/users');


// Mount the router as middleware using the app.use() method:
app.use('/users', userRouter);

app.listen(3000)
```

```js
// users.js
const express = require('express');
const router = express.Router();

// Define routes
router.get('/', (req, res) => {
  res.send('Hello, this is the homepage!');
});

router.get('/about/:id', (req, res) => {
  console.log(req.params.id)
});

// You can also group routes that share a common URL prefix
router.get('/api/users', (req, res) => {
  // Return a list of users from your database or any other data source
  
  res.json({ users: [...] });
  
});

module.exports = router;
```

> [app.use](#todo)

### Dynamic Routes

For routes with dynamic parameters like `id` the syntax of the url is `:id`

```js
router.get('/:id', (req, res) => {
  console.log(req.params.id)
});
```

**Static Routes should always be placed before dynamic routes**

```js
router.get('/:id', (req, res) => {
  console.log(req.params.id)
});

router.get('/new', (req, res) => {
  console.log('new')
});
```

In the above code snippet, the new block will actually never be called. Since, A request to URL `/new` will be matched to `id` first as Express reads routes from top to bottom. Hence, `new` will be treated as the id.

For dynamic routes with the same path but different methods we can use `router.route` to chain them.

```js
router.get('/:id', (req, res) => {
  console.log(req.params.id)
});

router.put('/:id', (req, res) => {
  console.log(req.params.id)
});

router.post('/:id', (req, res) => {
  console.log(req.params.id)
});

router.delete('/:id', (req, res) => {
  console.log(req.params.id)
});

router.route('/:id')
.get((req,res) => {

})
.post()
.delete()
```

To further reduce complexity when a snippet of code will run in all above methods is [route.param](https://youtu.be/SccSCuHhOw0?t=1261), which will be called whenever a specific param is discovered.

## Middleware

To define a middleware, we use the syntax of `function middleware(req, res, next)` and `app.use` to use the middleware.

```js
app.get('/' (req, res) => {

})

app.use(logger);

app.get('/new', (req, res) => {

})

function logger(req, res, next) {
    next();
}
```

Only routes defined after the `use` statement will be passed through the middleware. Hence, it's always a good practice to place the `use` statement at the very top.

> Hence, the above code URL `/` will not be passed through logger, while `/new` will.

`next` is a function that tells Express the move on to the next middleware. If we don't call it explicitly, the request will be stuck in this middleware and will not continue, which will result in infinite loading for the client. 

Also, for a handling function, there's actually a `next` argument as well, hence, it can be regarded as a layer of middleware, only that it's the last layer so that there is no much need to call it.

### Middleware for individual route

For define middleware for a single route, we pass the function as argument,

```js
app.get('/', middleware1, middleware2, middleware3, (req, res) => {

})
```

> We can pass as many middleware as we want, and they will be called in order.

Also, we can define middleware for the [Router](#route)

```js
router.use(logger)
```

so that only routes defined inside `router` will be passed through the middleware.




