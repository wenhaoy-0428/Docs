# TypeScript


## Basic SetUp

**Install**

```bash
npm i -g typescript
```

**Compile**

```bash
tsc test.js
```

To configure the compilation procedure, it's common to create a `tsconfig.json` file that stores all the settings, which can be easily done by running:

```bash
tsc --init
```

Inside the json file, we can change the output JS version, source dir, output dir and etc. A quick intro can be found at [Configuring TS Compiler](https://youtu.be/d56mG7DezGs?t=800)

For debugging, `sourceMap` inside `tsconfig.json` has to be enabled. Inside the `launch.json` which defines the behavior of launching the debug session.   

```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "type": "node",
            "request": "launch",
            "name": "Launch Program",
            "skipFiles": [
                "<node_internals>/**"
            ],
            "program": "${workspaceFolder}/index.ts",
            "preLaunchTask": "tsc: build - tsconfig.json",
            "outFiles": [
                "${workspaceFolder}/**/*.js"
            ]
        }
    ]
}
```

> The `preLaunchTask` defines a task that compiles the Ts code into Js code before running the debug session.

More of debugging can be found at the [official doc](https://code.visualstudio.com/docs/typescript/typescript-debugging) or a quick reference from [YouTube](https://www.youtube.com/watch?v=d56mG7DezGs&t=1044s)



To work with Node and [Express](../Express/expressNotes.md), more dependencies are required.

```bash
npm install typescript ts-node @types/node @types/express --save-dev
```

> Even the project is writing in TS, they will be compiled into vanilla JS in production. So we add these dependencies as dev.

- `ts-node`: allows us to run ts code directly with Node, so that we don't have to call `tsc` to translate the TS files into JS files then call `node target.js`. Instead `ts-node target.ts`.

- `@types/express` or `@types/node`: provides type declarations. This sounds confusing at first. In TS, we have [Interfaces](#interface) that defines the class (type). The same as a header file.
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

TS compiler can infer types based on value. Hence, `a` and `b` are both numbers in the above code. Hence, changing their value to a string will cause error at compile time. However, since `c` is variable without a value. It's type is `any`. **We can assign it with a number and later change it to a string.** This basically makes the Ts Js.


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

### Literal Types

```ts
// literally only 50 or 100
type Quantity = 50 | 100;
let quantity: Quantity = 50;

let quantity: Quantity = 20; // ERROR
```

**However, Ts infers the type of a object property as value first.**

```ts
declare function handleRequest(url: string, method: "GET" | "POST"): void;
 
const req = { url: "https://example.com", method: "GET" };
handleRequest(req.url, req.method);
```

> In the above code snippet, `req.method` is inferred as a string with value `GET`, instead of type of `GET`, as this is object initialization. To resolve this issue, consider [type assertion](#type-assertions)

```ts
// I intend for req.method to always have the literal type "GET"”
const req = { url: "https://example.com", method: "GET" as "GET" };
const req = { url: "https://example.com", method: "GET" as const };
//OR
// I know req.method has the value "GET"“ (personal guarantee only, we can still change it before calling handleRequest)
handleRequest(req.url, req.method as "GET");
```

### ReadonlyArray

We know Array is self can be constant, but its internal content is always mutable after going through the JS world. However, Ts gives us an option to make it constant internally by declaring a normal array as `ReadOnlyArray`

```ts
const roArray: ReadonlyArray<string> = ["red", "green", "blue"];

// function call
function doStuff(values: ReadonlyArray<string>) {...}
// or
function doStuff(values: readonly string[]) {...}
```

> Tuples can be `readonly` as well but has to follow the second notation when called.

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


Almost all features of an interface are available in type, **the key distinction is that a type cannot be re-opened to add new properties vs an interface which is always extendable.**

> interfaces that are declared multiple times will be merged while type alias will throw error.

```ts
interface User {
  name: string;
}

interface User {
  age: number
}
```

### [Difference Between Type Alias and interface](https://www.youtube.com/watch?v=QYO-sieqLD4)

`extend` keyword is exclusive to interfaces, however, type alias can use type intersection to achieve the same behavior.


```ts
interface Child extends Parent {

}

type Child = Parent & {

}
```


> A good practice is to use type alias as much as possible and only use interface when needed.




### Optional Property Access Operator

```ts
// customer can potentially be null or undefined
let customer = getCustomer();

// instead of writing checks like this:
if (customer != null && customer customer != undefined) {
  console.log(customer.property);
}

// Write like this:
console.log(customer?.property);
```

This operator can also be chained if the inner property's value is also optional.

```ts
console.log(customer?.property?.anotherProperty)
```

For array access, the quotation is a bit of counter intuitive at first.

```ts
console.log(customer?.[0]);
```

## [Structural Type System](https://www.typescriptlang.org/docs/handbook/typescript-in-5-minutes.html#structural-type-system)

In a structural type system, if two objects have the same shape, they are considered to be of the same type.

Therefore,  objects without declaring their type as well objects constructed by a `class` or `object` are all the same.

```ts
interface Point {
  x: number;
  y: number;
}
 
function logPoint(p: Point) {
  console.log(`${p.x}, ${p.y}`);
}
 
// logs "12, 26"
const point = { x: 12, y: 26 };
logPoint(point);
```

> As long as the shape of the object is a **subset** of the defined type, the, it's defined as the same shape.

### Rest Parameter and Spread Operator

`...arg` is the notation to tell the number of arguments is not fixed. The same notation used inside a function is a spread operator which is used to access the individual elements of an array (of similar type).

> The inferred type of the rest parameter has a type of `any[]` not `any`

```ts
// Rest Parameter
function multiply(n: number, ...m: number[]) {
  return m.map((x) => n * x);
}
// Spread Operator
const arr1 = [1, 2, 3];
const arr2 = [4, 5, 6];
// This works fine as push accepts flexible number of arguments.
arr1.push(...arr2);
```

A catchup here is that sometimes we try to use spread operator to pass in arguments to a function with **Fixed** number of arguments.

```ts
// Inferred type is number[] -- "an array with zero or more numbers",
const args = [8, 5];
// Error
const angle = Math.atan2(...args);

// Fix
const args = [8, 5] as const;
```

> This happens as `atan2` expects specifically 2 arguments, while `...args` infers flexible length, the meantime Ts doesn't regard array as immutable, even `const args` is defined as const. (args itself is const, but not its content.)






## Type Assertions

Type Assertion uses keyword `as` when Ts has no idea of the return value, but you do. This helps to enforce the type strictness. 

```ts
const myCanvas = document.getElementById("main_canvas") as HTMLCanvasElement;
// or

const myCanvas = <HTMLCanvasElement>document.getElementById("main_canvas");
```

It can also help to enforce literal type of a random object.

```ts
// I intend for req.method to always have the literal type "GET"”
const req = { url: "https://example.com", method: "GET" as "GET" };
const req = { url: "https://example.com", method: "GET" as const };
//OR
// I know req.method has the value "GET"“ (personal guarantee only, we can still change it before calling handleRequest)
handleRequest(req.url, req.method as "GET");
```

## [Assignment](https://www.typescriptlang.org/docs/handbook/2/narrowing.html#assignments)

Assignability is always checked against the **declared type.**. Therefore, 

```ts
let x = Math.random() < 0.5 ? 10 : "hello world!";
// x: string | number

x = 1;
// x: number
 
console.log(x);
           
x = "goodbye!";
// x can still be assigned to string
console.log(x);
```

## non-null assertion

Given the following shape `Square` if we're sure that when `kind === circle`, radius is not null, we can use `!` to tell the compiler that we know what we're doing.
```ts
interface Shape {
  kind: "circle" | "square";
  radius?: number;
  sideLength?: number;
}


function getArea(shape: Shape) {
  if (shape.kind === "circle") {
    return Math.PI * shape.radius! ** 2;
  }
}
```

> This is not a good approach, but something we can do. Since `radius === undefined` is certainly a grammar-correct code. Hence, this is error prone.


```ts
interface Circle {
  kind: "circle";
  radius: number;
}
 
interface Square {
  kind: "square";
  sideLength: number;
}
 
type Shape = Circle | Square;
```


## Functions

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

#### Function signatures

Function signatures describe how the function looks like. It's better to interpret is as **function declaration**. 

```ts
// function signatures
function makeDate(m: number, d: number, y: number): Date;
// implementation signatures.
function makeDate(mOrTimestamp: number, d?: number, y?: number): Date {
  if (d !== undefined && y !== undefined) {
    return new Date(y, mOrTimestamp, d);
  } else {
    return new Date(mOrTimestamp);
  }
}
```

However, there are also some other signatures that are **related** to functions (Not called function signatures, but related to functions). They may have the different notation in writing. 

There are several function signatures defined in TS. 

1. [Call Signatures](https://www.typescriptlang.org/docs/handbook/2/functions.html#call-signatures)
    > This defines the object (function is also an object) is callable and other **additional properties** (we can customize this). **It defines the function itself**. A function property without a name makes it a call signature.
    ```ts
    type Obj = {
      // arrow function named arrow
      arrow: (s: string) => void,
      // normal function named func
      func(s: string): void,
    }

    type Sig = {
      // colon without a name, this defines sig is callable.
      (s: string): void, 
      property: string,
    }
    // !! ERROR !!
    obj(); // let obj: Obj ....
    // great
    sig();
    obj.arrow("hello");
    obj.func("Hello");
    ```

    Try to understand the following code. ;)
    ```ts
    type Obj = {
        (): () => number,
    };

    let obj: Obj = () => {
        return function() {
            return 10;
        }
    }
    ```

2. [Construct Signatures](https://www.typescriptlang.org/docs/handbook/2/functions.html#construct-signatures)
    > Describes the function is a constructor. Below is an example, `new` keyword is used.

    ```ts
      // Define a class for 
    // representing books
    class Book {
        constructor(
            public title: string, public author: string) { }
    }
    
    // Define a construct signature for the Book class (a new before a call signature)
    type BookConstructor = {
      new (title: string, author: string): Book;
    }
    // or 
    type BookConstructor = 
        new (title: string, author: string) => Book;
        
    
    // Create a factory function based
    // on the construct signature
    function createBook(BookConstructor: BookConstructor,
        title: string, author: string) {
        return new BookConstructor(title, author);
    }
    
    // Use the factory function 
    // to create a book instance
    const bookInstance = createBook(Book,
        "The Story of My Experiments", "Mahatma Gandhi");
    
    // Log the book's properties
    console.log("Title:", bookInstance.title);
    console.log("Author:", bookInstance.author);
    ```

3. [**Overload Signatures**](https://www.typescriptlang.org/docs/handbook/2/functions.html#function-overloads)
    > Similar to overloads in CPP, however, **this is an extremely interesting one**.
    1. All *overload signatures* have the same function name (without doubts)
    2. We can define multiple *overload signatures*.
    3. We can only define a **single implementation signature** (WAAT!!!)
    4. The single implementation has to be compatible with all overload signatures. Compatible means the types of inputs as well as the outputs. (return type **may not** be inferred automatically)
    5. The implementation signature is **not visible** to outside.
    
    ```ts
    function fn(x: string): string;
    // Return type isn't right
    function fn(x: number): boolean;
    // !!ERROR!! This overload signature is compatible with its implementation signature.
    // function fn(x: string | boolean): string | boolean {
    //   return "oops";
    // }
    // function fn(x: string | boolean) {
    //   return "oops";
    // }

    // even boolean is not in the overload signature, but it's compatible!!
    function fn(x: string | number |boolean): string | boolean {
        return "oops";
    }

    console.log(fn("hello"))

    //!!! ERROR!!! The implementation signature is not visible. 
    // We can only call string | number
    console.log(fn(true))
    ```
    > Only use overloads when different signatures have different number of parameters or return type. Otherwise not really helpful besides adding difficulty to understand the code. **Always prefer parameters with union types instead of overloads when possible**


Check out more signatures on [More signatures](#more-signatures)

## [Generics](https://www.typescriptlang.org/docs/handbook/2/functions.html#generic-functions)


Use the `extends` keyword to add constraints

```ts
function longest<Type extends { length: number }>(a: Type, b: Type) {
  if (a.length >= b.length) {
    return a;
  } else {
    return b;
  }
}
 
// longerArray is of type 'number[]'
const longerArray = longest([1, 2], [1, 2, 3]);
// longerString is of type 'alice' | 'bob'
const longerString = longest("alice", "bob");
// Error! Numbers don't have a 'length' property
const notOK = longest(10, 100);
```

> The above code snippet expects the `Type` has `.length` property.


Generics are like templates in C++. They are used when we want to describe a **correspondence (in type)** between two values. 

```ts
function combine<Type>(arr1: Type[], arr2: Type[]): Type[] {
  return arr1.concat(arr2);
}

// Error
const arr = combine([1, 2, 3], ["hello"]);
```

The above code will complain error as Ts by default will infer the types of `arr1` and `arr2` are the same, which is not. To resolve this issue, we can combine **Union Type** and explicitly specify the type when calling the function.

```ts
const arr = combine<string | number>([1, 2, 3], ["hello"]);
```


> [Guidelines for writing Good Generic functions](https://www.typescriptlang.org/docs/handbook/2/functions.html#guidelines-for-writing-good-generic-functions)





## More signatures

Apart from [Function Signatures](#function-signatures), we also have array signatures, dictionary signatures.

```ts
interface StringArray {
  [index: number]: string;
}

interface NumberDictionary {
  [index: string]: number;
 
  length: number; // ok
  // !ERROR! Property 'name' of type 'string' is not assignable to 'string' index type 'number'.
  name: string;
}
```

> We can add more customized properties as well. e.g. `length`, However, in Ts as well as Js, we can access properties with 2 notations one is `obj.property` another one is `obj["property"]`. Therefore, the return type of `index` has to support the type of our customized properties. As for now, the return type is `number` while `obj['name]` returns a `string`.

```ts
interface NumberDictionary {
  // Here is the fix
  [index: string]: number | string;
 
  length: number; // ok
  name: string;
}
```


## [Excess Property Checks](https://www.typescriptlang.org/docs/handbook/2/objects.html#excess-property-checks)

Where and how an object is assigned a type can make a difference in the type system. One of the key examples of this is in excess property checking, which validates the object more thoroughly **when it is created and assigned to an object type during creation.**

> This happens when creating and assigning a type at the same time.

```ts
interface SquareConfig {
    color?: string;
    width?: number;
  }

  function createSquare(config: SquareConfig): { color: string; area: number } {
    return {
      color: config.color || "red",
      area: config.width ? config.width * config.width : 20,
    };
  }

// !!Error!!
let squareOptions: SquareConfig = { colour: "red", width: 100 };

// !!ERROR!!
let mySquare = createSquare({colour: "red", width: 100});

// Good
let squareOptions = { colour: "red", width: 100 };
```

> Check out more possible fixes from the title link.


## [Class](https://www.typescriptlang.org/docs/handbook/2/classes.html)

Classes, unlike C++ class, where we can have class declarations and class implementations, in Ts, only mean implementations. The role of declaration is taken by [Interfaces](#interface) and [type alias](#type-alias).

```ts
// A,B can be other classes or interfaces
class C implements A, B {}
```

A class needs to be constructed and fields (local variables) need to be initialized. However, if we know some fields will be initialized later (somehow). We can use `!`

```ts
class OKGreeter {
  // Not initialized, but no error
  name!: string;
}
```

Constructor overloads is similar to [function overloads](#function-signatures).

```ts
class Point {
  // Overloads
  constructor(x: number, y: string);
  constructor(s: string);
  constructor(xs: any, y?: any) {
    // TBD
  }
}
```

### Class Visibility

Both `protected` and `private` are soft, meaning in some cases, they're **not** really protected and private.

```ts
class Greeter {
    protected m: number = 10;
public greet() {
    console.log("Hello, " + this.getName());
}
protected getName() {
    return "hi";
}
}

class SpecialGreeter extends Greeter {
public howdy() {
    // OK to access protected member here
    console.log("Howdy, " + this.getName());
}
}
const g = new SpecialGreeter();
g.greet(); // OK
// ERROR
console.log(g.m);
// BUT THIS IS OK!!!!!
console.log(g['m']);
```

We can't access the `protected/private` members using dot notation, but we can still access them using bracket notation. More importantly, even using dot notation after compilation, the Js file doesn't enforce the privacy actually. **The visibility constraint only occurs when type checking**.

For a hard private, we can use [Js private field](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes/Private_properties).

```ts
class Dog {
    #barkAmount = 0;
    personality = "happy";
   
    constructor() {
        this.#barkAmount = 10;
    }

    getBarkAmount() {
        return this.#barkAmount;
    }
}

let d: Dog = new Dog();

console.log(d.getBarkAmount());
// error
console.log(d["barkAmount"]);
```


## [The Module Battle](https://www.youtube.com/watch?v=mK54Cn4ceac)

Before ES6 specification came out, surprisingly, module is not part of the feature in JS. Therefore, isolation is huge problem. JS code is also regarded as **script**. Therefore, to break this dilemma, `commonJS module` came out to rescue. 

Even though we don't have isolation between files, but we have isolation in functions (Absolutely, variables defined inside a function can't be seen by others). The idea is that for an anonymous function like the following one can be immediately called when the file is loaded by wrapping it by a double parenthesis `()()`. 

```js
(() => {
  var a = 'a';
  console.log("a", a);
})()
```

> This is the fundamental idea of commonJS module. **Therefore, *imports* of commonJS module are actually just functions**


commonJS module is embraced by Node.js and became fundamental to Node.js.

The syntax iconic import syntax is `let a = require('path')`, and export is `module.exports = {}`

Later, as JS evolves, module is finally officially supported by ES6. 

The import/export syntax are `import a from 'path'` and `exports = {}`

In summary, the difference between `import` and `require` are:

1. The future of module system is `import` as its official.
2. `require` is only recognizable by Node (the backend), the browser doesn't support it.
3. `require` is just a function, therefore it can be placed wherever in the code, even in condition clause.
4. `import` is static, therefore, it can't be placed inside any function and the position of it will be hoisted to the top of the file automatically.




## [d.ts](https://www.youtube.com/watch?v=s_CZeWuEZ_s&t=278s)

`d.ts` file is kinda like header file in CPP. It's designed to store all [type declarations](#type-declaration) and type declarations only. It's primary usage is designed to work with `JS` instead of `Ts.`

> [The "d.ts" file is used to provide typescript type information about an API **that's written in JavaScript**. ](https://stackoverflow.com/questions/21247278/about-d-ts-in-typescript)

As Js doesn't have type checking, in order to make a Js library compatible with a Ts project, type has to be explicitly stated. Therefore, role of `d.ts` file is to help merge **Js** library **into** Ts project. 

Under normally cases, only Js programmer needs to write one manually. 

However, d.ts can also be used in a different way, exactly like how header file in CPP. [More importantly, they're globally declared.](https://www.reddit.com/r/typescript/comments/126im5c/dts_files_on_a_ts_project/)

```ts
// d.ts
interface Person {
    name: string;
    age: number;
}

declare function greet(person: Person): string;
```

```ts
// without any import,
let p:Person = {
  name: "Hao",
  age: 10,
}
```

We can also treat it as a normal ts file by adding export keyword before the declarations. In such way, we have to import it explicitly.

```ts
// d.ts
export interface Person {
    name: string;
    age: number;
}

// ts
import {Person} from './path';
```