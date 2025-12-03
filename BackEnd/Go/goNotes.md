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
