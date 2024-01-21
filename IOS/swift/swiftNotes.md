# Swift

A very quick introduction to Swift can be found at [A Swift tour](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/guidedtour/).

## [Procedure of instantiating subclass](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/guidedtour/#Objects-and-Classes)

1. Setting the value of properties that the subclass declares.
2. Calling the superclass’s initializer.
3. Changing the value of properties defined by the superclass. Any additional setup work that uses methods, getters, or setters can also be done at this point.

## Structure vs Classes

Use `struct` to create a structure. Structures support many of the same behaviors as classes, including methods and initializers.** One of the most important differences between structures and classes is that structures are always copied when they’re passed around in your code, but classes are passed by reference.**


### Properties

Properties of classes, structures can be mainly classified into 2 categories: **Stored Property** and **Computed Property**.

A Stored Property is just simple declarations of variables or constants of a class/structure. 

A Computed Property doesn't store any information rather represent a value that is computed based on one or more Stored Properties. Hence, it has 0 or 1 getter/setter function.

#### Stored Property

Worth mentioning that variable stored properties can **NOT** be modified if the **structure** instance is constant.

```swift
struct Temp {
    var prop1 = 10
}

let instance = Temp()

// This will cause error.
instance.prop1 = 1 
```

This behavior is due to structures being **value** types. When an instance of a value type is marked as a constant, so are all of its properties.

The same isn’t true for classes, which are **reference** types. If you assign an instance of a reference type to a constant, you can still change that instance’s variable properties.

More of this behavior can be found at [Stored Properties of Constant Structure Instances](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/properties#Stored-Properties-of-Constant-Structure-Instances)

#### Initialization

In swift, class initialization uses [2 phase initialization](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/initialization#Two-Phase-Initialization). (Due to the fact that structure doesn't have inheritance, it can only conforms to protocols not another struct/class, the chain up procedure will be later discussed is not fit here.)

* Phase 1
  1. A designated or convenience initializer is called on a class.
  2. Memory for a new instance of that class is allocated. The memory isn’t yet initialized.
  3. A designated initializer for that class confirms that all stored properties introduced by that class have a value. The memory for these stored properties is now initialized.
  4. The designated initializer hands off to a superclass initializer to perform the same task for its own stored properties.
  5. This continues up the class inheritance chain until the top of the chain is reached.
  6. Once the top of the chain is reached, and the final class in the chain has ensured that all of its stored properties have a value, the instance’s memory is considered to be fully initialized, and phase 1 is complete.

> Only After Phase 1 is completed `self` is available, and only stored properties are initialized in Phase 1

* Phase 2
  1. Working back down from the top of the chain, each designated initializer in the chain has the option to customize the instance further. Initializers are now able to access self and can modify its properties, call its instance methods, and so on.
  2. Finally, any convenience initializers in the chain have the option to customize the instance and to work with self.

#### Computed Property

Due the behavior of 2-Phase initialization, computed properties that rely on stored properties can not be computed until phase 1 is completed as `self` can not be accessed yet util that moment.

> One important note here, since computed properties rely on other properties and don't have its own storage, it can't be used as stateful variables for SwiftUI by prefixing `@State` property wrapper.

## [Self vs self](https://stevenpcurtis.medium.com/self-or-self-in-swift-code-b0d2199ec2ef)

In Swift `Self` with capital letter `S` is actually different from `self` with lowercase `s`. 

`Self` and `self` are commonly used inside class/struct/protocol and `Self` represents the type, while `self` represent the object instance.

In the following code snippet, `self` represent an object instance and hence can access all properties inside the object. `Self` on the other hand is type, meaning in function `test` the return type is `Person` itself.

```swift
struct Person {
    let name: String
    init(name: String) {
        self.name = name
    }
}

extension Person {
    static func test(name: String = "Rosa") -> Self {
        .init(name: name)
    }
}
```




## Generic

Generic is basically the same as Template in C++. However, unlike CPP Template that you can explicitly specify the type when using the template. Here, in Swift, you can't. All Generic functions are specialized through inference automatically either by **parameter type** or **return type**. 

More can be found at [How to explicitly specialize a generic function in Swift](https://sarunw.com/posts/how-to-explicitly-specialize-generic-function-in-swift/)

## Closure

### Trailing Closure

Like JavaScript, functions can also be passed around as arguments hence it includes its own closure. In the following example, by is a function with its own closure.

```swift
reversedNames = names.sorted(by: { (s1: String, s2: String) -> Bool in
    return s1 > s2
})
```

Here, if the closure is the **final** argument meaning it's the last argument of parameters, we can omit it in the parameter parenthesis and have it its own trailing bracket. 

```swift
func someFunctionThatTakesAClosure(closure: () -> Void) {
    // function body goes here
}

// Here's how you call this function without using a trailing closure:

someFunctionThatTakesAClosure(closure: {
    // closure's body goes here
})

// Here's how you call this function with a trailing closure instead:

someFunctionThatTakesAClosure() {
    // trailing closure's body goes here
}
```

Trailing Closure is greatly used in [SwiftUI](#swiftui). For example, creating a horizontal stack using `HStack`

```swift
HStack() {
    landmark.image
        .resizable()
        .frame(width: 50, height: 50)
    Text(landmark.name)
    
    Spacer()
}
```

The above notation makes the bracket a trailing closure (a function) that can be later evaluated. Even though, the closure is a function and it passed along as a function which can be found at the description of [HStack](https://developer.apple.com/documentation/swiftui/hstack/init(alignment:spacing:content:)) that it accepts a function closure in the end, it seems that indeed its **not** really handled as a function by Swift. Under the hood, HStack or other containers invoke `@ViewBuilder` which is an implementation of `@resultBuilder`. How resultBuilder handlers the closure is called [result builder transform](https://github.com/apple/swift-evolution/blob/main/proposals/0289-result-builders.md#the-result-builder-transform). It reads each statement inside the closure and calls one of the required function named `buildBlock` to build a hierarchy. More of `resultBuilder` can be found at [A deep dive into Swift’s result builders](https://www.swiftbysundell.com/articles/deep-dive-into-swift-function-builders/).



## KeyPath

A key path is a reference to properties. Meaning, we are referencing to the properties itself, not the value of it. For example, with the following code snippet. A keyPath `\A.prop1` is a reference to the `prop1` itself, instead of the value of it. Hence, we're sorting a array of objects based on certain property. We can just tell the keyPath as it references to the property itself rather than the value.

```swift
struct A {
    var prop1: String = "10"
    var prop2: String = "1"
}
```

This is a basic introduction of keyPath and tells what it is. More can be found at [Understanding Swift KeyPaths](https://www.youtube.com/watch?v=2-fzccDtc7o) for video and [What is a KeyPath in Swift](https://sarunw.com/posts/what-is-keypath-in-swift/) for post.

## Exclamation Mark or Force Unwrap

The `!` operator in Swift is known as the force-unwrap operator or the force unwrapping operator. It is used to forcefully unwrap an optional value, indicating that the programmer expects the optional to contain a non-nil value.

In the following code, it's forced to unwrap the value returned from `...min()`. 

```swift
// use guard to enure data are safe to be used with !
guard !ranges.isEmpty else { return 0..<0 }
let low = ranges.lazy.map { $0.lowerBound }.min()!
```

