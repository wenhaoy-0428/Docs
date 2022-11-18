## Question
1. [What's the difference between `let`, `var` and `const`?](#difference-between-let-var-const-bare)
2. [Why variables can be used before declaration?](#hoisting)
3. [What is `this`?](#this)
4. [What's the back-tick](#string-template)
5. [What's the difference between null and undefined](https://www.geeksforgeeks.org/undefined-vs-null-in-javascript/)
6. [Is JS pass by value?](#pass-by-sharing)
7. [What's the difference between map and object](https://www.geeksforgeeks.org/map-vs-object-in-javascript/)
8. [How to define read only property?](https://stackoverflow.com/questions/7757337/defining-read-only-properties-in-javascript)
9. [How to get a computed property name](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/get#using_a_computed_property_name)
10. [What is prototype and prototype chain in JS](#prototype)
11. [What is class fields](#class-fields)
13. [Why does console.log(this) in node return an empty object?](https://stackoverflow.com/questions/42631698/why-does-console-logthis-in-node-return-an-empty-object)
14. [What are species in JS](#TODO)
15. [https://stackoverflow.com/questions/650764/how-does-proto-differ-from-constructor-prototype](#prototype-with-constructor)

//[TODO](https://stackoverflow.com/questions/597769/how-do-i-create-an-abstract-base-class-in-javascript)


## [Pass by sharing](https://stackoverflow.com/questions/518000/is-javascript-a-pass-by-reference-or-pass-by-value-language)

change the parameter itself, that won't affect the item that was fed into the parameter. But if you change the internals of the parameter, that will propagate back up.

## [All keywords](https://www.w3schools.com/js/js_reserved.asp)

#### Difference between `let`, `var`, `const`, `bare`

[->Ref1](https://www.geeksforgeeks.org/difference-between-var-and-let-in-javascript/)

[->Ref2](https://stackoverflow.com/questions/762011/what-is-the-difference-between-let-and-var)
- common
  - Both declares a variable.

- var 
  - variable is declared within the function scope
  - variable is hoisted when page loads, and set to undefined before initialization.
  - allows re-declaring.
  - allows globally defined.
  - [Hoist](#hoisting) with type 2 behavior
    ```js
    function f(input) {
        if(input == 1) {
            var a = 20;	// hoist to the function scope
        }
        return a; // accessible
    }
    console.log(f(2)); // undefined
    console.log(a); // ReferenceError as statement is outside function f
    ```
  - [closure problem of var](https://stackoverflow.com/questions/750486/javascript-closure-inside-loops-simple-practical-example)
- let
  - variable is declared within the **Block** scope (meaning `{}` within brackets)
  - access before initialization cause `ReferenceError`.
  - disallows re-declaring.
  - disallows globally defined.
  - disallows redeclare from var to let in the same scope.
  - [Hoist](#hoisting) with type 3 behavior
    ```js
    function f(input) {
    if(input == 1) {
        let a = 20;	// defined only within this if block.
    }
    return a; // ReferenceError.
    }
    console.log(f(1)); // undefined
    ```
- [bare](https://stackoverflow.com/questions/2485423/is-using-var-to-declare-variables-optional)
  - At runtime, when the initialization code is reached, the variable's scope will bubble up and become an automatic global variable. However, it's invalid in [strict mode](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Strict_mode)
    ```js
    function f(input) {
        if(input == 1) {
        	
        } else {
            a = 20;
        }
        return 10;
    }
    console.log(a); // ReferenceError as a is not defined.
    console.log(f(2)); // defines a, and it's scope will bubble up out of the function scope.
    console.log(a); // prints 20.
    ```
- [const](https://www.w3schools.com/js/js_const.asp)  
  - const variables have to be initialized when declared.
  - const variables can't be re-declared and reassigned, and changed. 
  - **BUT**, const array/object's **element** can be changed. (*array/object itself can't*)
    ```js
    // You can create a constant array:
    const cars = ["Saab", "Volvo", "BMW"];
    // You can change an element:
    cars[0] = "Toyota";
    // You can add an element:
    cars.push("Audi");
    cars = ["Toyota", "Volvo", "Audi"];  // ERROR
    ```

    ?> Therefore, it's a common practice to declare an object as `const`.
    
  - Others the same as `let`
    ```js
    var x = 2;     // Allowed
    const x = 2;   // Not allowed

    {
    let x = 2;     // Allowed
    const x = 2;   // Not allowed
    }

    {
    const x = 2;   // Allowed
    const x = 2;   // Not allowed
    }

    const x = 2;     // Allowed
    x = 2;           // Not allowed
    var x = 2;       // Not allowed
    let x = 2;       // Not allowed
    const x = 2;     // Not allowed

    {
    const x = 2;   // Allowed
    x = 2;         // Not allowed
    var x = 2;     // Not allowed
    let x = 2;     // Not allowed
    const x = 2;   // Not allowed
    }
    ```

  - Additional:
    * Declaring variables in a global scope, in Js means variables are accessible in the JS runtime environment; in HTML means the variables become a property of the root element, which is `window`. However, variables declared with `let` and `const` are not.
      ```js
      let lgVar = 10;
      // in HTML window.lgVar is invalid
      var vgVar = 10;
      // in HTML window.vgVar is valid
      ```
---

## Place to define Js

* `script` can be placed inside `head`, `body` and `external`
* **Placing scripts at the bottom of the <body> element improves the display speed, because script interpretation slows down the display.**
* `external` Js can benefit from Cached JavaScript files that speeds up page loads

---

## Output

* `document.write()` can write out messages.

!> Using `document.write()` after an HTML document is loaded, will delete all existing HTML: 

    ```html
    <!DOCTYPE html>
    <html>
    <body>

    <h1>My First Web Page</h1>
    <script>
        document.write(5 + 6);
    </script>
    <p>My first paragraph.</p>
    <!-- Prints out My First Web Page 11 My first paragraph.-->

    <button type="button" onclick="document.write(5 + 6)">Try it</button>
    <!-- Rewrites the whole page -->

    </body>
    </html>
  ```

---

## Nullish coalescing assignment operator

If the first value is undefined or null, the second value is assigned.

```js
let x = 10;
x ??= 5;
y ??= 5;
console.log(x); // print 10;
console.log(y); // print 5;
```


## Assignment operator in If

An assignment always returns the value of the assignment.

```js
if (x = 4)  // returns true.
if (x = 0) // returns false.

```
---

## Type Identification

- `typeof var` keyword to check `var`'s primitive type.
- `var` [instanceof](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/instanceof) `constructor` keyword test the `var` against a constructor function

```js
// constructor
function Car(make, model, year) {
  this.make = make;
  this.model = model;
  this.year = year;
}
const auto = new Car('Honda', 'Accord', 1998);

console.log(typeof auto);
// expected output: "object"
console.log(auto instanceof Car);
// expected output: true

console.log(auto instanceof Object);
// expected output: true
```

---

## String

- `replace` will is case sensitive, use RegExpr with `i` to indicate case insensitive.
  ```js
  let text = "Please visit Microsoft!";
  let newText = text.replace("MICROSOFT", "W3Schools"); // no match, return the original line.
  let newText = text.replace(/MICROSOFT/i, "W3Schools");
  ```
- `replace` only works for the first occurrence. Use RegExpr with `g` to indicate global match. `replaceAll` also comes to rescue.
  ```js
  let newText = text.replace(/Microsoft/g, "W3Schools");
  ```
- `padStart` is a good tool.
  ```js
  let text = "5";
  let padded = text.padStart(4,"x"); // xxxx5
  ```

---

#### [String Template](https://www.w3schools.com/js/js_string_templates.asp)

Template literals are enclosed by back-ticks(\`\`). They act the same as a normal string, but easier for string interpolation<sub>`Automatic replacing of expressions with real values is called string interpolation.`</sub>.
  ```js
  let firstName = "John";
  let lastName = "Doe";
  let text = `Welcome ${firstName}, ${lastName}!`;
  // the substitution can not only of variable but expression, and html.

  let header = "Templates Literals";
  let tags = ["template literals", "javascript", "es6"];

  let html = `<h2>${header}</h2><ul>`; 
  for (const x of tags) {
    html += `<li>${x}</li>`;
  }

  html += `</ul>`;
  ```

---

## Number

- All numbers are 64bit double precision. (no float, integer difference).
- Number without a decimal point has up to 15 digits accuracy.
  ```js
  let x = 999999999999999;   // x will be 999999999999999
  let y = 9999999999999999;  // y will be 10000000000000000
  ```
- Numeric operations work on numbers in string form. (except `+` operator)
  ```js
  console.info("100" / "10"); // 10 in number.
  ```
- `NaN` is a number meaning the number is illegal.
- Division by 0 (zero) also generates `Infinity`
- `.toString(base)` to output number in `base`.
  ```js
  let myNumber = 32;
  myNumber.toString(16);
  myNumber.toString(10);
  myNumber.toString(2);
  ```
- Biggest number is `9007199254740991`, bigger number will have security issue. `Number.isSafeInteger(n)` is a method to check if `n` is within bound.
  ```js
  9007199254740992 === 9007199254740993; // true
  ```
- `BigInt()` or `n` suffix allows the number to be bigger than 15 digits.
- `BigInt` can not do arithmetics with normal number nor have decimal point.

---
## Array

Array is a special object using number to index elements (object use propertyName), `typeof anArray` will return `object`. Since, it's an object, an array can have not only one type of elements. (function, string, array, object, number can store in a single array.)

```js
const person = ["John", "Doe", 46];
```

- It's better use `[]` to create array. and `new Array()` constructor is slower and behave unexpectedly.
  ```js
  // situation 1, following 2 produce the same result.
  const points1 = new Array(40, 100, 1, 5, 25, 10); 
  const points2 = [40, 100, 1, 5, 25, 10]; 
  //(do remember both are object, and comparison between objects are always false)
  points1==points2; //false
  // situation 2, same as above
  const points1 = new Array(40, 100);
  const points2 = [40, 100];
  // situation 3
  const points1 = new Array(3); // [,,,]
  const points2 = [3]; // [3]
  ```
  !> `new Array(n)` with only 1 input creates an array of `n` undefined elements, which is different from `[n]`

- Use `Array.isArray(var)` method to verify `var` is an Array or `var` [instanceof](#type-identification) `Array`. 

- Always use `push` to insert element, or the length as index. 

!> Index that exceeds the length will add `undefined` in between.

  ```js
  const fruits = ["Banana", "Orange", "Apple"];
  fruits[6] = "Lemon";
  // Banana Orange Apple undefined undefined undefined Lemon
  ```

- Use `pop` to delete last element, `shift` to delete first element, `push` to add at the end, `unshift` to add at the front. `splice` to add and remove at specific location. Check [more Array methods](https://www.w3schools.com/js/js_array_methods.asp)

!> using `delete` will cause undefined holes.
  ```js
  const fruits = ["Banana", "Orange", "Apple", "Mango"];
  delete fruits[0]; // undefined, orange, apple, mango
  ```

---

#### Sort an array

- [Sorting an array](https://www.w3schools.com/js/js_array_sort.asp) will start with changing all elements into a string then sort. 
  ```js
  const myarray = [ 100, 2,  3, 1, 4];
  myarray.sort();
  console.log(myarray); // 1, 100, 2, 3, 4
  ```

- Use compare function to solve sorting. The following rule applies:
  1. A compare function returns negative, zero, and positive
  2. If the result is negative, a is sorted before b.
  3. If the result is positive, b is sorted before a.
  4. If the result is 0, no changes are done with the sort order of the two values.

  ```js
  const points = [40, 100, 1, 5, 25, 10];
  points.sort(function(a, b){return b - a});
  ```  

- There's no built in `MaxElement` nor `MinElement` functions, Use [Math.max](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/max) to address.

  ```js
  Math.max.apply(null, [1,2,3]); // use null cause max expect 2 arguments.  
  ```

---

#### Useful array methods

- The `reduce()` method runs a function on each array element to produce (reduce it to) a single value.
  ```js
  const numbers = [45, 4, 9, 16, 25];
  let sum = numbers.reduce(myFunction);
  // The total (the initial value / previously returned value)
  // The item value
  // The item index
  // The array itself
  function myFunction(total, value, index, array) { // unused parameter can be omitted.
    return total + value;
  }
  ```
- The `every()` method checks if all array values pass a test.
  ```js
  const numbers = [45, 4, 9, 16, 25];
  let allOver18 = numbers.every(myFunction); // false

  function myFunction(value, index, array) {
    return value > 18;
  }
  ```

- The `find()` method returns the value of the first array element that passes a test function. The `findIndex()` method returns the index.
  ```js
  const numbers = [4, 9, 16, 25, 29];
  let first = numbers.find(myFunction);

  function myFunction(value, index, array) {
    return value > 18;
  }
  ```
- The `Array.from()` method returns an Array object from any object with a **length property** or any iterable object.
  ```js
  Array.from("ABCDEFG");
  ```
- The `entries()` method returns an Array Iterator object with key/value pairs.
- The `includes()` method checks if an element exists. 
  ```js
  const fruits = ["Banana", "Orange", "Apple", "Mango"];
  fruits.includes("Mango"); // is true
  ```
  > For `NaN`, `includes` return true, while indexOf doesn't
    ```js
    const myarray = [ 100, 2,  3, 1, 4, NaN];

    console.log(myarray.includes(NaN)); // true
    console.log(myarray.indexOf(NaN)); // -1
    ```

---

## Loop

* The first expression in a loop can initialize many variables. (only declaration works)

  ```js
  for (let i = 0, len = cars.length, text = ""; i < len; i++) { 
    text += cars[i] + "<br>";
  }
  ```

* [`var` and `let`](#difference-between-let-var-const-bare)

  ```js
  var i = 5;
  for (var i = 0; i < 10; i++) {
    // some code
  }
  // Here i is 10
  ```

  ```js
  let i = 5;
  for (var i = 0; i < 10; i++) {
    // some code
  }
  // Error
  ```

  ```js
  let i = 5;
  for (let i = 0; i < 10; i++) {
    // some code
    // this i is isolated from the outside.
  }
  // Here i is 5
  ```

!> **Do not** use `for in` over an Array if the index order is important. The index order is implementation-dependent, and array values may not be accessed in the order you expect.It is better to use a `for` loop, a `for of` loop, or `Array.forEach()` when the order is important.

* The `for..of` loop only supports iterable objects like arrays, not objects. Check here for [Enumerability and ownership of properties](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Enumerability_and_ownership_of_properties)

  ```js
  const cars = ["BMW", "Volvo", "Mini"];

  let text = "";
  // x can be declared as let, var, or const. for const, changing x in loop cause error.
  for (const x of cars) {
    x = 10; // cause error
    text += x;
  }
  ```

---
## Labels

* The `continue` statement (with or without a label reference) can only be used to skip one loop iteration.

* The break statement, without a label reference, can only be used to jump out of a loop or a switch.

* With a label reference, the break statement can be used to jump out of any code block
  ```js
  hello: {
      document.write("hello");
  }

  list: {
      text += "1" + "<br>"; 
      text += "2" + "<br>"; 
      break list;
      break hello; // error: A 'break' statement can only jump to a label of an enclosing statement.
      text += "3" + "<br>"; 
      text += "4" + "<br>"; 
  }
  ```

---

## [Pseudo URL and void operator](https://www.freecodecamp.org/news/javascript-void-keyword-explained/)

* Avoid the use of this, it plays a link as a button.
  ```js
  <a href="javascript:void(document.body.style.backgroundColor='red');">
  ```
* `javascript:` is the pseudo URL, tells the anchor that the url is not a path but a js code to run.
* `void` operator executes the expression, but returns nothing.

---
## [RegExp](https://www.w3schools.com/jsref/jsref_obj_regexp.asp)

Regular Expression is has a syntax `/pattern/modifier(s)` where `pattern` has its own rule, and `modifiers` include the following options:
  - `g` for global search
  - `i` for case-insensitive search
  - `m` for multi-line search

> Use `regExp.exec(text)` to match a string and return the match portion, `regExp.test(text)` to match a string a return a bool.

---

## [Hoisting](https://developer.mozilla.org/en-US/docs/Glossary/Hoisting)

- The parser of js engine will read through the entire file before running it, and any variable declarations will be executed as if they were at the top of the containing scope. Note: only declarations are hoisted, not the definition. [->Ref](https://stackoverflow.com/questions/20220862/in-javascript-can-i-use-a-variable-before-it-is-declared), [->Ref](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/var#var_hoisting)

  1. Example
    ```js
    console.log(value_); // This will print out undefined, but it will work.
    var value_ = "HelloWorld"; // declaration will be hoisted but definition.
    console.log(value_); // This will print out HelloWorld as expected.
    // --- a different example below.
    console.log(value_); // This will throw an error.
    // without declaration.
    ```
  2. Example
    ```js
    function test() {
        x = 5; // hoisted not automatic global
        console.log(x);
        var x;
    }
    console.log(x); // error
    ```

- In [the comparison among let, var, const](#difference-between-let-var-const-bare), its mentioned that, for `let` and `const`, using before declaration causes error, which infers that `let` and `const` are not hoisted, in some sort? The [truth](https://developer.mozilla.org/en-US/docs/Glossary/Hoisting) is that they are hoisted, but also put into a temporary dead zone before it's declaration line.
  ```js
  const x = 1;
  {
      console.log(x); // Reference error
      const x = 2; // if const is not hoisted, console.log(x) should've read 1.
  }
  ```

---

## [new](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/new)

The new operator lets developers create an instance of a user-defined object type or of one of the built-in object types that has a constructor function.

Since `function` is an instance of `Object`, it's also valid to `new func()` to call a function. And [new.target](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/new.target) will be available in `func()` that refers to the function itself.

Check the above reference for what procedures are executed when `new`ing an instance.

Only object with [prototype](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/prototype) property can be `new`ed, but the verse is not right.

---

## [Object](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object)

* Nearly all objects in JavaScript are instances of `Object`; a typical object inherits properties (including methods) from `Object.prototype`, although these properties may be overridden. The only objects that don't inherit from `Object.prototype` are those with [null prototype](#null-prototype-objects), or descended from other null prototype objects. Learn more out [prototype here](#prototype).

* For derived objects from `Object.prototype`, they auto inherits `valueOf()` and `toString()` functions, even though you should expect the objects to implement their own overridden versions. But these two functions calls are implicitly called through type conversion, and you don't have to override.

> It's a common practice to `declare` an object as [const](#difference-between-let-var-const-bare), and a bad practice to declare primitive types (Number..) as `Object`.


#### Scope of Object Literal
* Object doesn't have a [scope](https://developer.mozilla.org/en-US/docs/Glossary/Scope). [All the properties of an object are associated with the object itself but the scope.](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Working_with_Objects#objects_and_properties). Therefore, object doesn't have its own context.

> To be more precise, it's that object literal (`const a = {...}`) doesn't have a scope, constructor (indeed a function) does have a scope.

* An object's property can be a function.
  ```js
  const person = {
    firstName: "John",
    lastName : "Doe",
    id       : 5566,
    fullName : function() {
      return this.firstName + " " + this.lastName;
    }
  };
  person.fullName(); // calls the function.
  person.fullName; // prints out the function declaration.
  ```
* Avoid String, Number, and Boolean objects. They complicate your code and slow down execution speed.
  ```js
  x = new String();        // Declares x as a String object
  y = new Number();        // Declares y as a Number object
  z = new Boolean();       // Declares z as a Boolean object
  ```

* Comparing two JavaScript objects always returns false.
  ```js
  let x = new String("John");
  let y = new String("John");
  let z = "John";
  x==z; // true
  x==y; // false
  x===y; // false
  ```

#### Add properties to an object constructor

* To add a new property to an object, either add the property into the constructor function or use [prototype](#prototype) of the constructor. Changes to the `constructor.prototype` are seen by **all**<sub> Not only the newly created object will have the addon property but the existing ones</sub> objects through prototype chaining, unless the properties and methods subject to those changes are overridden further along the prototype chain. 
  ```js
  function Car(name) {
    this.name_ = name;
  }
  let myCar1 = new Car("Audi");
  Car.engine = "V8"; // defines a static property for Car
  console.log(myCar1.engine); // undefined
  
  Car.prototype.engine = "V8"; 
  console.log(myCar1.engine); // V8

  let myCar2 = new Car("BMW"); 
  console.log(myCar2.engine); // V8
  ```

* For adding property to an object created by calling a constructor doesn't change the property of the other created objects.
  ```js
  function Car(name) {
    this.name_ = name;
  }
  
  let myCar1 = new Car("Audi");
  console.log(myCar1.engine); // undefined
  myCar1.engine = "v8"; 
  console.log(myCar1.engine); // v8

  let myCar2 = new Car("BMW");
  console.log(myCar2.engine); // undefined

  // another approach doesn't work either.
  let myCar1 = new Car("Audi");
  console.log(myCar1.engine); // undefined
  Car.engine = "v8";
  console.log(myCar1.engine); // undefined

  let myCar2 = new Car("BMW");
  console.log(myCar2.engine); // undefined  
  ```


> `Car.engine` doesn't add new property to an object, instead it defines a [static property](#static-methods-and-properties) for class `Car`.

#### Null prototype objects

Objects that have `null prototype` doesn't inherit functions form `Object.prototype` meaning, `toString`, `valueOf`, etc. property methods are all unavailable to use.

To objects null prototype objects, the follow ways can be used to achieve
  1. call `static` function `Object.create(null)`
    ```js
    const obj = Object.create(null);
    ```
  2. set `__proto__` property to `null` in an object.
    ```js
    const obj2 = { __proto__: null };
    ```
  3. Set `prototype` property in constructor to `Object.create(null)`. Setting to null won't work.
    ```js
    function Obj() {
        name: "HAO"
    }
    // Obj.prototype = null; This won't work.
    Obj.prototype = Object.create(null);

    console.log(new Obj().toString) // undefined.
    ```
    > [objects created by `new` will always inherit from `Object.prototype`](https://stackoverflow.com/questions/18198178/null-prototype-object-prototype-and-object-create)

The benefits of using `null prototype` seem unobvious, util you find yourself suffers from the expected result of `Object.prototype`, and prototype pollution attacks. 
```js
const ages = { alice: 18, bob: 27 };

function hasPerson(name) {
  return name in ages;
}

function getAge(name) {
  return ages[name];
}

console.log(hasPerson("hasOwnProperty")); // true
console.log(getAge("toString")); // Function toString
```
> `ages` is an object that automatically inherits from `Object.prototype`, meaning it inherits the properties of `hasOwnProperty()` and `toString()`. Therefore, `hasOwnProperty in ages` will result in true, and `ages["toString"]` a.k.a `ages.toString` result in a function.

To add the same `toString` as `Object.prototype` simply do `nullProtoObj.toString = Object.prototype.toString;` or [Add it to the  constructor](#add-properties-to-an-object-constructor). Therefore, `null prototype` objects remove this hazard without introducing too much complexity.

```js
// pollution attacks
const user = {};
// A malicious script:
Object.prototype.authenticated = true;
// Unexpectedly allowing unauthenticated user to pass through
if (user.authenticated) {
  // access confidential data
}
```

---

## [This](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/this)

`this` is not a variable. It is a **keyword**. You cannot change the value of this.


#### This substitution

//TODO:

#### This in normal function

**The value of `this` is not the object that has the function as an own property, but the object that is used to call the function.** 

For a typical function, the value of this is the object that the function is accessed on. In other words, if the function call is in the form `obj.f()`, then this refers to `obj`. (Think about this as a hidden parameter of a function — just like the parameters declared in the function definition)

```html
<!DOCTYPE html>
<html>
<body>
<h1>The JavaScript <i>this</i> Keyword</h1>
<!-- this refers to Button -->
<button onclick="this.style.display='none'">Click to Remove Me!</button>
<button onclick="myfunc'">Click to Remove Me!</button>
<script>
function myfunc() {
  // this refers to shit.
	this.style.display='none
}
</script>
</body>
</html>
```

- **Callback**

When a function is passed as a callback, the value of this depends on how the callback is called, which is determined by the implementor of the API

- **The rule of thumb**: `this` always refers to `who` calls the function when the function is a normal function.
  ```js
  const obj = {
    i: 10,
    b: () => console.log(this.i, this),
    c() {
      console.log(this.i, this);
    },
  };
  obj.c() // this refers to obj
  var tempFunc = obj.c;
  tempFunc(); // this refers to global. 
  ```
- Methods like call(), apply(), and bind()[<sub>see difference</sub>](https://stackoverflow.com/questions/15455009/javascript-call-apply-vs-bind) can refer `this` to any object. 

#### This in arrow function

With arrow functions the `this` keyword always represents the object that `defined` the arrow function.

Arrow function doesn't have its own `this` binding, meaning, it will not change its `this` based on context changes.

Arrow functions create a `closure` over the **`this` value of its `surrounding scope`(parent scope)**, which means arrow functions behave as if they are "auto-bound" — no matter how it's invoked, **this is set to what it was when the function was created**. 

For example, `func1` is created in a global env, thus its `surrounding scope` is `global`, and `this` refers to global.
```js
const func1 = () => {
  console.log(this);
};
```

In this example, `autoBoundMethod` is an arrow function, and its `surrounding scope` is `C` hence, at creation, `this` refers to `C`. Because, arrow function doesn't have its own `this` binding based on context changes, changing the `calling context` doesn't change `this`. 
```js
class C {
  a = 1;
  autoBoundMethod = () => {
    console.log(this.a);
  }
}

const c = new C();
c.autoBoundMethod(); // 1
const { autoBoundMethod } = c;
autoBoundMethod(); // 1
// If it were a normal method, it should be undefined in this case
```

In this example, surprisingly `this` in arrow function `b` doesn't refer to `obj` as [Object](#object) doesn't have its own scope and context. Therefore, there is no `this` for a object, thus `this` is refers to global or window. 
```js
const obj = {
  i: 10,
  b: () => console.log(this.i, this),
  d: this,
  c() {
    console.log(this.i, this);
  },
};
obj.b(); // undefined, {}
console.log(this) // {}
obj.c(); // 10, obj
var temp = obj.c;
temp(); // window or global
```

It's mentioned above that object does't have a scope, but function does. [class](#class) is a special function, so class has a scope.  In this example, when `myMethod` is called, because it's a normal function, then its `this` binding makes `this` refers to `myObject` in `myMethod`'s function scope. In the function, arrow function `myArrowFunction` is created, since arrow function doesn't have its own `this` binding, it automatically searches for the `this` value in its `surrounding scope` which is `myMethod`'s function scope. Thus, `this` is bind to `myObject`. 

```js
const myObject = {
    myArrowFunction: null,
    myMethod: function () {
      this.myArrowFunction = () => { console.log(this) };
    }
  };
myObject.myArrowFunction(); // #1 error
myObject.myMethod(); 
myObject.myArrowFunction(); // myObject
```

?> REMEMBER `this` in arrow function refers to the `this` value in its surrounding scope when **CREATED** **, not just when you saw it's written in code.

In this example, we use explicit binding by calling `apply` on `myMethod`. Thus `this` in `myMethod`'s function scope refers to `obj2`, **NOT** `myObject`. Therefore, `myObject` didn't initialize its own `myArrowFunction`, and on the other hand, `obj2` declared its `myArrowFunction`. 
```js
const obj2 = {

}
myObject.myMethod.apply(obj2);
myObject.myMethod(); // error.
obj2.myArrowFunction(); // obj2
```

#### This in constructor

It's mentioned that object doesn't have its scope, but function does have a scope, in which object constructor is also included. However, `this` in the constructor doesn't refer to the function, but it refers to the object that's being created.
```js
function Car() {
    this.arrow = () => {
        return this;
    }
}
let myCar = new Car();
console.log(myCar.arrow()); // this refers to myCar
console.log(myCar.arrow() === myCar); // true
```

#### [This in class](#https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes#binding_this_with_prototype_and_static_methods)




> [Arrow function is extremely useful for asynchronous function calls](https://www.codementor.io/@dariogarciamoya/understanding-this-in-javascript-with-arrow-functions-gcpjwfyuc) as it remembers its context at creating and can't be changed no matter what.
  ```js
  myObject = {
    myMethod: function () {
      helperObject.doSomethingAsync('superCool', () => {
        console.log(this); // this === myObject
      });
    },
  };
  ```
  If you pull the anonymous arrow function into a named function outside for reusing. It changes its surrounding scope thus `this` it refers to. 
  ```js
  // solve
  const reusabledCallback = function () {
    console.log(this);
  };

  myObject = {
    myMethod: function () {
      helperObject.doSomethingAsync('superCool', reusabledCallback.bind(myObject));
    },
  };
  ```

- Refs
  - [Beginner](https://www.w3schools.com/js/js_arrow_function.asp)
  - [Intermediate](https://www.codementor.io/@dariogarciamoya/understanding-this-in-javascript-with-arrow-functions-gcpjwfyuc)
  - [Reference](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/Arrow_functions)



## Function

#### [All functions](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/Method_definitions)

#### [Generators](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/function*)

#### [getter/setter](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/get)

`getter` and `setter` can have the same name as the property. However, the property will be accessed is it's public.

getter and setter gains cleaner syntax and can play as they sound in C++ language.


## [prototype](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Inheritance_and_the_prototype_chain)

While [classes](#class) abstract most of the prototypical mechanism away, understanding how prototypes work under the hood is still useful.

Each object has a property which holds a link to another object called its **prototype**. It's a chain up to `null` as the final link. 

**Terminology Confusion**
-  the notation `someObject.[[Prototype]]` is used to designate the prototype of `someObject`, `someObject` doesn't have property named `prototype`.
- `obj.__proto__` is not a standard way to access the `[[Prototype]]` property, even though widely supported. 
- `Object.getPrototypeOf()` and `Object.setPrototypeOf()` are standard wa to access instead.
- `{__proto__: xxx, ...}` is a standard way to defined `prototype` property in an object literal.
- **functions do have a property named `prototype`.** to construct instances, but they also have their own `[[Prototype]]`.

> function in JavaScript will always have a default prototype property — with one exception: an arrow function doesn't have a default prototype property:

When trying to access a property of an object, the property will not only be sought on the object but on the prototype of the object, the prototype of the prototype, and so on until either a property with a matching name is found or the end of the prototype chain is reached.

```js
const o = {
  a: 1,
  b: 2,
  // __proto__ sets the [[Prototype]]. It's specified here as another object literal.
  __proto__: {
    b: 3,
    c: 4,
    __proto__: {
      d: 5,
    },
  },
};
// { a: 1, b: 2 } ---> { b: 3, c: 4 } ---> { d: 5 } ---> Object.prototype ---> null
console.log(o.d); // 5
```

> Functions are also acted as properties. When an [inherited function](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Inheritance_and_the_prototype_chain#inheriting_methods) is executed, the value of `this` points to the inheriting object, not to the `prototype object` where the function is an own property.
#### [Different ways to mutate prototype chain](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Inheritance_and_the_prototype_chain#different_ways_of_creating_and_mutating_prototype_chains)

#### Prototype with Constructor 

**`constructor.prototype` and `constructor.[[Prototype]]` are two different things and the former includes the latter.**

Check [new](#new) for the procedure, you'll find:
  1. Creates a blank, plain JavaScript object. For convenience, let's call it newInstance.
  2. **Points**(not copy this is extremely important [check here](#why-adding-properties-to-constructorprototype-is-ok-but-reassignment-if-bad)]) newInstance's `[[Prototype]]` to the constructor function's `prototype` property, if the `prototype` is an Object. Otherwise, newInstance stays as a plain object with `Object.prototype` as its `[[Prototype]]`.

Hence, we know that object instances created by constructor will have `[[Prototype]]` set to the `prototype` of the constructor, the `constructor.[[Prototype]]` is also included actually in `prototype` property to link up the prototype chain. See [map here](https://stackoverflow.com/questions/650764/how-does-proto-differ-from-constructor-prototype) for a better understanding. And [Building longer inheritance chains](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Inheritance_and_the_prototype_chain#building_longer_inheritance_chains) for reference.

Therefore, [when adding properties](#add-properties-to-an-object-constructor), we need to add to the `prototype` of the constructor to propagate the adding to all instances. Since all instances, when accessing properties, will follow up the chain.
  ```js
  function Car(name) {
    this.name_ = name;
  }
  let myCar1 = new Car("Audi");
  Car.engine = "V8"; // defines a property for Car itself, since function is also an object.
  console.log(myCar1.engine); // undefined
  
  Car.prototype.engine = "V8"; 
  console.log(myCar1.engine); // V8

  let myCar2 = new Car("BMW"); 
  console.log(myCar2.engine); // V8
  console.log(Object.getPrototypeOf(new Car()) === Car.prototype); // true
  // myCar2 : {name: "BMW", __proto__: Car.prototype} -> Car.prototype: {engine: "V8", __proto__: Object.prototype},  Object.prototype : {__proto__: null}
  ```

The constructor's `prototype` property by default has one own property: `constructor`: `constructor.prototype.constructor`, which refers to the constructor function itself. Therefore, all instances will also have a property named `constructor` to check its constructor. Check question [How does __proto__ differ from constructor.prototype?](https://stackoverflow.com/questions/650764/how-does-proto-differ-from-constructor-prototype) to wrap your head around.

```js
class Box {
  constructor(value) {
    this.value = value;
  }

  // Methods are created on Box.prototype
  getValue() {
    return this.value;
  }
}
```
Classes are syntax sugar over constructor functions, which means you can still manipulate `Box.prototype` to change the behavior of all instances.

#### Why adding properties to `constructor.prototype` is OK, but reassignment if bad

Because, all instances' `[[Prototype]]` are **referenced** or **pointed** but not copied to `constructor.prototype`, after we add properties to `constructor.prototype`, new changes can take effect. However, `constructor.prototype` is an object and it's there, after the reassignment, instances created before the reassignment will still have their `[[Prototype]]` referenced to the old `constructor.prototype` object. BAD THINGS will happen, as you'll see the example below that `myCar1` doesn't have its own `engine` property, and it has a constructor with a different prototype than its `[[Prototype]]` and the original `constructor.prototype` is still there (because `engine` is still reachable) but untractable any more.

```js
function Car(name) {
    this.name_ = name;
}
Car.prototype.engine = "V8";
let myCar1 = new Car("Audi");
console.log(myCar1.engine);  // V8
console.log(myCar1.__proto__); // {engine: 'V8'}
Car.prototype = {};
console.log(myCar1.engine); // STILL V8 !!!!!!!!!
console.log(myCar1.hasOwnProperty("engine")); // false
console.log(myCar1.constructor.prototype === myCar1.__proto__); // things may break 
let myCar2 = new Car("BMW"); 
console.log(myCar2.engine); // undefined. Inconsistency !!!!!!
```

Use `Object.setPrototypeOf` instead. Because `constructor.prototype` and `constructor.[[Prototype]]` are two different things and the former includes the latter which is mentioned at the beginning of this section, the following code mutates `constructor.[[Prototype]]` only but not reassigning, hence won't have the above problems.
```js
Object.setPrototypeOf(Car.prototype, {});
```
> Refer to [Building longer inheritance chains](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Inheritance_and_the_prototype_chain#building_longer_inheritance_chains) for more details


#### Old shit
All JavaScript objects **inherit** properties and methods from a prototype:
  - Date objects inherit from Date.prototype
  - Array objects inherit from Array.prototype


---

## Class

Class is a **template** to create objects. **It's a special function**. To create a template object, one way is to use `function declaration`, the other one is to use `class declaration`.

> JavaScript classes, introduced in ECMAScript 2015, are primarily syntactical sugar over JavaScript's existing [prototype-based](#prototype-with-constructor) inheritance. classes are designed to be an abstraction over the underlying prototype mechanism.

An important difference between function declarations and class declarations is that while functions can be called in code that appears before they are defined (**functions are [hoisted](#hoisting)**), classes must be defined before they can be constructed. Code like the following will throw a ReferenceError:

```js
let obj = new myClass();
console.log(obj.height); // print 10
function myClass() {
    this.height = 10;
}

const p = new Rectangle(); // ReferenceError

class Rectangle {} 
```


?> Refers to [This in class](#this-in-class) to see how `this` behaves.


#### [Class constructor](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes/constructor)

constructor is the first function to call when creating an object instance, and like C language, You will get a default one if you don't provide one yourself. But the default one will still invoke the base class's constructor but won't pass in [spreading arguments](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes/constructor). But unlike C language, there can only be **1** constructor, and there's no constructor overloading, only default values. 

> Computed properties cannot become constructors.

If you decide to have a self-implemented constructor, `super()` must be called in the constructor if the class is a derived one. Passing arguments to `super()` doesn't matter, you can leave empty, but you have to call `super`

```js
class A {
    constructor(name) {
        this.name = name;
        console.log("A");
    }
}
class B extends A {
    constructor() {
        // super("Tom"); // Error
        super() // fine
        console.log("B");
    }
}
let obj = new B(); // prints A, B
console.log(obj.name); // prints undefined.
```

[new](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/new) procedure in constructor:
1. (If it's a derived class) The constructor body before the super() call is evaluated. This part should not access this because it's not yet initialized.
2. (If it's a derived class) The super() call is evaluated, which initializes the parent class through the same process.
3. The current class's fields are initialized.
4. The constructor body after the super() call (or the entire body, if it's a base class) is evaluated.

**Note that methods (including getters and setters) and the prototype chain are already initialized on this before the constructor is executed**, so you can even access methods of the subclass from the constructor of the superclass. However, if those methods use `this`, the `this` will not have been fully initialized yet. Check Example in the reference.


Both function constructor and class's constructor can have return value, but are ignored if the return value is not an object.
```js

function myClass() {
    return 1; // 1
    return {name: "hello"}; // 2
}
console.log(new myClass());
// 1: myClass {}; 2: {name: "hello"}
```

!> When the base class's constructor returns a value, (any value even not an object), derived class must return an object or `undefined` or error will be thrown.

When the class returns an **object**(not value, value will still be ignored), `this` in the derived class will refer to the object returned from base.

```js
class Base {
    constructor() {
        // this.name = "abc";
        return {name: "hello"};
    }
}

class Derived extends Base {
    constructor() {
        super();
        console.log(this);
    }
}

let obj =new Derived(); // prints {name: "hello"}
console.log(obj.name); // prints "hello"
```

```js
class Base {
    constructor() {
      this.name = "abc";
    }
}

class Derived extends Base {
    constructor() {
        super();
        console.log(this);
    }
}

let obj =new Derived(); // prints Derived {name: "abc"}
console.log(obj.name); // prints "abc"
```


#### Class Fields

In the following example, `height` and `width` are called `filed declarations`, and themselves are called `instance properties` which mush be defined inside class methods (normally the constructor). Also, `filed declarations` can be **omitted**. 

```js
class Rectangle {
  height = 0;
  width;
  constructor(height, width) {
    this.height = height;
    this.width = width;
  }
}
```

> No `let`, `const`, `var` specifiers needed.

* Public filed declaration, by default is the shown above. 
* Private filed declaration can be defined with `#` sign in front. Thus filed can not be omitted.
  ```js
  class Rectangle {
    #height = 0;
    #width;
    constructor(height, width) {
      this.#height = height;
      this.#width = width;
    }
  }
  ```

##### Private filed

Private members can be emulated with [WeakMap](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WeakMap#emulating_private_members) or [Closure](#TODO)

If you access a private property from an object that doesn't have the property, a `TypeError` is thrown, instead of returning undefined as normal properties do. Therefore, use `in` or `try...catch` to check before using it. **Normal print of the object won't show the private properties**.

Private properties are not part of the prototypical inheritance model since they can only be accessed within the current class's body and **aren't inherited** by subclasses.

**static private fields**: are only accessible on the class itself or on the `this` context of **static** methods, but not on the `this` context of **instance**(normal public) methods.
  ```js
  class ClassWithPrivateStaticField {
    static #PRIVATE_STATIC_FIELD;

    static publicStaticMethod() {
      ClassWithPrivateStaticField.#PRIVATE_STATIC_FIELD = 42;
      return ClassWithPrivateStaticField.#PRIVATE_STATIC_FIELD;
    }

    publicInstanceMethod() {
      ClassWithPrivateStaticField.#PRIVATE_STATIC_FIELD = 42;
      return ClassWithPrivateStaticField.#PRIVATE_STATIC_FIELD;
    }
  }
  console.log(ClassWithPrivateStaticField.#PRIVATE_STATIC_FIELD); // ERROR
  console.log(ClassWithPrivateStaticField.publicStaticMethod()); // 42
  console.log(new ClassWithPrivateStaticField().publicInstanceMethod()); // 42
  ```
  * Restriction: Only the class which defines the private static field can access the field. 
    ```js
    class BaseClassWithPrivateStaticField {
      static #PRIVATE_STATIC_FIELD;

      static basePublicStaticMethod() {
        return this.#PRIVATE_STATIC_FIELD;
      }
    }
    class SubClass extends BaseClassWithPrivateStaticField {}
    SubClass.basePublicStaticMethod(); // TypeError: Cannot read private member #PRIVATE_STATIC_FIELD from an object whose class did not declare it
    ```
    Even with `super`, there's still a type error, as [super methods are not called with the super class as this](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/super#calling_methods_from_super)
    ```js
    class BaseClassWithPrivateStaticField {
      static #PRIVATE_STATIC_FIELD;

      static basePublicStaticMethod() {
        // When invoked through super, `this` still refers to Subclass
        return this.#PRIVATE_STATIC_FIELD;
      }
    }

    class SubClass extends BaseClassWithPrivateStaticField {
      static callSuperBaseMethod() {
        return super.basePublicStaticMethod();
      }
    }

    SubClass.callSuperBaseMethod();
    ```

**Private Constructor** is not supported natively, but can be accomplished by static tag. Refer [private constructor](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes/Private_class_fields#simulating_private_constructors) for more details.

  

#### [Static methods and properties](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes#static_methods_and_properties)

They can be called or used directly without instantiating: `ClassName.staticMethod()`. **AND** They can't be used with an instance: `obj.staticMethod() === undefined`.

For function declaration, static properties can only set in the following way.
```js
function Animal() { }
// static
Animal.eat = function () {
  return this;
}
```

Or use [Object.assign](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object/assign) to copy from another object

```js
const myObj = {
    eat() {
        console.log("HELLOWORLD");
    }
}
Object.assign(Animal, myObj);
```

#### [Class inheritance](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes/extends)


`extends` key word specifies inheritance of the class. 

Only class with [prototype](#prototype) is an object can be inherited from.
```js
function ParentClass() {}
ParentClass.prototype = 3;

class ChildClass extends ParentClass {}
// Uncaught TypeError: Class extends value does not have valid prototype property 3
```


>In the constructor of the derived class, [super()](#super-keyword) must be used to call parent's constructor before using derived class `this`. Check [new procedure in constructor](#class-constructor) for more details. The [constructor can be omitted](#class-constructor) to get a default one. 

[A derived class can be `extended` from: ](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes#sub_classing_with_extends)
  - Another class
  - Another function declared class
  - A object 

!> Multiple inheritance is invalid, a class can only have 1 single super class. Therefore, in order to have a class with properties from multiple class, [Mixin](#mixin) is used.


#### Mixin 

The definition of mixins can be stated as mixins is a class that contains methods that can be used by other classes without inheriting from that class. 

A simple mixin can be accomplished by copying properties of an Object without using inheritance. [Object.assign()](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object/assign) plays an important role here.

```js
// mixin
let sayWelcomeMixin = {
    sayWelcome() {
      console.log(`Welcome ${this.userName}`);
    },
    sayBye() {
      console.log(`Bye ${this.userName}`);
    }
  };
  class User {
    constructor(userName) {
      this.usrName = userName;
    }
  }
// copy the methods
Object.assign(User.prototype, sayWelcomeMixin);
```

> The above example copies properties of `sayWelcomeMixin` to `User.prototype` instead of `User`, check [prototype](#prototype) for more details.

The [second mixin pattern](https://www.youtube.com/watch?v=QWVuubrms18) is to use class inheritance.

```js
const calculatorMixin = (Base) => class extends Base {
  calc() { } // A property method
};

const randomizerMixin = (Base) => class extends Base { // An arrow function that creates a class that extends the input class.
  randomize() { } // A property method
};
// Usage
class Foo { }
class Bar extends calculatorMixin(randomizerMixin(Foo)) { } // So Bar extends a mixin of Foo
```


#### super keyword 

`super` keyword is used to represent methods of the super class (parent class). 
```js
super.speak() // calls parent's speak() function
super(); // calls parent's constructor.
```


