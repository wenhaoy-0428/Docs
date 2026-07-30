# Rust 基础概念速查

## 1. Rust 工具链

Rust 官方推荐使用 `rustup` 安装和管理工具链。

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

常见工具：

| 工具       | 作用               |
| -------- | ---------------- |
| `rustup` | 安装、更新和切换 Rust 版本 |
| `rustc`  | Rust 编译器         |
| `cargo`  | 项目、依赖、构建和测试管理工具  |

验证安装：

```bash
rustc --version
cargo --version
rustup --version
```

---

## 2. Cargo

Cargo 不只是依赖管理工具，它同时负责：

* 创建项目
* 管理依赖
* 编译项目
* 运行程序
* 执行测试
* 格式化和静态检查

创建可执行项目：

```bash
cargo new hello
cd hello
cargo run
```

创建库项目：

```bash
cargo new calculator --lib
```

在现有目录初始化：

```bash
cargo init
```

常用命令：

```bash
cargo check
cargo build
cargo run
cargo test
cargo fmt
cargo clippy
cargo build --release
```

添加项目依赖：

```bash
cargo add serde
```

安装命令行工具：

```bash
cargo install ripgrep
```

区别：

```text
cargo add       给当前项目添加依赖
cargo install   安装全局命令行程序
```

---

## 3. Cargo.toml

`Cargo.toml` 是 Cargo package 的配置文件，类似 JavaScript 的 `package.json`。

```toml
[package]
name = "my-app"
version = "0.1.0"
edition = "2024"

[dependencies]
serde = "1.0"
```

执行 `cargo run` 时，Cargo 会从当前目录向父目录查找 `Cargo.toml`。

出现以下错误：

```text
could not find Cargo.toml
```

表示当前目录不属于 Cargo 项目。

可以执行：

```bash
cargo init
```

---

# 4. Package、Crate、Module 和文件

这是 Rust 项目结构中最容易混淆的部分。

| 概念      | 含义                            |
| ------- | ----------------------------- |
| Package | Cargo 管理的项目，由 `Cargo.toml` 定义 |
| Crate   | Rust 的独立编译单元                  |
| Module  | Crate 内部组织代码的命名空间             |
| 文件      | 承载模块代码的物理文件                   |

关系：

```text
Package
├── Crate
│   ├── Module
│   └── Module
└── Crate
```

---

## 5. Crate

Crate 是一次独立交给 Rust 编译器处理的代码单元。

两种主要 crate：

```text
Binary crate    编译成可执行程序
Library crate   编译成库
```

### Binary crate

默认入口：

```text
src/main.rs
```

必须包含：

```rust
fn main() {
    println!("Hello");
}
```

### Library crate

默认入口：

```text
src/lib.rs
```

不需要 `main()`：

```rust
pub fn add(a: i32, b: i32) -> i32 {
    a + b
}
```

---

## 6. `main.rs` 和 `lib.rs` 为什么是两个 crate

当一个 package 同时包含：

```text
src/main.rs
src/lib.rs
```

Cargo 会创建两个独立编译目标：

```text
src/main.rs → binary crate
src/lib.rs  → library crate
```

它们不是父子模块，而是两个平级 crate：

```text
Package
├── binary crate
└── library crate
```

在 `main.rs` 中使用 `lib.rs`，需要通过库 crate 名访问。

假设：

```toml
[package]
name = "my-app"
```

`src/lib.rs`：

```rust
pub fn add(a: i32, b: i32) -> i32 {
    a + b
}
```

`src/main.rs`：

```rust
use my_app::add;

fn main() {
    println!("{}", add(1, 2));
}
```

Cargo package 名中的 `-`，在 Rust 路径中通常写成 `_`：

```text
my-app → my_app
```

---

## 7. Cargo 自动识别的 Crate Root

Cargo 默认会把以下文件识别为独立编译目标：

| 路径                       | 类型                         |
| ------------------------ | -------------------------- |
| `src/lib.rs`             | Library crate              |
| `src/main.rs`            | 默认 Binary crate            |
| `src/bin/server.rs`      | 名为 `server` 的 Binary crate |
| `examples/demo.rs`       | Example crate              |
| `tests/api_test.rs`      | Integration test crate     |
| `benches/performance.rs` | Benchmark crate            |
| `build.rs`               | Build script crate         |

普通文件不会自动成为 crate：

```text
src/user.rs
src/service.rs
```

它们必须通过 `mod` 加入某个 crate。

---

# 8. Module

Module 用于：

* 组织代码
* 建立命名空间
* 控制可见性
* 拆分文件

同文件模块：

```rust
mod math {
    pub fn add(a: i32, b: i32) -> i32 {
        a + b
    }
}

fn main() {
    println!("{}", math::add(1, 2));
}
```

不同文件：

```text
src/
├── main.rs
└── math.rs
```

`main.rs`：

```rust
mod math;

fn main() {
    println!("{}", math::add(1, 2));
}
```

`math.rs`：

```rust
pub fn add(a: i32, b: i32) -> i32 {
    a + b
}
```

关键区别：

```rust
mod math {
    // 模块内容直接写在这里
}
```

```rust
mod math;
// 模块内容去对应文件中寻找
```

---

## 9. 文件不会自动成为 Module

单独创建：

```text
src/user.rs
```

不会让它自动进入项目。

必须由某个模块声明：

```rust
mod user;
```

如果 `main.rs` 声明：

```rust
mod user;
```

那么 `user.rs` 属于 binary crate。

如果 `lib.rs` 声明：

```rust
pub mod user;
```

那么 `user.rs` 属于 library crate。

判断一个文件属于哪个 crate：

```text
从文件对应的 mod 声明向上追溯
最终到 main.rs → binary crate
最终到 lib.rs  → library crate
```

---

## 10. 不要在 main.rs 和 lib.rs 重复声明同一文件

假设：

```text
src/
├── main.rs
├── lib.rs
└── user.rs
```

如果两个文件都写：

```rust
mod user;
```

那么 `user.rs` 会分别进入两个 crate：

```text
binary crate
└── user

library crate
└── user
```

这不是共享同一个模块，而是同一份源码被分别编译两次。

推荐方式：

```rust
// lib.rs
pub mod user;
```

```rust
// main.rs
use my_app::user;
```

业务模块通常放进 library crate，`main.rs` 只负责程序入口。

---

## 11. 多层 Module

目录：

```text
src/
├── lib.rs
├── user.rs
└── user/
    └── service.rs
```

`lib.rs`：

```rust
pub mod user;
```

`user.rs`：

```rust
pub mod service;
```

`user/service.rs`：

```rust
pub fn run() {
    println!("running");
}
```

模块树：

```text
crate
└── user
    └── service
```

路径：

```rust
crate::user::service::run();
```

每一级父模块都必须声明它的子模块。

---

## 12. `mod` 名是否必须全局唯一

不需要全局唯一。

同一个父模块下，子模块名必须唯一：

```rust
mod service;
mod service; // 错误
```

不同路径下可以同名：

```text
crate::app::service
crate::book::service
```

完整路径不同，因此不会冲突。

---

## 13. Rust Module 与 Go Package 的区别

Go 会自动合并同一个 package 下的多个文件：

```text
user/
├── create.go
├── update.go
└── query.go
```

文件都声明：

```go
package user
```

Rust 不会自动合并同名模块。

不能在多个文件中分别重新定义：

```rust
mod user {
}
```

然后期待 Rust 自动拼接。

Rust 必须使用明确的模块树：

```text
user
├── create
├── update
└── query
```

```rust
pub mod create;
pub mod update;
pub mod query;
```

---

## 14. 同一个 Struct 可以有多个 impl

虽然 module 不能跨文件自动合并，但同一个类型可以在多个文件中添加方法。

`user.rs`：

```rust
mod operations;

pub struct User {
    name: String,
}

impl User {
    pub fn new(name: &str) -> Self {
        Self {
            name: name.to_string(),
        }
    }
}
```

`user/operations.rs`：

```rust
use super::User;

impl User {
    pub fn rename(&mut self, name: &str) {
        self.name = name.to_string();
    }
}
```

最终可以直接调用：

```rust
let mut user = User::new("Hao");
user.rename("Xiao Hao");
```

Rust 没有传统 class，通常使用：

```text
struct              定义数据
impl Type           定义类型自己的方法
trait               定义抽象能力
impl Trait for Type 给类型实现某种能力
```

---

# 15. 路径语法

## `crate::`

从当前 crate 根开始：

```rust
use crate::user::User;
```

在 `lib.rs` 模块树中，`crate` 指向 `lib.rs`。

在 `main.rs` 模块树中，`crate` 指向 `main.rs`。

## `self::`

从当前模块开始：

```rust
use self::service::run;
```

## `super::`

从父模块开始：

```rust
use super::User;
```

## `::`

访问模块、类型或关联成员：

```rust
std::fs::read_to_string
Vec::new
String::from
User::new
```

---

## 16. `use` 和 `mod` 的区别

```rust
mod user;
```

负责声明模块并把模块加入当前 crate。

```rust
use crate::user::User;
```

负责把已有路径引入当前作用域。

可以理解为：

```text
mod    建立模块树
use    缩短访问路径
```

`use` 不能代替 `mod`。

---

# 17. 变量声明

常见完整语法：

```rust
let mut variable_name: Type = expression;
```

例如：

```rust
let mut count: i32 = 0;
```

组成：

```text
let       声明绑定
mut       允许修改，可选
count     变量名
i32       类型，可选
0         初始化表达式
```

常见形式：

```rust
let count = 0;
let mut count = 0;
let count: i32 = 0;
let mut count: i32 = 0;
```

Rust 变量默认不可变：

```rust
let count = 0;
count = 1; // 错误
```

允许修改：

```rust
let mut count = 0;
count = 1;
```

更准确地说，`let` 后面可以是 pattern：

```rust
let (name, age) = ("Hao", 27);
```

---

# 18. Rust 是静态类型安全语言

Rust 是静态类型语言。

```rust
let age: i32 = 27;
age = "hello"; // 编译错误
```

即使不显式写类型：

```rust
let age = 27;
```

编译器仍会在编译期确定类型。

Rust 的类型系统还会检查：

* 函数参数和返回值
* 泛型约束
* 枚举匹配是否完整
* 引用是否有效
* 可变借用是否冲突
* 部分线程安全问题

---

# 19. 函数和表达式

函数：

```rust
fn add(a: i32, b: i32) -> i32 {
    a + b
}
```

`-> i32` 表示返回类型。

最后一行没有分号时，该表达式是返回值：

```rust
a + b
```

也可以显式返回：

```rust
return a + b;
```

Rust 中很多结构都是表达式：

```rust
let result = if condition {
    10
} else {
    20
};
```

---

# 20. Loop 返回值

```rust
let mut count = 0;

let result = loop {
    count += 1;

    if count == 3 {
        break count * 10;
    }
};
```

结果：

```text
result = 30
```

`loop` 是表达式，`break value` 指定它的返回值：

```rust
break count * 10;
```

如果只写：

```rust
break;
```

则返回空值：

```rust
()
```

---

# 21. `match` 和 `=>`

```rust
let message = match status {
    200 => "OK",
    404 => "Not Found",
    _ => "Unknown",
};
```

`=>` 表示：

```text
匹配模式 => 匹配成功后执行的表达式
```

`_` 表示其他所有情况。

函数返回类型使用的是：

```rust
->
```

不是 `=>`。

---

# 22. Macro 和 `!`

```rust
println!("Hello");
```

`println!` 是宏，不是普通函数。

常见宏：

```rust
println!("Hello");
vec![1, 2, 3];
format!("Hello {}", name);
panic!("error");
```

普通函数调用没有 `!`：

```rust
String::from("hello");
user.rename("Hao");
```

---

# 23. Vec

`Vec<T>` 是动态数组。

```rust
let mut numbers: Vec<i32> = Vec::new();

numbers.push(10);
numbers.push(20);
```

拆解：

```text
Vec          类型
::           访问类型的关联成员
new          关联函数
()           调用函数
```

也可以使用宏：

```rust
let numbers = vec![1, 2, 3];
```

`new` 不是关键字，只是常见的关联函数名。

---

# 24. 所有权

Rust 中，每个值都有一个所有者。

```rust
let s1 = String::from("hello");
let s2 = s1;
```

这里所有权从 `s1` 移动到 `s2`。

之后不能继续使用：

```rust
println!("{s1}"); // 错误
```

需要复制数据时：

```rust
let s2 = s1.clone();
```

---

# 25. 引用和借用

引用允许访问数据，而不获取所有权。

```rust
fn print_text(text: &String) {
    println!("{text}");
}

let message = String::from("hello");

print_text(&message);
println!("{message}");
```

符号：

```text
&T       不可变引用
&mut T   可变引用
*        解引用
```

---

## 26. 不可变引用

```rust
fn get_length(text: &str) -> usize {
    text.len()
}
```

字符串参数通常优先使用：

```rust
&str
```

而不是：

```rust
&String
```

因为 `&str` 可以同时接收：

```rust
let message = String::from("hello");

get_length(&message);
get_length("hello");
```

---

## 27. 可变引用

```rust
fn append_world(text: &mut String) {
    text.push_str(" world");
}

let mut message = String::from("hello");

append_world(&mut message);
```

需要同时满足：

```rust
let mut message
```

```rust
text: &mut String
```

```rust
&mut message
```

---

## 28. 借用规则

同一时间，对同一份数据：

```text
可以有多个不可变引用
或者有一个可变引用
不能同时存在冲突的可变和不可变引用
```

允许：

```rust
let r1 = &message;
let r2 = &message;
```

不允许同时使用：

```rust
let r1 = &mut message;
let r2 = &mut message;
```

也不允许冲突：

```rust
let r1 = &message;
let r2 = &mut message;
```

---

## 29. 解引用

```rust
let number = 10;
let reference = &number;

println!("{}", *reference);
```

记忆：

```text
&value       创建引用
*reference   解引用
```

修改引用指向的值：

```rust
let mut number = 10;
let reference = &mut number;

*reference += 5;
```

---

## 30. `self`、`&self` 和 `&mut self`

```rust
impl User {
    fn consume(self) {}

    fn read(&self) {}

    fn modify(&mut self) {}
}
```

含义：

```text
self       获取对象所有权
&self      不可变借用，只读
&mut self  可变借用，可以修改
```

---

# 31. 推荐项目结构

对于同时包含库和可执行程序的项目：

```text
my-app/
├── Cargo.toml
└── src/
    ├── lib.rs
    ├── main.rs
    ├── user.rs
    └── user/
        └── service.rs
```

`lib.rs`：

```rust
pub mod user;
```

`user.rs`：

```rust
pub mod service;

pub struct User {
    pub name: String,
}
```

`user/service.rs`：

```rust
use super::User;

pub fn print_user(user: &User) {
    println!("{}", user.name);
}
```

`main.rs`：

```rust
use my_app::user::service::print_user;
use my_app::user::User;

fn main() {
    let user = User {
        name: String::from("Hao"),
    };

    print_user(&user);
}
```

模块树：

```text
library crate
└── user
    └── service

binary crate
└── 使用 library crate
```

---

# 32. 核心结论

```text
Cargo.toml 定义 Package。

main.rs、lib.rs 等 crate root 定义独立 Crate。

mod 用于在 Crate 内建立 Module 树。

.rs 文件本身不会自动成为 Module。

一个文件属于哪个 Crate，由 mod 声明链决定。

main.rs 和 lib.rs 是两个独立 Crate。

同一个父 Module 下，子 Module 名不能重复。

Rust 不会像 Go 一样自动合并同 package 的多个文件。

同一个 Struct 可以在多个文件中拥有多个 impl。

& 表示借用，&mut 表示可变借用，* 表示解引用。
```
