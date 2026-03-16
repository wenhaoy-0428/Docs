## Package

### Overview
A package in Go is a way to organize and reuse code. Every Go program is made up of packages, and programs start running in package `main`. Packages provide encapsulation, modularity, and namespace management.

### Package Declaration
Every Go source file begins with a package declaration:
```go
package main        // Executable package
package mypackage   // Library package
```

### Key Concepts

#### Package Name Rules
- Must be lowercase, single word
- Avoid underscores, hyphens, or mixed case
- Package name should match the directory name (convention)

#### Main Package
```go
package main

import "fmt"

func main() {
    fmt.Println("Hello, World!")
}
```
- Special package that creates an executable
- Must contain a `main()` function as entry point
- Used for applications, not libraries

#### Library Packages
```go
package calculator

func Add(a, b int) int {
    return a + b
}

func subtract(a, b int) int { // lowercase = private
    return a - b
}
```

#### Shared Scope Within Package
All files belonging to the same package share the same namespace and can access each other's variables and functions (both exported and unexported) without imports.

**Example - Multiple files in the same package:**

```go
// File: math.go
package calculator

var pi = 3.14159  // Shared variable (unexported)

func multiply(a, b float64) float64 {  // Shared function (unexported)
    return a * b
}
```

```go
// File: geometry.go
package calculator

// Can access pi and multiply from math.go directly
func CircleArea(radius float64) float64 {
    return multiply(pi, radius*radius)  // Using shared variable and function
}

func UpdatePi(newValue float64) {
    pi = newValue  // Can modify shared variable
}
```

**Key Points:**
- No import statements needed between files in the same package
- Package-level variables are shared across all files
- Unexported (private) functions and variables are accessible within the package
- All files must have the same package declaration
- Changes to shared variables affect all files in the package

### Visibility and Exports

#### Exported vs Unexported
- **Exported**: Starts with uppercase letter (public)
- **Unexported**: Starts with lowercase letter (private)

```go
package mypackage

// Exported - can be used by other packages
var PublicVariable = "I'm public"
func PublicFunction() {}

// Unexported - only accessible within this package
var privateVariable = "I'm private"
func privateFunction() {}
```

### Package Import

#### Basic Import
```go
import "fmt"                    // Standard library
import "github.com/user/repo"   // External package
import "./local"                // Local relative path (not recommended)
```

#### Multiple Imports
```go
import (
    "fmt"
    "os"
    "strings"
)
```

#### Import Aliases
```go
import (
    f "fmt"                     // Alias
    . "strings"                 // Dot import (use with caution)
    _ "github.com/user/driver"  // Blank import (for side effects)
)
```

#### Import for Side Effects

Sometimes you import a package not to use its functions or variables, but solely to execute its `init()` functions, which produces certain "side effects" (such as registration, initialization, configuration, etc.).

```go
import _ "github.com/lib/pq"  // Registers PostgreSQL driver
```


### Package Structure

#### Recommended Directory Structure
```
myproject/
├── main.go
├── go.mod
├── go.sum
├── internal/           // Private packages
│   └── config/
├── pkg/               // Public packages
│   └── utils/
└── cmd/               // Main applications
    └── server/
```

#### Internal Packages
```go
// myproject/internal/config/config.go
package config

// Only accessible by packages in myproject
```

### Package Initialization

#### init() Function
```go
package mypackage

import "fmt"

var initialized bool

func init() {
    fmt.Println("Package initialized")
    initialized = true
}

func init() {
    // Multiple init functions are allowed
    fmt.Println("Second init function")
}
```

**Execution Order:**
1. Package-level variables
2. init() functions (in order of appearance)
3. main() function (if in main package)


### Best Practices

#### Package Organization
- One package per directory
- Keep packages focused and cohesive
- Use internal/ for private code
- Group related functionality



#### Circular Dependencies
```go
// Avoid circular imports
// package A imports B, B imports A (BAD)

// Use interfaces to break cycles
package user
type Storage interface {
    Save(User) error
}

package storage
import "myproject/user"
func (s *DB) Save(u user.User) error { /* */ }
```


### Pointer

#### Overview
A pointer is a variable that stores the memory address of another variable. Pointers allow you to pass variables by reference and create complex data structures.

#### Declaring and Using Pointers

```go
var p *int      // Declare a pointer to int
var ptr *string // Declare a pointer to string

x := 10
p = &x          // & operator gets the address of x
fmt.Println(p)  // Prints memory address (e.g., 0xc0000160a8)
fmt.Println(*p) // * operator dereferences, prints 10
```

**Key Operators:**
- `&` - Address operator: gets the memory address of a variable
- `*` - Dereference operator: accesses the value at the address

#### The Zero Value of Pointers

```go
var p *int
fmt.Println(p)      // <nil>
fmt.Println(p == nil) // true
```

Uninitialized pointers have a value of `nil`.

#### Modifying Values Through Pointers

```go
x := 5
p := &x

*p = 10         // Modify the value x through pointer
fmt.Println(x)  // 10
fmt.Println(*p) // 10
```

#### Pointer to Structs

```go
type Person struct {
    Name string
    Age  int
}

p := &Person{
    Name: "Alice",
    Age:  30,
}

// Two ways to access fields
fmt.Println(p.Name)      // Alice (Go auto-dereferences)
fmt.Println((*p).Name)   // Alice (explicit dereference)

// Modifying through pointer
p.Age = 31               // Direct assignment
fmt.Println(p.Age)       // 31
```

**Note:** Go automatically dereferences pointers when accessing struct fields.

#### Passing by Reference

```go
func increment(p *int) {
    *p = *p + 1
}

x := 5
increment(&x)
fmt.Println(x) // 6
```

Without pointers (pass by value), the original variable wouldn't change:

```go
func incrementValue(x int) {
    x = x + 1  // Only modifies local copy
}

y := 5
incrementValue(y)
fmt.Println(y) // Still 5
```

#### Pointers to Pointers

```go
x := 10
p := &x      // Pointer to x
pp := &p     // Pointer to pointer

fmt.Println(**pp)  // 10

**pp = 20
fmt.Println(x)     // 20
```

#### Arrays and Slices with Pointers

```go
arr := [3]int{1, 2, 3}
p := &arr       // Pointer to array

fmt.Println((*p)[0])  // 1

slice := []int{1, 2, 3}
pSlice := &slice  // Pointer to slice

fmt.Println((*pSlice)[0]) // 1
```

#### Common Patterns

**Creating a Pointer to a Variable:**

```go
x := 42
p := &x

// Or in one line with new()
p := new(int)  // Allocates memory and returns pointer
*p = 42
```

**Pointer Receivers (Methods on Pointers):**

```go
type Rectangle struct {
    Width, Height float64
}

// Pointer receiver - can modify the struct
func (r *Rectangle) Scale(factor float64) {
    r.Width *= factor
    r.Height *= factor
}

// Value receiver - cannot modify
func (r Rectangle) Area() float64 {
    return r.Width * r.Height
}

rect := Rectangle{Width: 10, Height: 5}
rect.Scale(2)         // Works - Go passes address automatically
fmt.Println(rect.Area())  // 200
```

#### Important Notes

- **Nil Pointers:** Always check if a pointer is nil before dereferencing
  ```go
  var p *int
  if p != nil {
      fmt.Println(*p)
  }
  ```

- **No Pointer Arithmetic:** Unlike C/C++, Go does not support pointer arithmetic
  ```go
  // This is NOT allowed in Go
  // p++  // ERROR
  ```

- **Garbage Collection:** Go has automatic garbage collection, so you don't need to free memory

- **Efficiency:** Use pointers for large structs to avoid copying, but prefer values for small types

#### When to Use Pointers

✓ **Use pointers when:**
- Modifying a struct in a method
- Avoiding expensive copies of large structs
- Building data structures like linked lists or trees
- Implementing optional parameters (nil check)

✗ **Avoid pointers for:**
- Small types (int, string, bool)
- Immutable data
- Simple value semantics


### Structs and Classes

#### Overview
Go doesn't have classes in the traditional OOP sense. Instead, it uses **structs** with **methods** to achieve similar functionality. This approach is simpler and more flexible than classical inheritance-based OOP.

#### Defining a Struct

```go
type Person struct {
    Name    string
    Age     int
    Email   string
    private string  // Unexported field (private)
}
```

**Key Points:**
- Capitalized fields are exported (public)
- Lowercase fields are unexported (private to the package)

#### Creating Struct Instances

**Method 1: Struct Literal**
```go
// Named fields (recommended)
p1 := Person{
    Name:  "Alice",
    Age:   30,
    Email: "alice@example.com",
}

// Positional (must include all fields in order)
p2 := Person{"Bob", 25, "bob@example.com", ""}

// Partial initialization (other fields get zero values)
p3 := Person{Name: "Charlie"}
fmt.Println(p3.Age)  // 0
```

**Method 2: New Function**
```go
p := new(Person)  // Returns *Person
p.Name = "David"
p.Age = 35
```

**Method 3: Constructor Function (Common Pattern)**
```go
func NewPerson(name string, age int) *Person {
    return &Person{
        Name: name,
        Age:  age,
    }
}

p := NewPerson("Eve", 28)
```

#### Adding Methods to Structs

Methods are functions with a special receiver argument that appears between `func` keyword and method name.

**Value Receiver:**
```go
type Rectangle struct {
    Width, Height float64
}

// Value receiver - receives a copy
func (r Rectangle) Area() float64 {
    return r.Width * r.Height
}

rect := Rectangle{Width: 10, Height: 5}
fmt.Println(rect.Area())  // 50
```

**Pointer Receiver:**
```go
// Pointer receiver - can modify the struct
func (r *Rectangle) Scale(factor float64) {
    r.Width *= factor
    r.Height *= factor
}

rect := Rectangle{Width: 10, Height: 5}
rect.Scale(2)  // Go automatically takes the address
fmt.Println(rect.Width)  // 20
```

**When to Use Each:**
- Use **pointer receiver** when: method needs to modify the struct, or struct is large
- Use **value receiver** when: method doesn't modify struct, or struct is small

> Methods can only be defined in the same package as where the struct type is defined.

#### Complete Class-Like Example

```go
package main

import "fmt"

// Define the "class"
type BankAccount struct {
    owner   string  // Private field
    balance float64 // Private field
}

// Constructor function
func NewBankAccount(owner string, initialBalance float64) *BankAccount {
    return &BankAccount{
        owner:   owner,
        balance: initialBalance,
    }
}

// Getter methods (read-only access to private fields)
func (a *BankAccount) Owner() string {
    return a.owner
}

func (a *BankAccount) Balance() float64 {
    return a.balance
}

// Methods that modify state
func (a *BankAccount) Deposit(amount float64) {
    if amount > 0 {
        a.balance += amount
    }
}

func (a *BankAccount) Withdraw(amount float64) bool {
    if amount > 0 && amount <= a.balance {
        a.balance -= amount
        return true
    }
    return false
}

// Method with value receiver (doesn't modify)
func (a BankAccount) String() string {
    return fmt.Sprintf("Account[owner=%s, balance=%.2f]", a.owner, a.balance)
}

func main() {
    account := NewBankAccount("Alice", 1000)
    account.Deposit(500)
    account.Withdraw(200)
    fmt.Println(account)  // Account[owner=Alice, balance=1300.00]
}
```

#### Embedded Structs (Composition over Inheritance)

Go uses **composition** instead of inheritance. You can embed structs to reuse fields and methods.

```go
type Animal struct {
    Name string
    Age  int
}

func (a Animal) Speak() {
    fmt.Println("Some sound")
}

// Dog "inherits" from Animal through embedding
type Dog struct {
    Animal  // Embedded struct
    Breed string
}

func (d Dog) Speak() {
    fmt.Println("Woof!")
}

func main() {
    dog := Dog{
        Animal: Animal{Name: "Buddy", Age: 3},
        Breed:  "Golden Retriever",
    }
    
    // Access embedded fields directly
    fmt.Println(dog.Name)   // Buddy
    fmt.Println(dog.Age)    // 3
    fmt.Println(dog.Breed)  // Golden Retriever
    
    // Method overriding
    dog.Speak()             // Woof!
    dog.Animal.Speak()      // Some sound (access embedded method)
}
```

#### Anonymous Structs

Useful for one-off data structures:

```go
// Define and initialize in one go
person := struct {
    Name string
    Age  int
}{
    Name: "Alice",
    Age:  30,
}

// Common in JSON marshaling
data := []struct {
    ID   int
    Name string
}{
    {1, "Alice"},
    {2, "Bob"},
}
```

#### Struct Tags

Used for metadata, commonly with JSON, XML, and database mapping:

```go
type User struct {
    ID        int    `json:"id"`
    FirstName string `json:"first_name"`
    LastName  string `json:"last_name"`
    Password  string `json:"-"`  // Ignore this field
    Email     string `json:"email,omitempty"`  // Omit if empty
}

// JSON marshaling
user := User{ID: 1, FirstName: "John", LastName: "Doe"}
jsonData, _ := json.Marshal(user)
fmt.Println(string(jsonData))
// {"id":1,"first_name":"John","last_name":"Doe"}
```

#### Struct Comparison

Structs are comparable if all their fields are comparable:

```go
type Point struct {
    X, Y int
}

p1 := Point{1, 2}
p2 := Point{1, 2}
p3 := Point{2, 3}

fmt.Println(p1 == p2)  // true
fmt.Println(p1 == p3)  // false
```

#### Private vs Public (Encapsulation)

```go
type employee struct {  // Private struct
    name   string       // Private field
    salary float64      // Private field
}

type Company struct {   // Public struct
    Name      string    // Public field
    employees []employee // Private field
}

// Public methods provide controlled access
func (c *Company) AddEmployee(name string, salary float64) {
    c.employees = append(c.employees, employee{name, salary})
}

func (c *Company) EmployeeCount() int {
    return len(c.employees)
}
```

#### Best Practices

✓ **Do:**
- Use constructor functions (NewXxx) for complex initialization
- Use pointer receivers for methods that modify the struct
- Use composition (embedding) instead of trying to simulate inheritance
- Keep structs focused and cohesive
- Use struct tags for serialization metadata

✗ **Don't:**
- Mix pointer and value receivers on the same type
- Make all fields public unless necessary
- Create deep inheritance hierarchies (use composition)
- Use getters/setters for all fields (only when needed)

#### Common Patterns

**Builder Pattern:**
```go
type Config struct {
    Host    string
    Port    int
    Timeout int
}

func NewConfig() *Config {
    return &Config{
        Host:    "localhost",
        Port:    8080,
        Timeout: 30,
    }
}

func (c *Config) WithHost(host string) *Config {
    c.Host = host
    return c
}

func (c *Config) WithPort(port int) *Config {
    c.Port = port
    return c
}

// Usage
config := NewConfig().
    WithHost("example.com").
    WithPort(9000)
```

**Factory Pattern:**
```go
type Shape interface {
    Area() float64
}

type Circle struct {
    Radius float64
}

func (c Circle) Area() float64 {
    return 3.14 * c.Radius * c.Radius
}

type Square struct {
    Side float64
}

func (s Square) Area() float64 {
    return s.Side * s.Side
}

func NewShape(shapeType string, size float64) Shape {
    switch shapeType {
    case "circle":
        return Circle{Radius: size}
    case "square":
        return Square{Side: size}
    default:
        return nil
    }
}
```


### Stack and Heap Memory

#### Overview
Go automatically manages memory allocation between the **stack** and **heap**. Understanding how Go decides where to allocate memory can help you write more efficient code.

**Stack:**
- Fast allocation and deallocation
- Memory automatically freed when function returns
- Limited in size (typically 2-8 KB initially, can grow)
- Thread-safe (each goroutine has its own stack)

**Heap:**
- Slower allocation (requires GC to clean up)
- Memory lives beyond function scope
- Shared across goroutines
- Managed by garbage collector

#### How Go Decides: Escape Analysis

Go uses **escape analysis** at compile time to determine whether a variable should be allocated on the stack or heap.

**General Rules:**
1. If a variable's lifetime is limited to a function → **Stack**
2. If a variable escapes the function scope → **Heap**

#### Stack Allocation Examples

```go
func stackExample() {
    x := 42           // Allocated on stack
    y := "hello"      // Allocated on stack
    z := [3]int{1, 2, 3}  // Array on stack
    
    // All variables freed when function returns
}

func calculate(a, b int) int {
    sum := a + b      // Stack allocation
    return sum        // Value copied, stack cleaned up
}
```

**Why Stack?**
- Variables don't escape the function
- Return value is copied
- No references persist after return

#### Heap Allocation Examples

**Example 1: Returning a Pointer**
```go
func heapExample1() *int {
    x := 42
    return &x  // x escapes to heap (returned pointer)
}
// x must live beyond function, so allocated on heap
```

**Example 2: Storing in Global Variable**
```go
var global *int

func heapExample2() {
    x := 42
    global = &x  // x escapes to heap (stored globally)
}
```

**Example 3: Large Data Structures**
```go
func heapExample3() {
    // Large slice allocated on heap
    data := make([]int, 1000000)
    // Process data...
}
```

**Example 4: Closure Capturing Variables**
```go
func heapExample4() func() int {
    x := 42
    return func() int {
        return x  // x escapes (referenced by closure)
    }
}
```

**Example 5: Interface Assignment**
```go
func heapExample5() {
    x := 42
    var i interface{} = x  // May cause x to escape to heap
    fmt.Println(i)
}
```

#### Checking Escape Analysis

Use the `-gcflags` option to see escape analysis decisions:

```bash
go build -gcflags='-m' main.go
```

Output example:
```
./main.go:5:2: moved to heap: x
./main.go:6:9: &x escapes to heap
./main.go:10:13: ... argument does not escape
```

**More verbose output:**
```bash
go build -gcflags='-m -m' main.go
```

#### Practical Examples with Analysis

**Example 1: Stack Allocation**
```go
package main

func sum(a, b int) int {
    result := a + b  // Stack
    return result
}

func main() {
    x := 10    // Stack
    y := 20    // Stack
    z := sum(x, y)  // Stack
    println(z)
}

// Escape analysis: No heap allocations
```

**Example 2: Heap Allocation**
```go
package main

type Point struct {
    X, Y int
}

func newPoint() *Point {
    p := Point{X: 1, Y: 2}  // Escapes to heap
    return &p
}

func main() {
    p := newPoint()
    println(p.X)
}

// Escape analysis: p escapes to heap
```

**Example 3: Optimization - Value Return**
```go
// Less efficient (heap allocation)
func createPersonPointer() *Person {
    return &Person{Name: "Alice", Age: 30}  // Heap
}

// More efficient (stack allocation)
func createPersonValue() Person {
    return Person{Name: "Alice", Age: 30}  // Stack
}

func main() {
    p1 := createPersonPointer()  // p1 points to heap
    p2 := createPersonValue()    // p2 on stack
}
```

#### Stack vs Heap Performance

```go
package main

import "testing"

type Data struct {
    values [100]int
}

// Heap allocation
func BenchmarkHeap(b *testing.B) {
    for i := 0; i < b.N; i++ {
        _ = createHeap()
    }
}

func createHeap() *Data {
    return &Data{}  // Escapes to heap
}

// Stack allocation
func BenchmarkStack(b *testing.B) {
    for i := 0; i < b.N; i++ {
        _ = createStack()
    }
}

func createStack() Data {
    return Data{}  // Stays on stack
}

// Results: Stack allocation is significantly faster
// BenchmarkHeap-8    50000000    25.3 ns/op    800 B/op    1 allocs/op
// BenchmarkStack-8  2000000000   0.33 ns/op      0 B/op    0 allocs/op
```

#### Common Scenarios and Allocation

| Scenario                               | Allocation | Reason                          |
| -------------------------------------- | ---------- | ------------------------------- |
| Local variable, not referenced outside | Stack      | Lifetime ends with function     |
| Return pointer to local variable       | Heap       | Pointer escapes function        |
| Large arrays/slices (>10 KB)           | Heap       | Size exceeds stack comfort zone |
| Global variables                       | Heap       | Lifetime is entire program      |
| Interface conversion                   | Often Heap | Dynamic type requires heap      |
| Goroutine captures variable            | Heap       | Variable outlives function      |
| Passed to `fmt.Println`                | Heap       | Interface{} parameter           |
| Small structs passed by value          | Stack      | No escaping reference           |

#### Slices, Maps, and Channels

```go
func sliceExample() {
    // Slice header (len, cap, ptr) on stack
    // Underlying array on heap
    s := make([]int, 10)
    
    // Small slice might be stack-allocated
    small := []int{1, 2, 3}
    
    _ = s
    _ = small
}

func mapExample() {
    // Map header on stack
    // Map data structure on heap
    m := make(map[string]int)
    m["key"] = 42
}

func channelExample() {
    // Channel structure always on heap
    ch := make(chan int)
    _ = ch
}
```

#### Optimization Strategies

**1. Return Values Instead of Pointers (When Possible)**
```go
// Before: Heap allocation
func getBounds() *Rectangle {
    return &Rectangle{Width: 10, Height: 20}
}

// After: Stack allocation
func getBounds() Rectangle {
    return Rectangle{Width: 10, Height: 20}
}
```

**2. Avoid Capturing Variables in Closures**
```go
// Before: x escapes to heap
func badClosure() func() {
    x := 42
    return func() {
        println(x)  // Captures x
    }
}

// After: Pass as parameter
func goodClosure() func(int) {
    return func(x int) {
        println(x)  // No capture
    }
}
```

**3. Use Value Receivers for Small Structs**
```go
type Point struct {
    X, Y int
}

// Value receiver - passed on stack
func (p Point) String() string {
    return fmt.Sprintf("(%d, %d)", p.X, p.Y)
}

// Pointer receiver - may cause heap allocation
func (p *Point) Move(dx, dy int) {
    p.X += dx
    p.Y += dy
}
```

**4. Preallocate Slices to Avoid Multiple Allocations**
```go
// Less efficient: Multiple heap allocations
func bad() []int {
    var result []int
    for i := 0; i < 1000; i++ {
        result = append(result, i)  // Multiple reallocations
    }
    return result
}

// More efficient: Single heap allocation
func good() []int {
    result := make([]int, 0, 1000)
    for i := 0; i < 1000; i++ {
        result = append(result, i)  // No reallocation
    }
    return result
}
```

#### Stack Growth

Go stacks start small and grow dynamically:

```go
func recursiveExample(n int) {
    if n <= 0 {
        return
    }
    var buffer [1024]byte  // Each call adds 1KB to stack
    _ = buffer
    recursiveExample(n - 1)
}

// Stack grows as needed, but deep recursion can cause issues
```

**Stack Size:**
- Initial: ~2 KB per goroutine
- Grows: Automatically doubles when needed
- Max: Limited by available memory (not by OS thread stack)

#### Best Practices

✓ **Do:**
- Let Go's escape analysis do its job
- Profile before optimizing
- Return values instead of pointers for small structs
- Use value receivers when you don't need to modify the struct
- Preallocate slices when you know the size

✗ **Avoid:**
- Premature optimization
- Returning pointers to small structs unnecessarily
- Creating unnecessary closures that capture variables
- Using `new()` when value initialization works

#### Key Insights

1. **Stack allocation is much faster** than heap allocation
2. **Escape analysis is automatic** - compiler decides for you
3. **Returning pointers causes heap allocation** - consider returning values
4. **Large objects go to heap** regardless of escape analysis
5. **Use `-gcflags='-m'` to understand** allocation decisions
6. **Profile first, optimize second** - don't guess about performance


### Garbage Collection

#### Overview
Go has automatic memory management with a built-in **garbage collector (GC)** that automatically frees memory that is no longer in use. This eliminates the need for manual memory management (like `malloc`/`free` in C) while providing predictable performance for most applications.

#### How Go's GC Works

**Concurrent Mark-and-Sweep Algorithm:**
Go uses a **tri-color mark-and-sweep** algorithm that runs concurrently with the application.

```
1. Mark Setup (Stop-the-World)
   - Brief pause to prepare for marking
   - Very short duration (~10-100 microseconds)

2. Concurrent Marking
   - Runs alongside application code
   - Identifies reachable objects
   - Uses write barriers to track changes

3. Mark Termination (Stop-the-World)
   - Another brief pause
   - Finishes marking phase

4. Concurrent Sweeping
   - Reclaims unmarked memory
   - Runs in background
   - Application continues normally
```

**Tri-Color Marking:**
- **White**: Objects not yet examined (potentially garbage)
- **Gray**: Objects found but not yet scanned
- **Black**: Objects examined and reachable

#### GC Triggers

The GC runs automatically when:
1. **Heap size threshold**: When live heap grows to 2x the previous collection size (by default)
2. **Time-based**: If 2 minutes pass without a GC cycle
3. **Manual trigger**: Calling `runtime.GC()` explicitly

```go
import "runtime"

func main() {
    // Force garbage collection (usually not recommended)
    runtime.GC()
}
```

#### Monitoring Garbage Collection

**Using GODEBUG:**
```bash
GODEBUG=gctrace=1 go run main.go
```

Output example:
```
gc 1 @0.004s 0%: 0.018+0.23+0.003 ms clock, 0.14+0.083/0.19/0.21+0.024 ms cpu, 4->4->0 MB, 5 MB goal, 8 P
```

Breakdown:
- `gc 1`: GC cycle number
- `@0.004s`: Time since program start
- `0%`: Percentage of CPU time spent in GC
- `4->4->0 MB`: Heap size before, after marking, after sweeping
- `5 MB goal`: Target heap size for next GC
- `8 P`: Number of processors

**Using runtime/debug:**
```go
package main

import (
    "fmt"
    "runtime"
    "runtime/debug"
)

func main() {
    var m runtime.MemStats
    runtime.ReadMemStats(&m)
    
    fmt.Printf("Alloc = %v MB", m.Alloc / 1024 / 1024)
    fmt.Printf("\nTotalAlloc = %v MB", m.TotalAlloc / 1024 / 1024)
    fmt.Printf("\nSys = %v MB", m.Sys / 1024 / 1024)
    fmt.Printf("\nNumGC = %v\n", m.NumGC)
    
    // Get GC statistics
    stats := debug.GCStats{}
    debug.ReadGCStats(&stats)
    fmt.Printf("Last GC: %v\n", stats.LastGC)
    fmt.Printf("Num GC: %v\n", stats.NumGC)
}
```

#### Special Cases Handling

**1. Reference Cycle**

```go
type Node struct {
    next *Node
    data string
}

func createCycle() {
    a := &Node{data: "A"}
    b := &Node{data: "B"}
    a.next = b
    b.next = a  // 循环引用！
} // 即使函数结束，a 和 b 仍互相引用
// Go GC 能处理循环引用，当外部没有引用时会清理
```

**2. File Descriptor**

```go

func readFile() {
    // 必须手动清理的资源
    file, err := os.Open("data.txt")
    if err != nil {
        return
    }
    defer file.Close()  // ✅ 必须手动关闭
    
    data := make([]byte, 100)
    // ... 使用 file
} // file.Close() 自动调用，释放系统资源
```

**3. Closure Prolongs GC LC**

```go
func counter() func() int {
    count := 0  // 被闭包捕获，延长生命周期
    return func() int {
        count++
        return count
    }
}

func main() {
    inc := counter()
    fmt.Println(inc())  // 1
    fmt.Println(inc())  // 2
    // count 变量一直存在，直到 inc 不再被引用
}
```

**4. Global Variable Never Clears**

```go
var globalCache = make(map[string]interface{})

func init() {
    globalCache["config"] = loadConfig()
}
// globalCache 在程序运行期间一直存在
```

#### Memory Management Best Practices

**1. Avoid Memory Leaks:**
```go
// BAD: Goroutine leak
func leakyFunction() {
    ch := make(chan int)
    go func() {
        // This goroutine will never exit
        val := <-ch  // Blocks forever
    }()
    // ch is never written to, goroutine leaks
}

// GOOD: Proper cleanup
func goodFunction(ctx context.Context) {
    ch := make(chan int)
    go func() {
        select {
        case val := <-ch:
            // Process value
        case <-ctx.Done():
            return  // Exit when context cancelled
        }
    }()
}
```

**2. Reuse Objects with sync.Pool:**
```go
import "sync"

var bufferPool = sync.Pool{
    New: func() interface{} {
        return make([]byte, 1024)
    },
}

func processData() {
    // Get buffer from pool
    buffer := bufferPool.Get().([]byte)
    defer bufferPool.Put(buffer)  // Return to pool
    
    // Use buffer...
}
```

**3. Avoid Unnecessary Allocations:**
```go
// BAD: Creates new slice on each iteration
func badConcat(strs []string) string {
    result := ""
    for _, s := range strs {
        result += s  // Allocates new string each time
    }
    return result
}

// GOOD: Use strings.Builder
import "strings"

func goodConcat(strs []string) string {
    var builder strings.Builder
    for _, s := range strs {
        builder.WriteString(s)
    }
    return builder.String()
}
```

**4. Pre-allocate Slices:**
```go
// BAD: Multiple reallocations
func bad() []int {
    var nums []int
    for i := 0; i < 1000; i++ {
        nums = append(nums, i)  // May reallocate multiple times
    }
    return nums
}

// GOOD: Pre-allocate capacity
func good() []int {
    nums := make([]int, 0, 1000)  // Pre-allocate capacity
    for i := 0; i < 1000; i++ {
        nums = append(nums, i)  // No reallocation needed
    }
    return nums
}
```

#### Finalizers

Finalizers run when an object is about to be garbage collected (rarely used):

```go
import "runtime"

type Resource struct {
    id int
}

func NewResource(id int) *Resource {
    r := &Resource{id: id}
    
    // Set finalizer
    runtime.SetFinalizer(r, func(r *Resource) {
        fmt.Printf("Resource %d is being collected\n", r.id)
        // Cleanup code here
    })
    
    return r
}

// Remove finalizer
runtime.SetFinalizer(r, nil)
```

**Warning:** Finalizers are not guaranteed to run immediately or at all. Don't rely on them for critical cleanup.

#### Common GC Issues and Solutions


**Issue 1: High GC Overhead**
```go
// Solution: Reduce allocations
// Use benchmarks to identify hot paths
go test -bench=. -benchmem
```

**Issue 2: Large Heap Size**
```go
// Solution: Profile memory usage
import _ "net/http/pprof"

go func() {
    http.ListenAndServe("localhost:6060", nil)
}()
// Visit http://localhost:6060/debug/pprof/heap
```

**Issue 3: GC Pauses**
```go
// Solution 1: Reduce live heap size
// Solution 2: Use GOGC to tune
// Solution 3: Optimize allocation patterns
```

#### Profiling Memory

**Heap Profile:**
```go
import (
    "os"
    "runtime/pprof"
)

func captureHeapProfile() {
    f, _ := os.Create("heap.prof")
    defer f.Close()
    pprof.WriteHeapProfile(f)
}

// Analyze with:
// go tool pprof heap.prof
```

**Memory Benchmarks:**
```go
func BenchmarkMyFunction(b *testing.B) {
    b.ReportAllocs()  // Report allocation statistics
    
    for i := 0; i < b.N; i++ {
        myFunction()
    }
}

// Run: go test -bench=. -benchmem
```

#### Key Takeaways

✓ **Understand:**
- GC is automatic and concurrent
- Most applications don't need GC tuning
- Focus on reducing allocations for performance

✓ **Monitor:**
- Use `GODEBUG=gctrace=1` to observe GC behavior
- Profile memory with `pprof` when needed
- Track allocations with benchmarks

✓ **Optimize:**
- Reuse objects with `sync.Pool`
- Pre-allocate slices and maps
- Avoid unnecessary string concatenation
- Use pointers for large structs

✗ **Avoid:**
- Calling `runtime.GC()` in production
- Relying on finalizers for critical cleanup
- Premature optimization without profiling
- Disabling GC with `GOGC=off`


