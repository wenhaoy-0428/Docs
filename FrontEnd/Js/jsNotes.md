## Question
1. What's the difference between `let`, `var` and `const`?
2. [Why variables can be used before declaration?](#var-hoisting)


## Basic


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
