# TypeScript


## Basic SetUp

Install

```bash
npm i -g typescript
```

Compile

```bash
tsc test.js
```

To configure the compilation procedure, it's common to create a `tsconfig.json` file that stores all the settings, which can be easily done by running:

```bash
tsc --init
```

Inside the json file, we can change the output JS version, source dir, output dir and etc. A quick intro can be found at [Configuring TS Compiler](https://youtu.be/d56mG7DezGs?t=800)

To work with Node and [Express](../Express/expressNotes.md), more dependencies are required.

```bash
npm install typescript ts-node @types/node @types/express --save-dev
```

> Even the project is writing in TS, they will be compiled into vanilla JS in production. So we add these dependencies as dev.

- `ts-node`: allows us to run ts code directly with Node, so that we don't have to call `tsc` to translate the TS files into JS files then call `node target.js`. Instead `ts-node target.ts`.

- `@types/express` or `@types/node`: provides type declarations. This sounds confusing at first. In TS, we have [Interfaces]() that defines the class (type). The same as a header file.
Since express and node are native to JS. They classes they declare like `Request` has to be explicitly declared with an Interface.

```ts
import express from 'express';

// Custom interface for Request object
interface MyRequest extends express.Request {
  // Define any additional custom properties you might need
  customProperty: string;
}

// Custom interface for Response object
interface MyResponse extends express.Response {
  // Define any additional custom methods or properties you might need
  customMethod: () => void;
}

const app = express();

app.get('/', (req: MyRequest, res: MyResponse) => {
  // Use the custom properties or methods defined in the interfaces
  req.customProperty = 'Hello';
  res.customMethod();

  // Regular Express functionality
  res.send('Hello, World!');
});

app.listen(3000, () => {
  console.log('Server is running on http://localhost:3000');
});
```

These dependencies help to write all the interfaces that express and node have builtin.

```ts
import express, { Request, Response } from 'express';

const app = express();

app.get('/', (req: Request, res: Response) => {
  // Regular Express functionality
  res.send('Hello, World!');
});

app.listen(3000, () => {
  console.log('Server is running on http://localhost:3000');
});
```


## Type Security

### Variables
Most built-in types of TS are those common ones. More than that, TS has some more types like `any`, `unknown`...

```ts
let a: number = 10;
let b = 10;
let c;
```

TS compiler can infer types based on value. Hence, `a` and `b` are both numbers in the above code. Hence, changing their value to a string will cause error at compile time. However, since `c` is variable without a value. It's type is `any`. We can assign it with a number and later change it to a string.

### Functions

For functions, all arguments have to be **explicitly** declared their types. For the following code, `document` has an **implicit** type of `any`. Hence, it will throw an error on type check. If we truly want the argument to be `any` like the function itself doesn't care about the type of argument, we can explicitly add `document: any` to dismiss the error.

```ts
// error
function render(document) {
    console.log(document);
}

function render(document: any) {
    console.log(document);
}
```

> In `tsconfig.json` file, we can turn off `strict` to allow argument to be implicit any type. However, this loses the purpose of TS and is a bad practice to do.

## Type Declaration

### Type Alias

To declare a type, we can use `type` keyword to declare type alias.

```ts
type Employee = {
  readonly id: number;
  name: string;
  retire: (date: Date) => void
}

let employee: Employee = {
  ...
  ...
}
```

Type Alias can be used to declare type for anything, classes, functions, objects. It also support type union, intersection operations to create new type.

```ts
type Employee = People & Worker

type Chinese = Han | {
  language: Chinese
}
```

## Interface

Same as Type Alias, `interface` is another keyword that works nearly identical to type alias. 

```ts
// a function declaration
interface Video {
  (time: number): Promise<boolean>
}

interface Object extends Parent {
  value1: number
}
```

They can both be used interchangeably. Like A type alisa union with an interface, or an interface extends from a type alias. 

> Note, when combining type alias with interface, type alias has to be explicit, for example, a type alias of a **union** can not work with an interface to create new type.

Also, same interfaces will be merged while type alias will throw error.

```ts
interface User {
  name: string;
}

interface User {
  age: number
}
```

### [Difference Between Type Alias and interface](https://www.youtube.com/watch?v=QYO-sieqLD4)

Extends is exclusive to interfaces, however, type alias can use type intersection to achieve the same behavior.


```ts
interface Child extends Parent {

}

type Child = Parent & {

}
```


> A good practice is to use type alias as much as possible and only use interface when needed.

## [d.ts](https://www.youtube.com/watch?v=s_CZeWuEZ_s&t=278s)

`d.ts` file is kinda like header file in CPP. It's designed to store all [type declarations](#type-declaration) and type declarations only. We can define type in a single file and import the d.ts file in multiple places to reduce duplicated code.




