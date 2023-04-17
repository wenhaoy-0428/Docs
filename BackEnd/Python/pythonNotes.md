# Python

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

