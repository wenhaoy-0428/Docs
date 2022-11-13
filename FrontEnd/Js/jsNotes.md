## Question
1. [What's the difference between `let`, `var` and `const`?](#difference-between-let-var-const-bare)
2. [Why variables can be used before declaration?](#var-hoisting)
3. [What is `this`?](#this)
4. [What's the back-tick](#string-template)
5. [What's the difference between null and undefined](#https://www.geeksforgeeks.org/undefined-vs-null-in-javascript/)


## Basic

### [All keywords](https://www.w3schools.com/js/js_reserved.asp)

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
  - variable is never hoisted when, access before initialization cause `ReferenceError`.
  - disallows re-declaring.
  - disallows globally defined.
  - disallows redeclare from var to let in the same scope.
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
  - At runtime, when the initialization code is reached, the variable's scope will bubble up until it reaches a usage of the variable or the global scope, and **attaches** to the variable used/or found declaration with keyword.
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
  - const variable can't be re-declared and reassigned, and changed. 
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

---

### Place to define Js

* `script` can be placed inside `head`, `body` and `external`
* **Placing scripts at the bottom of the <body> element improves the display speed, because script interpretation slows down the display.**
* `external` Js can benefit from Cached JavaScript files that speeds up page loads

---

### Output

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

### Nullish coalescing assignment operator

If the first value is undefined or null, the second value is assigned.

```js
let x = 10;
x ??= 5;
y ??= 5;
console.log(x); // print 10;
console.log(y); // print 5;
```

--- 

### [This](https://www.w3schools.com/js/js_this.asp)

`this` is not a variable. It is a **keyword**. You cannot change the value of this.

- In an object method, this refers to the object.
- Alone, this refers to the global object.
- In a function, this refers to the global object.
- In a function, in strict mode, this is undefined.
- In an event, this refers to the element that received the event.
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
- Methods like call(), apply(), and bind() can refer this to any object.

---

### Type Identification

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

### Object

* It's a common practice to `declare` an object as [const](#difference-between-let-var-const-bare)

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

---

### String

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

### Number

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
### Array

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

## Var hoisting

1. The parser of js engine will read through the entire file before running it, and any variable declarations (using `var`) will be executed as if they were at the top of the containing scope. Note: only declarations are hoisted, not the definition. [->Ref](https://stackoverflow.com/questions/20220862/in-javascript-can-i-use-a-variable-before-it-is-declared), [->Ref](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/var#var_hoisting)

    ```js
    console.log(value_); // This will print out undefined, but it will work.
    var value_ = "HelloWorld"; // declaration will be hoisted but definition.
    console.log(value_); // This will print out HelloWorld as expected.
    // --- a different example below.
    console.log(value_); // This will throw an error.
    // without declaration.
    ```
