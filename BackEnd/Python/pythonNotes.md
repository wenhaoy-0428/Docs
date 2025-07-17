# Python

## Python Env

For virtual environments, `venv` is a built-in library that come from python3.3 that allows the user to create a virtual environment.

`virtualenv` is a third-party library which is a pretty popular tool to create virtual env as well. 

`virtualenvwrapper` is a tool built upon `virtualenv` that mainly focuses on simplify the command lines. 

`Pyenv` is a popular Python version management tool that allows you to easily switch between multiple versions of Python on your system. It enables you to install and manage different versions of Python side by side, and set specific versions as the default for different projects or shell sessions.

> Tutorial: [Installation](https://www.youtube.com/watch?v=1F2IK7CU76U)

`Anaconda` is a distribution of Python. It also provides python version controls. It allows user to create virtual evn as well as specify the python version to be used. Not only that, it by default comes with more than enough machine learning/data analysis related packages installed out of the box. 

`JupyterNoteBook` is a web based tool that allows us to write markdown and python code together and run code as well. This is typically useful in document sharing in collaborations. Thus, it's one of the most popular tool in data analysis and machine learning. `JupyterLab` is a newer version of notebook that provides more IDE like interface and allows to have multiple tabs, which is more recommended. 

> JupyterNotebook /lab can be installed through Anaconda as well which is much easier to manage.

## [Common Sequence Operations](https://docs.python.org/3/library/stdtypes.html#sequence-types-list-tuple-range)

Sequence operations allows us to easily manipulate sequence types including **list**, **tuple**, **range**

The following code gives us a list of **n**  `0`s 
```py
dp = [0] * n
```

## walrus operator

The `:=` symbol is known as the "walrus operator" in Python. It was introduced in Python 3.8 and is used for assignment expressions.

The walrus operator allows you to assign a value to a variable within an expression. It combines the assignment statement with a conditional expression, making it useful in various scenarios, including loops, comprehensions, and conditional statements.

```python
while (input_value := input("Enter a value: ")) != "exit":
    print("You entered:", input_value)
```

## Reference 

Mutable data structures are stored as reference.

```python
t = [1]
s = [t]
print(s) # [[1]]
t.append(10) 
print(s) # [[1, 10]]
```

## Type Checking

Type checking in python is **not strict**.

**No enforcement at runtime**: Python ignores type hints during execution

```python
def add(a: int, b: int) -> int:
    return a + b

# These will all execute despite type violations
print(add(1, 2))      # OK - returns 3
print(add("1", "2"))   # Runs - returns "12"
print(add([1], [2]))   # Runs - returns [1, 2]
```

## Modules

Each file can be a module that encapsulates certain logics.

```python
# calculator.py

def add(a: float, b: float) -> float:
    return a + b

def subtract(a: float, b: float) -> float:
    return a - b
```

And can be used in other files/modules via importing

```python
# main.py
import calculator

result = calculator.add(5, 3)
```

## Packages

A package is a collection of modules organized in a directory hierarchy.

a special file `__init__.py` is required under the package root directory, and will be executed when the package is imported, only run only once.

`__all__` can also be defined in `__init__.py`, but it only controls what gets imported when a user does `from module import *`. It won't affect explicit importing.

```py
# - pkg
#   __init__.py
#   module1.py
#   module2.py

# pkg.__init__.py
__all__ = ["module1"]

# main.py
from pkg import *
module1.greet()
```

we don't have to explicitly import `module1` inside `__init__.py`, but using module name is sufficient. It will run the importing automatically.

```py
# module1.py
print('This is a hello from module1')

# pkg.__init__.py
print("This is a hello from __init__")
__all__ = ["module1"]

# main.py
from pkg import *

# Output:

"This is a hello from __init__"
"This is a hello from module1"
```

You can always explicit import `module2` even it's not included in `__all__`.


### Namespace package

A namespace package (python 3.3+) is a special type of Python package that let you split a package across multiple directories or distribution packages.

```
path1/
    my_namespace/
        module_a.py
        
path2/
    my_namespace/
        module_b.py
```

Both directories contribute to `my_namespace` package.


```
project/
├── plugin_a/
│   └── my_app/
│       └── plugins/
│           └── analytics.py
│
└── plugin_b/
    └── my_app/
        └── plugins/
            └── reporting.py

```

```py
# All these will work after both plugins are installed
from my_app.plugins import analytics
from my_app.plugins import reporting

# The namespace 'my_app.plugins' combines both locations
```



## Decorators

Decorators are functions that take another function as input and return a modified version of that function. They use the @decorator syntax and are applied right before function/class definitions.

```py
def my_decorator(func):
    def wrapper():
        print("Something is happening before the function is called.")
        func()
        print("Something is happening after the function is called.")
    return wrapper

@my_decorator
def say_hello():
    print("Hello!")

say_hello()
```


* Order matters: Decorators are applied from bottom to top
* 

## Manipulate with Files

### Serialization 

In Python, `pickling` is a process of converting a Python object into a serialized byte stream, which can be stored in a file or transferred over a network. The serialized representation of the object is called a pickled object, or simply a pickle.


The `pickle.dump()` function is used to serialize an object into a file, and the `pickle.load()` function is used to deserialize a pickled object from a file or a byte stream.

```py
# Unpickle the object from the file
with open('data.pickle', 'rb') as f:
    loaded_data = pickle.load(f)
# how loaded_data looks like {'name': 'John', 'age': 25, 'city': 'New York'}
```

## Numpy

### Broadcasting

When doing arithmetic operations between arrays of different dimensions. numpy will help to broadcast the operation. For example, when a 1D array tries to subtract a 2D array, the subtraction will be broadcast multiple times with each row of the 2D array.

```py
import numpy as np

a = np.array([1, 2, 3])
arr = np.array([[1, 2, 3], [4, 5, 6]])

arr - a
# array([[0, 0, 0],
#       [3, 3, 3]])
```

### Axis

Since arithmetic operations can be vectorized in numpy. Operations between Multi-dimensional matrices like `sum` has to specify the axis that the operation is performing on. In numpy, `axis=0` means going along the **row** and `axis=1` means going along the **colum**

```py
arr_2d = np.array([[1, 2, 3], [4, 5, 6]])

# Sum along axis 0 (columns)
sum_axis0 = np.sum(arr_2d, axis=0)
print(sum_axis0)
# Output: [5 7 9]

# Sum along axis 1 (rows)
sum_axis1 = np.sum(arr_2d, axis=1)
print(sum_axis1)
# Output: [ 6 15]

# 3D array
arr_3d = np.array([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])

# Sum along axis 0 (depth)
sum_axis0_3d = np.sum(arr_3d, axis=0)
print(sum_axis0_3d)
# Output: [[ 6  8]
#          [10 12]]

# Sum along axes 1 and 2
sum_axes12 = np.sum(arr_3d, axis=(1, 2))
print(sum_axes12)
# Output: [10 26]
```









## Questions

#### [What is `if __name__ == '__main__':`](https://stackoverflow.com/questions/419163/what-does-if-name-main-do)

#### [What is `__init__.py` file in a directory](https://stackoverflow.com/questions/448271/what-is-init-py-for)

#### [What are metaclasses in Python]()

#### [What does `**` and `*` do for parameter in Python](https://stackoverflow.com/questions/36901/what-does-double-star-asterisk-and-star-asterisk-do-for-parameters)

#### [What is python decorator](https://www.youtube.com/watch?v=r7Dtus7N4pI&t=575s)

Functions in python are regarded as objects and can be passed as a parameter to another function. Thus, it's possible to implement a wrapper function `W` that calls a function `F` as the following code.

```python
def F():
    pass

def W(f):
    f();

W(f)
```

For even more, the wrapper function can not only just call function `F` but also add some more attributes and conditions by adding more code before calling `F`. In summary, the reason to use wrapper function is to add more functionality to the original function `F` . **A decorator is a shorthand to the wrapper function notation.**


## [yield](https://www.youtube.com/watch?v=HnggP09mKpM)

Like Haskell, function with `yield` keyword inside is regarded as a generator. All codes will only be run during the first `next` call. The generator will be suspended at the line of `yield`, and resume when the next `next` is called.

```py
def func():
    print("hello world")
    for i in range(10):
        yield i

#prints nothing
count10 = func()

#prints Helloworld, 1
print(next(count10))
# prints 2
print(next(count10))
```